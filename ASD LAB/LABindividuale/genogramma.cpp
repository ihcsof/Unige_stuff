/*
	genogramma.cpp (Lorenzo Foschi - 4989646)

	halfEdge (mezz'arco di collegamento a figlio x,y..)
	NB: ordinamento in base alla data di nascita
	----------------------------------
	|	puntatore a nodo (figlio x)
	|--------------------------------
	|	puntatore al prossimo edge
	----------------------------------

	Person (persona x con tutti i campi associati)
	----------------------------------
	|	nome
	|--------------------------------
	|	sesso
	|--------------------------------
	|	data di nascita (facolt.)
	|--------------------------------
	|	data di morte (facolt.)
	|--------------------------------
	
	node
	----------------------------------
	|	persona (nome, sesso, date)
	|--------------------------------
	|	puntatore alla madre del nodo
	|--------------------------------
	|	puntatore al padre del nodo
	|--------------------------------
	|	puntatore alla lista di figli
	|--------------------------------
	|	puntatore al partner del nodo
	|--------------------------------
	|	marcatura di visita
	|--------------------------------
	|	puntatore al prox nodo
	----------------------------------

	Si implementano le funzioni esposte in modo tale da lavorare
	sulle Label e non direttamente sui puntatori: inf. hiding
*/

#include "genogramma.h"
#include "queue.h"
#include <sstream>
#include <fstream>

using namespace gen;
using namespace period;
using namespace queue;

// Struct halfEdge e node (v. sopra per dettagli):

struct halfEdge {
	node* ptr;
	halfEdge* next;
};

// Struct Persona di utility

struct Person {
	Label name;
	gender sex;
	period::Date birth;
	period::Date death;
};

struct gen::node {
	Person elem;
	node* father;
	node* mother;
	halfEdge* children;
	node* partner;
	bool visited;
	node* next;
};

// Costante emptyedge per il mezz'arco (information hiding)
halfEdge* const EMPTYEDGE = nullptr;

// Funzione per inizializzazione genogramma vuoto
Genogram gen::createEmpty() {
	return EMPTYGEN;
}

// Funzione di controllo isEmpty per information hiding
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::isEmpty(const Genogram& g) {
	return (g == EMPTYGEN);
}

// Ausiliaria per check isEmpty sull'half edge
bool isEmptyEdge(halfEdge* e) {
	return (e == EMPTYEDGE);
}

// Funzione ausiliaria stateful per formattazione stringhe
Label format(Label& l) {
	// (mArIo --> Mario)
	l[0] = toupper(l[0]);
	// Ciclo sulla length (uint per evitare warning con --Wall)
	for(unsigned int i = 1; i < l.length(); ++i) 
		l[i] = tolower(l[i]);
	return l;
}

// Ausiliaria (ciclo da lab asd) per rendere i vertici non marcati
void makeNotVisited(Genogram g) {
	for(; !isEmpty(g); g->visited = false, g = g->next);
}

// Ausiliaria per la ricerca di un nodo all'interno del Genogramma
node* getNode(const Genogram& g, Label l) {
	// Formattazione corretta della label
	format(l);
	Genogram aux = g;
	// Ciclo fino a che e' pieno: se trovo il nodo ritorno il puntatore
	while(!isEmpty(aux)) {
		if((aux->elem).name == l) return aux;
		aux = aux->next;
	}
	// Ritorno EMPTYGEN se non ho trovato il nodo
	return EMPTYGEN;
}

// Ausiliaria per addPerson
/* Crea una persona per utilizzarla nella addPerson senza che fuori
 dall'implementazione venga "bucato" il tipo di dato Genogramma. Non si
 effettua in modo ridondante il controllo sulla data, poichè TDD a parte. */
bool createPerson(Label l, char sex, Date birth, Date death, Person& p) {
	p.name = l;
	// Check sul sesso
	switch(sex) {
		case 'M': 
						p.sex = M;
						break;
		case 'F': 
						p.sex = F;
						break;
		default:		
						return false;
	}
	p.birth = birth;
	p.death = death;
	return true;
}

