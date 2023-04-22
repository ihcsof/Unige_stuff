#include <iostream>

#include "BasicList.h"

bool lst::isEmpty(basic_list& list) {
	return(list == emptyList);
}

void lst::head_insert(basic_list& list, DataType new_value) {
	cell* aux = new cell;
	aux->payload = new_value;
	if (isEmpty(list)) 
		aux->next = aux;
	else 
		{cell* tmp = list;
		 while (tmp->next != list)
			tmp = tmp->next;
		tmp->next = aux;
		aux->next = list;
		}
    
    list = aux;
}


void lst::print_listOLD(std::ostream& output_stream, basic_list list) {
	cell* aux = list;
	while (!isEmpty(aux)) {
		WriteData(output_stream, aux->payload);
		aux = aux->next;
		output_stream << std::endl;
	}
}


void lst::print_list(std::ostream& output_stream, basic_list list) {
	if (!isEmpty(list))
	{	
		cell* aux = list;
		while (aux->next != list) {
			WriteData(output_stream, aux->payload);
			aux = aux->next;
			output_stream << std::endl;
		}
		WriteData(output_stream, aux->payload);
	}
}

void lst::read_list(std::istream& input_stream, basic_list& list) {
	list = emptyList;
	DataType d;
	while (ReadData(input_stream, d)) {
		head_insert(list, d);
	}
}