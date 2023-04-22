#ifndef LIST_H
#define LIST_H
//#define BasicDataType
#include <iostream>
#include "BasicDataType.h"

struct cell {
	DataType payload;
	cell* next;
};

typedef cell* basic_list;

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
bool remove(basic_list& list, DataType to_be_removed, bool all_occurrences);

/*
 * It prints on output_stream all the elements in list
 */
void print_list(std::ostream& output_stream, basic_list list);

/*
* It reads values from input_stream and store them into list
* list is initialized by this function, any previous value will be lost 
*/
void read_list(std::istream& input_stream, basic_list& list);

/*
 * Release all the memory allocated to list
 */
void delete_list(basic_list& list);
#endif
