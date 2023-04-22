// header per implementazione con puntatore a head/tail delle code
// { Da laboratorio ASD realizzato durante l'anno }

#include "genogramma.h"
 
namespace queue {

// Tipo base degli elementi della queue
// Si usano i puntatori per maggiore efficienza: ma con information hiding
typedef gen::Genogram Elem;

// Definizione struttura base della queue
struct cell;
struct aux;

// Opaque pointer
typedef aux* Queue;

cell* const EMPTYQUEUE = nullptr;

// Creazione di una coda vuota
Queue createEmpty();
// Check se la coda è vuota
bool isEmpty(const Queue&);
// Inserimento nella coda
void enqueue(Elem, Queue&);
// Estrazione dalla coda
Elem dequeue(Queue&);

}
