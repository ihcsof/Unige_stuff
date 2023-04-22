// Set di utils per la lettura
// readUtility.cpp (Lorenzo Foschi - 4989646)

#include "readUtility.h"

#include <iostream>

using namespace std;

// Menù di scelta per permettere all'utente di selezionare le operazioni
// Funzione menu di scelta con controlli sul buffer
int menu() 
{
  int scelta = -1;
  for(;;)
  { 
    cout << "--------------------------------------------------------------------------\n";
    cout << "                                  MENU                                    \n";
    cout << "--------------------------------------------------------------------------\n";
    cout << "1. Inserimento del genogramma da file\n";
    cout << "2. Inserimento persona nel genogramma\n";
    cout << "3. Inserimento della relazione madre\n";
    cout << "4. Inserimento della relazione padre\n";
    cout << "5. Inserimento della relazione coppia\n";
    cout << "6. Inserimento della relazione figlio ad una coppia\n";
    cout << "7. Setta data di nascita\n";
    cout << "8. Setta data di morte\n";
    cout << "9. Cancella persona\n";
    cout << "10. Controlla validita' del genogramma\n";
    cout << "11. Stampa del genogramma\n";
	 cout << "12. Controllo di esistenza\n";
    cout << "0. Uscita\n";
    cout << "\nFornisci la tua scelta ---> ";
    cin >> scelta;
    cin.ignore();
    cout << "\n--------------------------------------------------------------------------\n";
    if (cin.fail()) {
        cout << "\nScelta non valida\n";
        cin.clear();
        cin.ignore();
        clearerr(stdin);
		  continue;
    }
    return scelta;
  }
}

// Ausiliaria per pulizia buffer e verifica errori
// Si evitano stampe multiple del menu e altri errori del buffer
/*
	Caso di inserimento di char: se inserisco "ciao" invece che un char sono
	presenti nel buffer char non validi, che generano la ristampa del menu
	n volte con n = size della str inserita --> Pulisco il buffer.
	
	Caso di inserimento di "ciao" all'atto della lettura della data: il tipo
	è diverso e cin va in stato di errore: oltre a pulire il buffer tolgo
	anche lo stato di errore dal cin.
*/
bool isError() {
	// Se i bit di stato sono impostati ad errore:
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		clearerr(stdin);
		return true;
	}
	// Svuoto in ogni caso il buffer per pulire eventuali char non validi
	cin.ignore(100, '\n');
	return false;
}
