#include "stack.h"

using namespace stack;


struct stack::cell {
    Elem	elem;
    cell	*next;
};


/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
	return(s == EMPTYSTACK);
}


/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
	 // Creo una nuova cella, la aggiungo in testa
    cell* newElem = new cell;
	 newElem->elem = x;
	 newElem->next = s;
	 s = newElem;
}

/****************************************************************/
Elem stack::pop(Stack& s)
{
	// Se lo stack è vuoto
   if(isEmpty(s))
		throw "Errore: lista vuota";
	// Salvo l'elemento, salto di una posizione, elimino e ritorno il suddetto
	Stack tmp = s;
	Elem toRet = s->elem;
	s = s->next;
	delete tmp;
	return toRet;
}


/****************************************************************/
Elem stack::top(Stack& s)
{
	 // Se lo stack è vuoto, ritorno EMPTYELEM (si poteva lanciare eccezione)
	 if(isEmpty(s)) return EMPTYELEM;
	 // Ritorno l'elemento in cima
    return(s->elem);
}
