#include <iostream>

#include "BasicList.h"

struct lst::cell {
		DataType payload;
		//lst::cell* next;
		basic_list next;
	};

bool lst::isEmpty(basic_list& list) {
	return(list == emptyList);
}


void lst::head_insert(basic_list& list, DataType new_value) {
	cell* aux = new cell;
	aux->next = list;
	aux->payload = new_value;
	list = aux;
}

/*
* It removes the element to_be_removed from the list;
* If all_occurrences it is true it removes all the occurrences of to_be_removed in the list,
* otherwise it removes just the first occurrency
* It returns true iff at least a cell have been removed
*/
bool lst::remove(basic_list& list, DataType to_be_removed, bool all_occurrences) {
	cell* aux = list;
	cell* prev = emptyList;
	while (!isEmpty(aux) && DataComparer(aux->payload, to_be_removed) != 0) {
		prev = aux;
		aux = aux->next;
	}
	if (isEmpty(aux))
		return false;
	//aux is pointing to the element to be removed
	if (isEmpty(prev)) //removing the head of the list
		list = aux->next;
	else
		prev->next = aux->next;
	delete(aux);
	if (all_occurrences)
		if (isEmpty(prev))
			remove(list, to_be_removed, all_occurrences);
		else
			remove(prev->next, to_be_removed, all_occurrences);
	return true;
}

void lst::print_list(std::ostream& output_stream, basic_list list) {
	cell* aux = list;
	while (!isEmpty(aux)) {
		WriteData(output_stream, aux->payload);
		aux = aux->next;
		output_stream << std::endl;
	}
}


void lst::read_list(std::istream& input_stream, basic_list& list) {
	list = emptyList;
	DataType d;
	while (ReadData(input_stream, d)) {
		cell* aux = new cell;
		aux->payload = d;
		aux->next = list;
		list = aux;
	}
}

void lst::delete_list(basic_list& list) {
	cell* aux = list;
	while (!isEmpty(aux)) {
		list = aux->next;
		delete(aux);
		aux = list;
	}
}