// Ausiliaria per l'aggiunta in testa alla lista di nodi
bool headInsert(Genogram& g, const Person& p) {
	// Creazione e init di un nuovo nodo Genogramma
	Genogram aux = new node;
	aux->elem = p;
	aux->father = aux->mother = aux->partner = EMPTYGEN;
	aux->children = EMPTYEDGE;

	// Inserimento in testa alla lista di nodi
	aux->next = g;
	g = aux;
	return true;
}

// Funzione per verificare se una persona e' presente nel genogramma
// Ritorna se non e' EMPTYGEN il valore ritornato da getNode
bool gen::isIn(const Genogram& g, Label l) {
	return (!isEmpty(getNode(g, l)));
}

// Funzione di aggiunta di una persona al genogramma (no relazioni)
// Utilizza una createPerson per mantenere consistente il tdd
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::addPerson(Genogram& g, Label l, char sex, Date birth, Date death) {
	// Creo una persona e utilizzo l'ausiliaria effettuando i controlli adeguati
	Person p;
	if(!createPerson(l, sex, birth, death, p)) return false;
	// Formattazione della label con funzione stateful (mArIo --> Mario)
	// Se la persona esiste già (la chiave univoca e' il nome): fallisce
	if(isIn(g, format(p.name))) return false;
	// Inserimento in testa
	return headInsert(g, p);
}

// Funzioni per settare le date di nascita e morte
// Si effettua creazione e validazione data
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::setBirth(const Genogram& g, Label l, int y, int m , int d) {
	// Creazione e validazione data
	Date date = createDate(y, m, d);
	if(verifyDate(date)) {
		// Ottengo il nodo; se esiste aggiorno la sua data di nascita
		Genogram toEdit = getNode(g, l);
		if(!isEmpty(toEdit)) {
			(toEdit->elem).birth = date;
			return true;
		}
	}
	return false;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::setDeath(const Genogram& g, Label l, int y, int m , int d) {
	// Creazione e validazione data
	Date date = createDate(y, m, d);
	if(verifyDate(date)) {
		// Ottengo il nodo; se esiste aggiorno la sua data di morte
		Genogram toEdit = getNode(g, l);
		if(!isEmpty(toEdit)) {
			(toEdit->elem).death = date;	
			return true;
		}		
	}
	return false;
}

// Funzione ausiliaria per cancellare la lista di figli
// Uso direttamente e per non dover impostare esplicitamente a EMPTYEDGE
void clearChildren(halfEdge* &e) {
	while(!isEmptyEdge(e)) {
		halfEdge* tmp = e->next;
		delete e;
		e = tmp;
	}
}

// Funzione per cancellare un genogramma
// Uso direttamente g per non dover impostare esplicitamente a EMPTYGEN
void gen::clearGen(Genogram& g) {
	// Ciclo fino a che e' pieno per cancellare il nodo x e la sua lista di figli
	while(!isEmpty(g)) {
		Genogram tmp = g->next;
		// Cancello la lista dei figli --> cancello il nodo --> vado avanti	
		clearChildren(g->children);
		delete g;
		g = tmp;
	}
}

// Ausiliaria per l'aggiunta ordinata di un figlio nella lista di figli
void addChild(Genogram& parent, Genogram& child) {
	halfEdge* e = parent->children;
	halfEdge* aux = new halfEdge;
	aux->ptr = child;
	// Caso di lista vuota o elem minore del primo
	if(isEmptyEdge(e) || (e->ptr->elem).birth > (child->elem).birth) {
		aux->next = e;
		parent->children = aux;
		return;
	}
	// Sposto avanti il puntatore finchè la lista e' piena e l'ordine e' mantenuto
	// Sfrutto l'operatore overloaded e la data INT_MAX non valida
	while(!isEmptyEdge(e->next) && (e->next->ptr->elem).birth < (child->elem).birth)
		e = e->next;

	// Inserimento del figlio nella pos corretta
	aux->next = e->next;
	e->next = aux;
}

// Funzione di aggiunta di una relazione "madre"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::addRelMother(const Genogram& g, Label mother, Label child) {
	// Trovo il figlio (se non esiste o ha già la madre ritorno false)
	Genogram ch = getNode(g, child);
	if(isEmpty(ch) || !isEmpty(ch->mother)) return false;
	// Trovo la madre (se non esiste ritorno false)
	Genogram mom = getNode(g, mother);
	if(isEmpty(mom)) return false;

	// Aggiungo la madre al figlio
	ch->mother = mom;

	// Aggiungo (in ordine) il figlio alla lista di figli della madre
	addChild(mom, ch);

	return true;
}

