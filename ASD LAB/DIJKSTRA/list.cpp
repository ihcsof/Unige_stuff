// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

/*
	GRUPPO 10
	---------
	Gianì Lorenzo 5008434 (progettazione)
	Pastorelli Patrick 5038958 (implementazione)
	Foschi Lorenzo 4989646 (testing)
																 */

#include "list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

/* stampa la lista */
void printList(const List& l) {
	cout << endl;
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next; 
    }
	cout << endl;
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

List list::createEmpty() {
	// Imposto la lista
   List l = new node;
	l->next = l;
	l->prev = l;
	return l;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List& l) {
	node* aux = new node;
	aux->info = e;
	// Salto dummy. Ora aux punta o al primo elem o a dummy stesso
	aux->next = l->next;
	// Il prev della nuova cella punta al dummy
	aux->prev = l;
	// l->next->prev esiste in ogni caso: punta ad aux
	l->next->prev = aux;
	// Il next del dummy deve puntare al nuovo elemento
	l->next = aux;
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e,  const List& l) {
	// Preparo la cella
   node* aux = new node;
	aux->info = e;
	// Collego l'ultimo elemento della lista ->next ad aux
	l->prev->next = aux;
	// Collego il prev del nuovo elemento al preced. ultimo elemento
	aux->prev = l->prev;
	// Il next del nuovo elemento deve "tornare indietro"
	aux->next = l;
	// Il precedente della sentinella punta all'ultimo
	l->prev = aux;
}
/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List& l) {
 	return(l->next == l);
}


