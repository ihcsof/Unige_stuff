/*
	data.h (Lorenzo Foschi - 4989646)

	Descrizione dell'interfaccia del tipo Date:
	Funzioni all'intero del namespace period (specifica del tipo Date):
		- struct contenente tre interi. Si sceglie di optare per una definizione della struct
			all'interno dell'header per leggibilità del codice: per effettuare una forward
			declaration come per la struct dei vertici del genogramma si sarebbe reso 
			necessario il meccanismo degli opaque pointer, dovendo definire la struct nel cpp
			in termini di puntatore al tipo Date (cosa che con strutture di tipo Genogram
			avviene per logica di costruzione intrinseca).

		- costante EMPTYDATE inizializzata a {INT_MAX, 0, 0}

		- funzione create di una nuova data dati tre parametri interi e funzione isEmpty

		- operatori overloaded per effettuare le comparazioni tra date con maggiore
			pulizia e riutilizzo del codice. L'operatore x overloaded verrà eseguito al
			posto dell'implementazione standard a livello superiore, grazie alla specifica
			firma differente (caratterizzata da due campi di tipo const Date&).

		- funzione verifyDate per la verifica della validità della data immessa;
			verifica sul range valido dei valori compreso di controllo su anno bisestile

	Funzioni esterne al namespace period:
		- printDate per effettuare una semplice stampa formattata su standard output
		- readDateCin per leggere da stdin una data

	NB: si sceglie di includere negli header solamente le librerie strettamente necessarie,
			onda evitare la loro inclusione incondizionata in ogni file che includa a sua volta
			l'header stesso.
*/

#ifndef D_H
#define D_H

#include <climits>

namespace period {

	// Struct e dichiarazioni (v. sopra per dettagli)
	struct Date {
		int yyyy;
		int mm;
		int dd; 
	};

	const Date EMPTYDATE = {INT_MAX, 0, 0};

	// Interfaccia funzioni (v. sopra per dettagli)

	Date createDate(int, int, int);

	bool isEmpty(const Date&);

	bool operator == (const Date&, const Date&);
	bool operator != (const Date&, const Date&);
	bool operator > (const Date&, const Date&);
	bool operator >= (const Date&, const Date&);
	bool operator < (const Date&, const Date&);
	bool operator <= (const Date&, const Date&);

	bool verifyDate(const Date&);
}

// FUnzioni di scrittura e lettura fuori dal namespace
bool printDate(const period::Date&);
bool readDateCin(int& dd, int& m, int& y);

#endif