// Funzione di aggiunta di una relazione "padre"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::addRelFather(const Genogram& g, Label father, Label child) {
	// Trovo il figlio (se non esiste o ha già la padre ritorno false)
	Genogram ch = getNode(g, child);
	if(isEmpty(ch) || !isEmpty(ch->father)) return false;
	// Trovo il padre (se non esiste ritorno false)
	Genogram dad = getNode(g, father);
	if(isEmpty(dad)) return false;

	// Aggiungo il padre al figlio
	ch->father = dad;

	// Aggiungo (in ordine) il figlio alla lista di figli del padre
	addChild(dad, ch);

	return true;
}

// Funzione di aggiunta di una relazione "coppia"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::addRelCouple(const Genogram& g, Label a, Label b) {
	// Ottenimento dei nodi e controlli incrociati
	Genogram g1 = getNode(g, a);
	if(isEmpty(g1)) return false;
	Genogram g2 = getNode(g, b);
	if(isEmpty(g2)) return false;
	if(!isEmpty(g1->partner) || !isEmpty(g2->partner)) return false;
	
	//Aggiunta della relazione (simmetrica)
	g1->partner = g2;
	g2->partner = g1;
	return true;
}

// Funzione di aggiunta di una relazione "figlio alla coppia"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::addRelChildToCouple(const Genogram& g, Label child, Label a, Label b) {
	// Ottenimento dei nodi genitore e controlli incrociati
	Genogram g1 = getNode(g, a);
	if(isEmpty(g1)) return false;
	Genogram g2 = getNode(g, b);
	if(isEmpty(g2)) return false;

	// Check sull'esistenza della relazione coppia (simmetrica)
	if(g1->partner != g2) return false;

	// Ottenimento del nodo figlio
	Genogram gCh = getNode(g, child);
	if(isEmpty(gCh)) return false;
	
	// Se il figlio ha già genitori: esci
	if(!isEmpty(gCh->mother) || !isEmpty(gCh->father)) return false;

	// Aggiunta delle relMother e relFather (il controllo e' delegato alla isValid)
	if((g1->elem).sex == M) {
		gCh->father = g1;
		gCh->mother = g2;
	}
	else {
		gCh->father = g2;
		gCh->mother = g1;
	}

	// Aggiunta del figlio alla lista di figli di madre e padre
	addChild(g1, gCh);
	addChild(g2, gCh);

	return true;
}

// Funzione aux ricorsiva che marca un'intera discendenza
void mark(Genogram& g) {
	// Pongo a visitato il nodo
	g->visited = true;
	
	// Chiamo la funzione su tutti i suoi figli per visitarli
	halfEdge* e = g->children;
	for(; !isEmptyEdge(e); e = e->next) {
		// Se il nodo non e' visitato, chiamo mark su di lui
		if(!e->ptr->visited)
			mark(e->ptr);
	}
}

// Eliminazione dalle liste di figli dei nodi marcati
/* Devo eliminare dai figli dei genitori del primo nodo; il nodo stesso
	ma anche da tutti i genitori senza relazione che però hanno figli
	in comune con la discendenza che sto eliminando */
void delChildren(Genogram g) {
	while(!isEmpty(g)) {
		halfEdge* e = g->children;
		halfEdge* prev;
	
		while(!isEmptyEdge(e)) {
			// Se il figlio e' visitato; lo cancello
			if(e->ptr->visited) {
				// Caso in testa
				if(e == g->children) {
					// Elimino head mandando avanti il puntatore a children
					g->children = e->next;
					delete e;
					e = g->children;
				}
				else {
					// Salto l'arco eliminandolo
					prev->next = e->next;
					delete e;
					e = prev->next;
				}
			}
			else {
				prev = e;
				e = e->next;
			}
		}

		g = g->next;
	}
}

