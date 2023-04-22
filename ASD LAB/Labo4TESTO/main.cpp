/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////

// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {
	codaToken = queue::createEmpty();
	string aux = str;
	token tok;

	while(aux.size() > 0) {
		if(!prossimoToken(aux, tok))
			return false;
		enqueue(tok, codaToken);
	}

	return true;
}

// Ausiliaria della calcola
bool eval(stack::Stack& s) {
	pop(s); // erodo la parentesi chiusa (ne siamo sicuri)
	token tok[4];
	int res;
	
	try { // try per l'eccezione della pop
		for(int i = 0; i < 4; ++i)
			tok[i] = pop(s);
	}
	catch(const char& err) {
		std::cerr << err << std::endl;
	}

	if(tok[3].k != PARENTESI_APERTA)
		return false;
	
	if(tok[0].k == NUMERO && tok[2].k == NUMERO) {
		switch(tok[1].k) {
			case OP_SOMMA:
				res = str2int(tok[2].val) + str2int(tok[0].val);
				break;
			case OP_SOTTRAZIONE:
				res = str2int(tok[2].val) - str2int(tok[0].val);
				break;
			case OP_MOLTIPLICAZIONE:
				res = str2int(tok[2].val) * str2int(tok[0].val);
				break;
			default:
				return false;
		}

		tok[0].val = int2str(res);
		stack::push(tok[0], s);
		return true;
	}
	
	return false;	
}

// Estrae uno dopo l'altro i token dalla coda, inserendoli via via sullo stack.
// Appena si incontra un token PARENTESI CHIUSA, quello segnala la fine
// di una sottoespressione; allora tiriamo giu' dallo stack gli ultimi cinque token inseriti.
// I token estratti dovrebbero essere esattamente, nell'ordine:
// un ")", un numero, un operatore aritmetico, un altro
// numero, e un "("; se non è così, allora si segnala
// errore sintattico e l'algoritmo termina.
// A questo punto la funzione deve convertire i token di tipo NUMERO in numeri interi, 
// eseguire l'operazione aritmetica opportuna, e trasformare il risultato da numero a
// token e inserire quest'ultimo sullo stack.
// Alla fine se non ci sono errori sintattici la funzione deve mettere nella variabile
// risultato il vaore dell'espressione
bool calcola(queue::Queue codaToken, int &risultato) {
	/*
		Assumiamo che, nel caso limite di un singolo numero,
		non avendo operazioni da compiere, il risultato è
		il numero stesso.
	*/
	stack::Stack aux = stack::EMPTYSTACK;
	token tok;

	while(!isEmpty(codaToken)) {
		tok = dequeue(codaToken);
		push(tok, aux);
		
		if(tok.k == PARENTESI_CHIUSA) {
			if(!eval(aux))
				return false;
		}
	}

	tok = pop(aux);
	try {
		// è un numero? Se si, abbiamo ottenuto il risultato...
		risultato = str2int(tok.val);
	}
	catch(...) {
		return false;
	}
	
	// ...ritorno true però solo se lo stack alla fine è vuoto (conteneva solo il ris)
   return (aux == stack::EMPTYSTACK);
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  cout << "Inserisci l'espressione che vuoi valutare:" << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cout << "errore lessicale\n";
    exit(1);
  }

  if (!calcola(q,r)) {
    cout << "errore sintattico\n";
    exit(1);
  }

  cout << "risultato: " << r << "\n";
  exit(0);
}
