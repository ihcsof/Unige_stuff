//main.cpp (Lorenzo Foschi - 4989646)

/*	 Si sceglie di implementare il sistema a registri incontrato durante
	i laboratori del corso, al fine di fornire maggiore flessibilità
	all'utente (la lettura da registro sovrascrive il precedente genogramma) 
*/

#include "genogramma.h"

using namespace std;
using namespace gen;
using namespace period;

// Costante per la dim dei registri
const int MAXREG = 10;

int main() {
	
	// Utilizzo dei registri
	Genogram g[MAXREG];
	for(int i = 0; i < MAXREG; ++i)
		g[i] = createEmpty();  
	
	// Variabili ausiliarie
	string nomefile, choice, validation;
	int scelta = 0;
	Label l1, l2, l3;
	int dd, m, y;
	int r;

	// Ciclo di scelta per l'utente: s'interromperà all'inserimento di zero
	for(;;) {

	// Visualizzazione menu e acquisizione scelta
	scelta = menu();
	
	// Acquisizione del registro
	if(scelta > 0 && scelta < 13) {
		cout << "Inserisci il registro su cui operare: ";
		cin >> r;
		// Error handling sull'inserimento registro
		if(isError()) continue;
		if (r < 0 || r >= MAXREG) {
			cout << "\nIndice out of range" << endl; 
			continue;
		}
	}

	switch (scelta) {
			// Se l'utente ha scelto "0" vuole uscire dal programma
			case 0:  
						// clear dei registri per evitare mem. leaks (test effettuato con valgrind)
						for(int i = 0; i < MAXREG; ++i)
							if(!isEmpty(g[i])) clearGen(g[i]);

						return 0;
			case 1:	
						cout << "Inserisci il nome del file da cui leggere" << endl;
						cin >> nomefile;
				
						// Lettura avvenuta con successo
						if(readFromFile(nomefile, g[r]))
							cout << "Lettura di " << nomefile << " avvenuta con successo" << endl;
						else {
							cout << "Lettura di " << nomefile << " errata" << endl;

							// clear dei registri per evitare mem. leaks (test effettuato con valgrind)
							for(int i = 0; i < MAXREG; ++i)
								if(!isEmpty(g[i])) clearGen(g[i]);

							return 1;
						}

						break;
			case 2:
						// Leggo la persona tramite l'apposita funzione e provo ad aggiungerla
						if(addPersonFromCin(g[r])) {
							cout << "Persona aggiunta con successo" << endl;
							break;
						}
						// Si sceglie di non terminare il programma nel caso di persona non aggiunta
						cout << "Persona non aggiunta" << endl;

						break;
			case 3:	
						cout << "\nLabel del figlio: ";
						cin >> l1;

						cout << "\nLabel della madre: ";
						cin >> l2;
	
						// Aggiunta di una relazione madre-figlio
						if(addRelMother(g[r], l2, l1))
							cout << l2 << " e' madre di " << l1 << endl;
						else
							cout << "Relazione non aggiunta\n";
				
						break;
			case 4:
						cout << "\nLabel del figlio: ";
						cin >> l1;

						cout << "\nLabel del padre: ";
						cin >> l2;

						// Aggiunta di una relazione padre-figlio
						if(addRelFather(g[r], l2, l1))
							cout << l2 << " e' padre di " << l1 << endl;
						else
							cout << "Relazione non aggiunta\n";

						break;
			case 5:	
						cout << "\nLabel della prima persona: ";
						cin >> l1;

						cout << "\nLabel della seconda persona: ";
						cin >> l2;

						// Aggiunta di una relazione di coppia
						if(addRelCouple(g[r], l1, l2))
							cout << l1 << " e' partner di " << l2 << endl;
						else
							cout << "Relazione non aggiunta\n";
						break;
			case 6:	
						cout << "\nLabel del figlio: ";
						cin >> l1;

						cout << "\nLabel del padre: ";
						cin >> l2;

						cout << "\nLabel della madre: ";
						cin >> l3;

						// Aggiunta di un figlio ad una coppia
						if(addRelChildToCouple(g[r], l1, l2, l3))
							cout << l1 << " e' figlio/a di " << l2 << " e " << l3 << endl;
						else
							cout << "Relazione non aggiunta\n";

				
						break;
			case 7:
						cout << "\nLabel del nodo di cui settare la data di nascita: ";
						cin >> l1;

						// Lettura della data da cin con controlli --> inserimento della stessa
						if(!readDateCin(dd, m, y)) {
							cout << "Data non settata";
							break;
						}
						if(setBirth(g[r], l1, y, m , dd))
							cout << "Data settata";
						else cout << "Data non settata";

						break;
			case 8:	
						cout << "\nLabel del nodo di cui settare la data di morte: ";
						cin >> l1;

						// Lettura della data da cin con controlli --> inserimento della stessa
						if(!readDateCin(dd, m, y)) {
							cout << "Data non settata";
							break;
						}
						if(setDeath(g[r], l1, y, m , dd))
							cout << "Data settata";
						else cout << "Data non settata"; 

						break;
			case 9:
						cout << "\nLabel della persona da cancellare: ";
						cin >> l1;

						// Cancellazione della persona dal genogramma
						if(deletePerson(g[r], l1))
							cout << l1 << " cancellata" << endl;
						else
							cout << "Nodo non cancellato\n";
						break;
			case 10:
						// Check sulla validità del genogramma
						if(isValid(g[r], validation))
							cout << "Il genogramma e' valido\n";
						else
							cout << validation;
						break;
			case 11: 
						// Stampa su stdout
						printGenogram(g[r]);

						break;
			case 12: 
						// Check di esistenza
						cout << "\nLabel della persona da cercare: ";
						cin >> l1;

						if(isIn(g[r], l1))
							cout << l1 << " e' presente nel genogramma\n";
						else
							cout << "Non presente\n";

						break;
			// Scelta non valida
			default:
						break;
	 }
	}
}