// Funzione che elimina tutti i nodi visitati dalla lista
void delVisited(Genogram& g) {
	Genogram cur = g;
	Genogram prev;

	while(!isEmpty(cur)) {
		// Elimino tutti i nodi che trovo visitati
		if(cur->visited) {
			// Dealloco la lista di figli del nodo da eliminare
			clearChildren(cur->children);
			// Elimino la relazione (simmetrica) di parentela
			if(!isEmpty(cur->partner))
				cur->partner->partner = EMPTYGEN;
			// Caso di nodo in testa
			if(cur == g) {
				// Elimino head mandando avanti il puntatore del genogram
				g = g->next;
				delete cur;
				cur = g;
			}
			else {
				// Salto il nodo eliminandolo
				prev->next = cur->next;
				delete cur;
				cur = prev->next;
			}
		}
		else {
			prev = cur;
			cur = cur->next;
		}
	}
}

// Funzione che cancella una persona dal genogramma e tutta la sua discendenza
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::deletePerson(Genogram& g, Label l) {
	// Rendo i nodi non visitati
	makeNotVisited(g);
	// Ottengo il nodo da cancellare e chiamo l'ausiliaria ricorsiva (se esiste)
	Genogram node = getNode(g, l);
	if(isEmpty(node)) return false;

	// Marcatura della discendenza da eliminare
	mark(node);

	// Eliminazione dalle liste di figli dei nodi marcati
	delChildren(g);

	// Eliminazione dalla lista dei nodi di quelli marcati
	delVisited(g);
	return true;
}

// Algoritmo dfs per la visita del genogramma
void dfs(const Genogram& g) {
	// Pongo a visitato il nodo
	g->visited = true;

	// Chiamo sul partner (non fa parte della discendenza, ma SI della connessione)
	if(!isEmpty(g->partner) && !g->partner->visited) 
		dfs(g->partner);

	// Devo chiamare anche sui genitori (partner con i suoi genitori)
	if(!isEmpty(g->father) && !g->father->visited) 
		dfs(g->father);
	if(!isEmpty(g->mother) && !g->mother->visited) 
		dfs(g->mother);
	
	// Chiamo la funzione su tutti i suoi figli per visitarli
	halfEdge* e = g->children;
	for(; !isEmptyEdge(e); e = e->next) {
		// Se il nodo non e' visitato, chiamo mark su di lui
		if(!e->ptr->visited)
			dfs(e->ptr);
	}
}

// Funzione ausiliaria per risalire il genogramma: controllo sulla discendenza
/* Non basta controllare il genitore: le date vuote creano problemi, dunque
	controllo tutta la discendenza fermandomi alla prima data non vuota (salto
	le date vuote arrivando al punto in cui inizia di nuovo l'ordine totale)
	1) se empty: il genogramma e' valido (ritorno false)
	2) se la data e' vuota: passo induttivo (controllo se è invalido uno dei rami)
	3) ritorno, se data !vuota, il bool di validazione della data
*/
bool isInvalidAncestor(const Genogram& g, Date d) {
	// Non ho trovato date problematiche
	if(isEmpty(g)) return false;
	// La data era vuota, continuo a risalire il genogramma
	if(isEmpty((g->elem).birth)) 
		return isInvalidAncestor(g->father, d) || isInvalidAncestor(g->mother, d);
	// Se la data è presente, ritorno la validazione
	return (d <= (g->elem).birth);
}

