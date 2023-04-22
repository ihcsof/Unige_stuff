#ifndef LIST_H
#define LIST_H
#define BasicDataType
#include <iostream>
#include "BasicDataType.h"

namespace lst {

	struct cell {
		DataType payload;
		cell* next;
	};

	typedef cell* basic_list;

	// const basic_list emptyList = NULL; /* quando la lista è circolare con sentinella, la lista vuota NON E' rappresentata da NULL ma da una lista con una sola cell il cui next punta a sé stessa; bisogna avere una funzione create_empty che crea tale lista, non si puo' usare una const

	/*
	 * list becomes the empty list (only one cell linked to itself)
	 */
	void create_empty(basic_list& list);

	/*
	 * It insert a new cell containing the new_value at the beginning of the list
	 */
	void head_insert(basic_list& list, DataType new_value);

	/*
	 * It removes the element to_be_removed from the list;
	 * If all_occurrences it is true it removes all the occurrences of to_be_removed in the list,
	 * otherwise it removes just the first occurrency
	 * It returns true iff at least a cell have been removed
	 */
	// bool remove(basic_list& list, DataType to_be_removed, bool all_occurrences);

	/*
	 * It prints on output_stream all the elements in list
	 */
	void print_list(std::ostream& output_stream, basic_list list);

	/*
	* It reads values from input_stream and store them into list
	* list is initialized by this function, any previous value will be lost 
	*/
	void read_list(std::istream& input_stream, basic_list& list);

	bool is_in(const basic_list &list, DataType x);
	basic_list concatNew(const basic_list &first, const basic_list &second);
	void concat(const basic_list &first, basic_list &second);
	void delete_list(basic_list& list);

}

#endif
