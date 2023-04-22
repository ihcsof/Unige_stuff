// Implementazione con puntatore a head/tail delle code
// { Da laboratorio ASD realizzato durante l'anno }

#include "queue.h"

using namespace queue;

// Implementazione della struttura base della queue
struct queue::cell {
	Elem content;
	cell* next;
};

struct queue::aux {
	cell* head;
	cell* tail;
};

/******************* Crea una queue vuota ***********************/
Queue queue::createEmpty() {
	Queue q = new aux;
	q->head = q->tail = EMPTYQUEUE;
	return q;
}

/************** Controlla se la queue e' vuota *******************/
bool queue::isEmpty(const Queue& q)
{
	/* Data la struttura e l'implementazione della coda, se uno
	dei due puntatori e' vuoto, allora sono vuoti entrambi */
	return (q->head == EMPTYQUEUE); 
}

/********** Aggiunge un elemento in fondo alla queue ************/
// <-- [][][] <---
void queue::enqueue(Elem e, Queue& q)
{
	// Creazione nuova cella
	cell* newCell = new cell;
	newCell -> content = e;
	newCell -> next = EMPTYQUEUE;
	
	if(isEmpty(q))
		q->head = newCell;
	else	// Queue non vuota
		q->tail->next = newCell;

	// Sposto il puntatore - indice alla nuova cella inserita
	q->tail = newCell;
}

/******* Elimina un elemento dalla testa della queue ************/
// <-- [][][] <---
Elem queue::dequeue(Queue& q) {
	if(isEmpty(q)) 
		return gen::EMPTYGEN;
	
	// Creazione cella ausiliaria per l'eliminazione
	cell* aux = q->head;
	// Salvataggio elemento da ritornare
	Elem elem = aux->content;
	
	// Sposto il puntatore - indice di inizio queue
	q->head = q->head->next;
	// Deallocazione della cella
	delete aux;

	if(isEmpty(q))
		q->tail = EMPTYQUEUE;

	return elem;
}