// Funzione per verificare se il genogramma e' valido
/* Si ritorna una stringa con i dettagli invece che array per evitare al chiamante 
	di dover conoscere il numero di errori che la isValid può generare.
	Si e' escluso un cout all'interno della funzione poichè non lascia traccia alcuna
	al chiamante del risultato ottenuto dalla isValid.
*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool gen::isValid(const Genogram& g, std::string& s) {
	if(isEmpty(g)) return true;
	s = "";
	// Bit vector per flag di errore
	bool e[] = {0, 0, 0, 0};

	// Rendo i nodi non visitati
	makeNotVisited(g);
	// Visita in profondità completa, a partire da un x nodo in prima pos
	dfs(g);
	
	Genogram aux = g;
	// Ciclo sulla lista dei vertici per effettuare i 4 controlli della isValid
	while(!isEmpty(aux)) {
		// Ottimizzazione: esco appena conscio della presenza di tutti gli errori
		if(e[0] && e[1] && e[2] && e[3]) return false;

		// Impostazione errore #1 (check genitori biologici)
		if(!e[0]) {
			// Controllo sul padre
			if(!isEmpty(aux->father) && (aux->father->elem).sex != M) {
				e[0] = true;
				s.append("Errore sul controllo genitori biologici\n");
			}
			// Controllo sulla madre
			else if(!isEmpty(aux->mother) && (aux->mother->elem).sex != F) {
				e[0] = true;
				s.append("Errore sul controllo genitori biologici\n");
			}
		}

		// Impostazione errore #2 (Ex la cui nascita e' successiva rispetto alla discendenza)
		// Data la natura facoltativa delle date, se EMPTYDATE non considero errori
		if(!e[1] && !isEmpty((aux->elem).birth)) {
			// Controllo sul padre (se la sua data e' EMPTYDATE non effettuo controllo)
			if(isInvalidAncestor(aux->father, (aux->elem).birth)) {
				e[1] = true;
				s.append("Esiste persona la cui nascita e' precedente rispetto alla discendenza\n");
			}
			// Controllo sulla madre (se la sua data e' EMPTYDATE non effettuo controllo)
			else if(isInvalidAncestor(aux->mother, (aux->elem).birth)) {
				e[1] = true;
				s.append("Esiste persona la cui nascita e' precedente rispetto alla discendenza\n");
			}
		}

		// Impostazione errore #3 (data nascita precedente a data morte)
		// Data la natura facoltativa delle date, se EMPTYDATE non considero errori
		if(!e[2] && !isEmpty((aux->elem).birth) && (aux->elem).birth > (aux->elem).death) {
			e[2] = true;
			s.append("Data di nascita successiva alla data di morte\n");
		}

		// Impostazione errore #4 (grafo sconnesso)
		if(!e[3] && !aux->visited) {
			e[3] = true;
			s.append("Il grafo risulta sconnesso\n");
		}
		
		aux = aux->next;
	}

	// Ritorno true sse il genogramma e' valido (nessun errore presente)
	return !(e[0] || e[1] || e[2] || e[3]);
}

// Ausiliaria per i check sulla validità delle stringhe
bool stringCheck(int x, std::string s) {
	std::string converted = std::to_string(x);
	return (converted.length() < s.length());
}

/* Si potrebbe assumere che l'inserimento avvenga con l'esatto formato. 
	Tuttavia, onde evitare comunque esecuzioni non eleganti del programma si opta 
	per effettuare un layer di controllo su alcuni casi limite più evidenti.
	Vengono controllati valori non validi tra i campi della data e successivi
	ad essa, e viene chiamato il controllo sulla validità della data stessa. */

period::Date convertDateForInsert(std::string d) {
	// Se trovo il carattere speciale "-": ritorno EMPTYDATE
	if(d == "-") return period::EMPTYDATE;
	try {
		Date toRet;
		// Frammento la stringa tra ogni separatore, utilizzando stoi per convertire
		// Viene chiamata la erase per facilitare la gestione dello spostamento di offset

		// Conversione e controllo del giorno
		int pos = d.std::string::find_first_of("/");
		toRet.dd = stoi(d);
		// Considero un offset di -1 sulla validità in caso di conversione di tipo 08-->8
		int zeroPerso = (toRet.dd < 10);
		if(stringCheck(toRet.dd, d.substr(0, pos-zeroPerso)))
			throw "Errore sul dato giorno";
		d.erase(0, pos+1);
		
		// Conversione e controllo del mese
		pos = d.std::string::find_first_of("/");
		toRet.mm = stoi(d);
		zeroPerso = (toRet.mm < 10);
		if(stringCheck(toRet.mm, d.substr(0, pos-zeroPerso)))
			throw "Errore sul dato mese";
		d.erase(0, pos+1);
		
		toRet.yyyy = stoi(d);
		// Check su caratteri rimasti (anno)
		if(stringCheck(toRet.yyyy, d))
			throw "Errore sul dato anno";
		if(!verifyDate(toRet))
			throw "Data non valida";
		return toRet;

	} catch(const char* err) {
		// Come primo filtro di eccezioni, lancio gli errori dati dalle verifiche
		throw err;

	} catch(...) {
		// stoi può lanciare invalid argument oppure out of range
		throw "Errore di conversione della data";
	}
}

