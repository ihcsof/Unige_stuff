#include "token.h"

using namespace std;

// Implementa QUEUE con strutture indicizzate e tipo base Elem dotato di ordinamento
 
namespace queue{

typedef token Elem;      // tipo base 

struct cell;

struct Queue {
   cell* head;
	cell* tail;
};


const token EMPTYELEM = {"\0",SCONOSCIUTO};
cell* const EMPTYQUEUE = nullptr;

Queue createEmpty();         /* restituisce la coda vuota */
bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);  /* inserisce l'elemento "da una parte" della coda */
Elem dequeue(Queue&);        /* cancella l'elemento (se esiste) "dall'altra parte della coda" e lo restituisce; se la coda è vuota la condizione è di errore. Lo segnaliamo restituendo EMPTYELEM (potremmo in alternativa sollevare un'eccezione) */

}
