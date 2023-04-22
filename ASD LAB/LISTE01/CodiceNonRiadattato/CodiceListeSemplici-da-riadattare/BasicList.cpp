#include <iostream>

#include "BasicList.h"


void head_insert(basic_list& list, DataType new_value) {
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
bool remove(basic_list& list, DataType to_be_removed, bool all_occurrences) {
	cell* aux = list;
	cell* prev = nullptr;
	while (aux != nullptr&&DataComparer(aux->payload, to_be_removed) != 0) {
		prev = aux;
		aux = aux->next;
	}
	if (aux == nullptr)
		return false;
	//aux is pointing to the element to be removed
	if (prev == nullptr) //removing the head of the list
		list = aux->next;
	else
		prev->next = aux->next;
	delete(aux);
	if (all_occurrences)
		if (prev == nullptr)
			remove(list, to_be_removed, all_occurrences);
		else
			remove(prev->next, to_be_removed, all_occurrences);
	return true;
}

void print_list(std::ostream& output_stream, basic_list list) {
	cell* aux = list;
	while (aux != nullptr) {
		WriteData(output_stream, aux->payload);
		aux = aux->next;
		output_stream << std::endl;
	}
}


void read_list(std::istream& input_stream, basic_list& list) {
	list = nullptr;
	DataType d;
	while (ReadData(input_stream, d)) {
		cell* aux = new cell;
		aux->payload = d;
		aux->next = list;
		list = aux;
	}
}

void delete_list(basic_list& list) {
	cell* aux = list;
	while (aux != nullptr) {
		list = aux->next;
		delete(aux);
		aux = list;
	}
}