/* 
	La funzione readFromFile, oltre a leggere un genogramma da file
	, prende in input un Genogramma in modo tale da fare una clear
	prima della sovrascrittura dello stesso (si evita il memory leak).
*/
bool readFromFile(std::string filename, Genogram& g) {
	// Elimino il genogramma se vuoto
	if(!isEmpty(g)) clearGen(g);
	// Apro il file passato per parametro
	std::ifstream ifs(filename.c_str());
	// Blocco try per gestione degli errori con comunicazione contestuale
	try {
   	if (!ifs.is_open()) throw "Errore in apertura file";
		// Variabili di ausilio
		char what, kind;
		std::string str;
		std::string nome, nome2, data;
		Date birth, death;

		// Ciclo di lettura su getline, avvalendosi di uno stream sstream
		while(getline(ifs, str)) {
			// Scelta di progettazione: si lascia comporre il file con righe vuote, anche..
			// .. per una corretta gestione di un "a capo" a fine file, che verrebbe..
			// .. interpretato dalla getline come un errore da terminazione (per bit di stato).
			if(str.length() == 0) continue;
			std::istringstream in(str);
			if(!(in >> what)) throw "Errore in lettura tipo di inserimento";
			
			// Casistiche di inserimento (persona o relazione)
			// Eccetto le date, si tratta di un insieme di letture, successivi controlli ..
			// .. sulla correttezza delle stesse e inserimenti tramite le funzioni apposite
			switch(what) {
				// P: Nome --> Genere persona --> Date (se presenti)
				case 'P':
							if(!(in >> nome)) throw "Errore in lettura nome";
							if(!(in >> kind)) throw "Errore in lettura genere";

							//Lettura delle date (se esistenti)
							if(!(in >> data)) throw "Errore in lettura data di nascita";
							birth = convertDateForInsert(data);
							if(!(in >> data)) throw "Errore in lettura data di morte";
							death = convertDateForInsert(data);					

							// Aggiunta persona
							addPerson(g, nome, kind, birth, death);
							break;
				// P: Nome 1 --> Relazione --> Nome 2
				case 'R':	
							if(!(in >> nome)) throw "Errore in lettura primo nome";
							if(!(in >> kind)) throw "Errore in lettura tipo relazione";
							if(!(in >> nome2)) throw "Errore in lettura secondo nome";
							if(kind == 'M') addRelMother(g, nome, nome2);
							else if(kind == 'F') addRelFather(g, nome, nome2);
							else if(kind == 'C') addRelCouple(g, nome, nome2);
							else throw "Tipo relazione non valido";
							break;

				default: throw "Tipo di azione non valido";
			}
		}	
		return true;	
	}
	catch(const char* err) {
		std::cerr << err << std::endl;
		return false;
	}
}

// Ausiliaria per leggere una persona da stdin con i suoi campi
bool addPersonFromCin(Genogram& g) {
	// Variabili ausiliarie
	char choice;
	std::string isdate, nome;
	int dd, m, y;
	Date birth, death;
	birth = death = EMPTYDATE;

	std::cout << "Inserisci il nome della persona: ";
	std::cin >> nome;
	// Inserimento (con controllo) del genere della persona
	std::cout << "\nInserisci il sesso della persona [M] [F]: ";
	std::cin >> choice;
	if(isError()) return false;

	// Inserimento data di nascita
	std::cout << "\nScrivi [si] se vuoi inserire la data di nascita: ";
	std::cin >> isdate;
	if(isdate == "si") {
		if(!readDateCin(dd, m, y)) return false;
		birth = createDate(y, m, dd);
		// Effettuo qui il controllo della data poichè potrebbe esistere atomica
		if(!verifyDate(birth)) return false;
	}

	// Inserimento data di morte
	std::cout << "\nScrivi [si] se vuoi inserire la data di morte: ";
	std::cin >> isdate;
	if(isdate == "si") {
		if(!readDateCin(dd, m, y)) return false;
		death = createDate(y, m, dd);
		// Effettuo qui il controllo della data poichè potrebbe esistere atomica
		if(!verifyDate(death)) return false;
	}
	
	// Aggiunta della persona tramite le funzioni del TDD
	return addPerson(g, nome, choice, birth, death);
}

