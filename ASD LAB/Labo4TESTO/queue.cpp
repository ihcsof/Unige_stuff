#include "queue.h"

using namespace queue;

struct queue::cell {
	Elem info;
	cell* next;
};

/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

Queue queue::createEmpty() {
	Queue q;
	q.head = q.tail = EMPTYQUEUE;
	return q;
}

bool queue::isEmpty(const Queue& q) {
	return (q.head == EMPTYQUEUE);
}

void queue::enqueue(Elem e, Queue& q) {
	cell* aux = new cell;
	aux->info = e;
	aux->next = EMPTYQUEUE;
	
	if(isEmpty(q))
		q.head = aux;
	else	
		q.tail->next = aux;

	q.tail = aux;
}

Elem queue::dequeue(Queue& q) {
	if(isEmpty(q)) 
		return EMPTYELEM;
	
	cell* tmp = q.head;
	Elem toRet = tmp->info;
	q.head = q.head->next;
	delete tmp;

	if(isEmpty(q))
		q.tail = EMPTYQUEUE;

	return toRet;
}
