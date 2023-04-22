/*
	genogramma.h (Lorenzo Foschi - 4989646)
	Descrizione dell'interfaccia del tipo Genogram:
	Interno del namespace gen (specifica del tipo Genogram):
		- struct con forward declaration per principio di information hiding. 

		- contestuale typedef di node* (puntatore a node): Genogram 

		- enum gender per la distinzione di sesso tra due persone

		- typedef del tipo stringa come Label

		- costante EMPTYGEN inizializzata a nullptr
	
		- Funzioni esposte:
		
			createEmpty; isEmpty; isIn; isValid

			setBirth; setDeath

			addPerson ; addRelMother; addRelFather; addRelCouple; addRelChildToCouple

			deletePerson; clearGen

	Esterno al namespace:
	
 		readFromFile; printGenogram; addPersonFromCin

	NB: si sceglie di includere negli header solamente le librerie strettamente necessarie,
			onda evitare la loro inclusione incondizionata in ogni file che includa a sua volta
			l'header stesso.
*/

#ifndef GEN_H
#define GEN_H

#include <iostream>
#include <string>
#include "data.h"
#include "readUtility.h"

namespace gen {
	
	// struct e dichiarazioni (v. sopra per dettagli):
	struct node;
	
	typedef node* Genogram;

	enum gender {M, F};

	typedef std::string Label;

	const Genogram EMPTYGEN = nullptr;

	// Funzione di creazione di un Genogramma vuoto
	Genogram createEmpty();

	// Funzione per verificare se un Genogramma e' vuoto
	bool isEmpty(const Genogram&);

	// Funzione per verificare se una persona è nel genogramma
	bool isIn(const Genogram& g, Label l);

	// Funzioni per settare le date di nascita e morte
	bool setBirth(const Genogram&, Label, int, int, int);

	bool setDeath(const Genogram&, Label, int, int, int);

	// Funzione di aggiunta di una persona al genogramma (no relazioni)
	bool addPerson(Genogram&, Label, char, period::Date, period::Date);

	// Funzione per cancellare un genogramma
	void clearGen(Genogram&);

	// Funzione di aggiunta di una relazione "madre"
	bool addRelMother(const Genogram&, Label, Label);

	// Funzione di aggiunta di una relazione "padre"
	bool addRelFather(const Genogram&, Label, Label);

	// Funzione di aggiunta di una relazione "coppia"
	bool addRelCouple(const Genogram&, Label, Label);

	// Funzione di aggiunta di una relazione "figlio alla coppia"
	bool addRelChildToCouple(const Genogram&, Label, Label, Label);

	// Funzione di cancellazione di una persona
	bool deletePerson(Genogram&, Label);

	// Funzione per verificare se il genogramma e' valido
	bool isValid(const Genogram&, std::string&);
}

// Funzione di lettura da file
bool readFromFile(std::string, gen::Genogram&);

// Funzione di stampa del genogramma
void printGenogram(gen::Genogram);

// Ausiliaria per leggere una persona da stdin con i suoi campi
bool addPersonFromCin(gen::Genogram&);

#endif