// Funzione di utility per stampare i dati di una persona
void printPersonData(Genogram g) {
	std::cout << (g->elem).name;

	if((g->elem).sex == M) std::cout << " M ";
	else std::cout << " F ";

	std::cout << "nato/a: ";
	if(printDate((g->elem).birth))
		std::cout << " ";

	std::cout << "morto/a: ";
	printDate((g->elem).death);

	std::cout << "\nmadre: ";
	if(!isEmpty(g->mother)) std::cout << ((g->mother)->elem).name;
	std::cout << "\npadre: ";
	if(!isEmpty(g->father)) std::cout << ((g->father)->elem).name;
}

// Funzione di utility per la stampa dei nodi non visitati
void printNotVisited(Genogram g) {
	for(; !isEmpty(g); g = g->next) {
		if(!g->visited) {
			// Stampo i dati della persona
			printPersonData(g);

			// Stampa del partner
			std::cout << "\nin coppia con: ";
			if(!isEmpty(g->partner))
				std::cout << ((g->partner)->elem).name;

			// Stampa dei figli
			std::cout << "\nfigli: ";
			halfEdge* e = g->children;
			while(!isEmptyEdge(e)) {
				std::cout << (e->ptr->elem).name << " ";
				e = e->next;
			}
			std::cout << std::endl << std::endl;
		}
	}
}

// Funzione di stampa formattata del genogramma
/*
	Come stampa del genogramma, si sceglie di implementare una BFS
	(breadth-first search) per poter stampare in ampiezza (il più
	possibile a livelli). L'algoritmo si compone delle seguenti fasi:
	
	1) cerco i nodi che non hanno genitori e li aggiungo alla queue (+ visited); in
		questo modo procedo su tutti i sotto-genogrammi (anche se sconnessi)
	2) finchè la queue non e' vuota...
	2.1) dequeue di u
	2.2) stampo u con la corretta formattazione:
	2.2.1) accodo prima il partner (se non visitato)..
	2.2.2) .. e poi accodo i figli (se non visitati)
	3) coda vuota: esco

	4) Gestione caso limite di presenza di cicli sconnessi 
	(si sceglie di stamparli comunque in fondo)
*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void printGenogram(Genogram g) {
	// Rendo i vertici non visitati e inizializzo la coda
	makeNotVisited(g);
	Queue q = queue::createEmpty();
	Genogram aux = g;

	// Visito e aggiungo i nodi alla prima generazione
	while(!isEmpty(g)) {
		if(isEmpty(g->mother) && isEmpty(g->father)) {
			g->visited = true;
			enqueue(g, q);
		}
		g = g->next;
	}

	// Finchè la coda e' piena: procedo con la visita
	while(!isEmpty(q)) {
		g = dequeue(q);

		// Stampo i dati della persona
		printPersonData(g);

		// Visito il partner (contestuale alla stampa per ottimizzare):
		// 1) lo stampo (se esiste) 2) se non visitato lo aggiugo e marco
		std::cout << "\nin coppia con: ";
		if(!isEmpty(g->partner)) {
			// Stampa
			std::cout << ((g->partner)->elem).name;
			// Aggiunta e marcatura
			if(!g->partner->visited) {
				g->partner->visited = true;
				enqueue(g->partner, q);
			}
		}

		// Visito i suoi figli:
		// 1) li stampo ; 2) se non visitati li aggiungo e marco --> ottimizz.
		std::cout << "\nfigli: ";
		halfEdge* e = g->children;
		while(!isEmptyEdge(e)) {
			// Stampa
			std::cout << (e->ptr->elem).name << " ";
			// Aggiunta e marcatura
			if(!e->ptr->visited) {
				e->ptr->visited = true;	
				enqueue(e->ptr, q);
			}
			e = e->next;
		}
		std::cout << std::endl << std::endl;
	}

	// Caso limite di genogramma con presenti dei cicli sconnessi
	printNotVisited(aux);
}
