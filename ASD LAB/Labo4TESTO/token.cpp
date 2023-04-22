/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// da stringa a numero
int str2int(const string &s) {
   return std::stoi(s);
}

// da numero a stringa
string int2str(int n) {
   return std::to_string(n);
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
	int pos = s.find(" ", 0);
	string newToken;
	
	if(pos == std::string::npos) {
		newToken = s;
		s.erase(0, s.size());
	}
	else {
		newToken = s.substr(0, pos);
		s.erase(0, pos+1);
	}
	t.val = newToken;
	
	try {
		std::stoi(newToken);
		t.k = NUMERO;	
	}
	catch(...) {
		if(newToken.size() != 1) {
			t.k = SCONOSCIUTO;
			return false;
		}
		
		switch(newToken[0]) {
			case '(':
				t.k = PARENTESI_APERTA;
				break;
			case ')':
				t.k = PARENTESI_CHIUSA;
				break;
			case '+':
				t.k = OP_SOMMA;
				break;
			case '-':
				t.k = OP_SOTTRAZIONE;
				break;
			case '*':
				t.k = OP_MOLTIPLICAZIONE;
				break;
			default:
				t.k = SCONOSCIUTO;
				return false;
		}
	}
	return true;
}

