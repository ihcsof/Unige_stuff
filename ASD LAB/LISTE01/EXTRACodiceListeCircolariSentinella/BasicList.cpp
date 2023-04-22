#include <iostream>

#include "BasicList.h"

void lst::create_empty(basic_list& list)
{
   cell* aux = new cell;
   aux->next = aux;
   list = aux;
}

void lst::head_insert(basic_list& list, DataType new_value) {
	cell* aux = new cell;
	aux->payload = new_value;
	aux->next = list->next;
	list->next = aux;
}


void lst::print_list(std::ostream& output_stream, basic_list list) {
	cell* aux = list->next; // devo saltare la sentinella
	while (aux != list) {
		WriteData(output_stream, aux->payload);
		aux = aux->next;
		output_stream << std::endl;
	}
}

void lst::read_list(std::istream& input_stream, basic_list& list) {
	// list = emptyList;
	create_empty(list); // non posso usare list = emptyList; sono liste con sentinella!!!
	DataType d;
	while (ReadData(input_stream, d)) {
		head_insert(list, d);
	}
}

bool lst::is_in(const basic_list &list, DataType x) {
	cell* aux = list->next;
	while (aux != list) {
		if(!DataComparer(aux->payload,x))
			return true;
		aux = aux->next;
	}
	return false;
}

//concat con copia profonda
lst::basic_list lst::concatNew(const basic_list &first, const basic_list &second) {
	basic_list toReturn;
	create_empty(toReturn);
	//Creo puntatore ausiliario e copio gli elementi di first
	cell* aux = first->next;
	while (aux != first) {
		head_insert(toReturn,aux->payload);
		aux = aux->next;	
	}
	//Creo puntatore ausiliario e copio gli elementi di second
	cell* aux2 = second->next;
	while (aux2 != second) {
		head_insert(toReturn,aux2->payload);
		aux2 = aux2->next;	
	}

	return toReturn;
}

//concat che sovrascrive (diventano "una sola") IN PLACE
//-->second non avrà più senso
void lst::concat(const basic_list &first, basic_list &second) {
	//Creo puntatore ausiliario e arrivo alla quasi fine della first
	cell* aux = first->next;
	while (aux->next != first)
		aux = aux->next;	
	//Invece che "tornare" alla testa attacco al primo vero elem di second
	aux->next = second->next;
	//Creo puntatore ausiliario
	cell* aux2 = second->next;
	//arrivo alla quasi fine della second
	while (aux2->next != second)
		aux2 = aux2->next;
	//torno alla testa
	aux2->next = first;
	//Cancello la dummy di second e "invalido second"
	delete second;
	second = nullptr;
}

//delete (mantiene il dummy intatto)
void lst::delete_list(basic_list& list) {
	cell* aux = list->next;
	cell* next = list->next;
	while (next != list) {
		next = aux->next;
		delete(aux);
		aux = next;
	}
	list->next = list;
}