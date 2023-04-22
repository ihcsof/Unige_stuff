#include "DoubleList.h"

struct lst::cell {
		list prev;
		data payload;
		list next;
};

bool lst::isEmpty(list& l) {
	return(l == emptyList);
}

void lst::insert_beginning(data x, list &l) {
	cell* aux = new cell;
	aux->payload = x;
	aux->prev = emptyList;
	if(isEmpty(l)) {
		aux->next = emptyList;
		l = aux;
	}
	else {
		l->prev = aux;
		aux->next = l;
		l = aux;
	}
}

void lst::insert_end(data x, list &l) {
	cell* aux = new cell;
	aux->payload = x;
	aux->prev = emptyList;
	aux->next = emptyList;

	list temp = l;
	if(isEmpty(l))
		l = aux;
	else {
		while(!isEmpty(temp->next))
			temp = temp->next;
		temp->next = aux;
		aux->prev = temp;
	}
}

void lst::clear(list &l) {
	cell* aux = l;
	while (!isEmpty(aux)) {
		l = aux->next;
		delete(aux);
		aux = l;
	}
}

//first diventerà la lista completa, second perde senso
void lst::concatInPlace(list &first, list &second) {
	//CASI PARTICOLARI
	if(isEmpty(first)) {
		first = second;
		return;
	}
	if(isEmpty(second))
		return;
	//Creo puntatore ausiliario e arrivo alla quasi fine della first
	cell* aux = first;
	while (!isEmpty(aux->next))
		aux = aux->next;	
	//attacco al primo elem di second
	aux->next = second;
	//collego prev di second
	second->prev = aux;
	//"invalido second"
	second = nullptr;
}

lst::list lst::concatNew(const list &first, const list &second) {
	list toReturn = emptyList;
	cell* aux = first;
	while (!isEmpty(aux)) {
		insert_end(aux->payload, toReturn);
		aux = aux->next;	
	}
	cell* aux2 = second;
	while (!isEmpty(aux2)) {
		insert_end(aux2->payload, toReturn);
		aux2 = aux2->next;	
	}
	return toReturn;
}

void lst::print_backward(const list &l) {
	cell* temp = l;
	if(isEmpty(temp))
		return;
	while(!isEmpty(temp->next))
		temp = temp->next;
	while(!isEmpty(temp)) {
		std::cout << temp->payload << " ";
		temp = temp->prev;
	}
	std::cout << std::endl;
}

void lst::print_backward_rec(list l) {
	if(!isEmpty(l)) {
		print_backward_rec(l->next);
		std::cout << l->payload << " ";
	}
}

void lst::set(list &l, int x, data e) {
	cell* aux = l;
	int i = 0;
	while(!isEmpty(aux) && i<x) {
		i++;
		aux = aux->next;
	}
	if(!isEmpty(aux))
		aux->payload = e;
}

lst::data lst::get(list &l, int x) {
	cell* aux = l;
	int i = 0;
	while(!isEmpty(aux) && i<x) {
		i++;
		aux = aux->next;
	}
	if(!isEmpty(aux))
		return aux->payload;
	else
		throw "elemento non presente";
}

bool lst::is_in(const list &l, data x) {
	cell* aux = l;
	while (!isEmpty(aux)) {
		if(aux->payload == x)
			return true;
		aux = aux->next;
	}
	return false;
}

bool lst::remove(list& l, data toRemove, bool all_occurrences) {
	cell* aux = l;
	cell* prec = emptyList;
	while (!isEmpty(aux) && aux->payload != toRemove) {
		prec = aux;
		aux = aux->next;
	}
	if (isEmpty(aux))
		return false;
	//aux punta ora all'elemento da rimuovere:
	//1: se devo rimuovere la testa
	if (isEmpty(prec)) {
		l = aux->next;
		//DIFFERENZA 1 con la funzione per liste normali
		if(!isEmpty(l))
			l->prev = emptyList;
	}
	else {
		prec->next = aux->next;
		//DIFFERENZA 2 con la funzione per liste normali
		//se non e' l'ultimo elemento devo anche collegare prev
		if(!isEmpty(aux->next))
			(aux->next)->prev = prec;
	}
	delete(aux);
	if (all_occurrences)
		if (isEmpty(prec))
			remove(l, toRemove, all_occurrences);
		else
			remove(prec->next, toRemove, all_occurrences);
	return true;
}

#ifdef complexTYPE //!!! SOLO UNA PROVA !!!

bool operator ==(lst::data x, lst::data y) {
	return x.prova == y.prova;
}

void operator >>(std::istream& input, lst::data x) {
	input >> x.prova;
}

void operator <<(std::ostream& output, lst::data x) {
	output << x.prova;
}

#endif

//!!!! NON SONO FUNZIONI GENERALI !!!!

lst::list read(std::istream& input) {
	if(&input == &std::cin)
		throw 42;
	lst::list toReturn = lst::emptyList;
	lst::data temp;
	while(input >> temp)
		insert_end(temp, toReturn);
	return toReturn;
}

void write(std::ostream& output, lst::list l) {
	while(!isEmpty(l)) {
		output << l->payload << " ";
		l = l->next;
	}
	output << std::endl;
}