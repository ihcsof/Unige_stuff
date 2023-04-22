#ifndef LIST_H
#define LIST_H
#define BasicDataType
#include <iostream>

namespace lst {

	struct cell;
	typedef cell* list;
	const list emptyList = nullptr;

	#ifdef BasicDataType
		typedef int data;
	#else
		#define complexTYPE
		typedef struct dummy
		{
			std::string prova;
		} data;
	#endif

	bool isEmpty(list& l);
	void insert_beginning(data x, list &l);
	void insert_end(data x, list &l);
	void clear(list &l);
	void concatInPlace(list &l1, list &l2);
	list concatNew(const list &first, const list &second);
	void print_backward(const list &l);
	void print_backward_rec(list l);
	void set(list &l, int x, data e);
	data get(list &l, int x);
	bool is_in(const list &l, data x);
	bool remove(list& l, data toRemove, bool all_occurrences);
}

//Funzioni fuori namespace (OPERANO su lst)

#ifdef TYPE
bool operator ==(lst::data x, lst::data y);
#endif

lst::list read(std::istream& input);
void write(std::ostream& output, lst::list l);

#endif

