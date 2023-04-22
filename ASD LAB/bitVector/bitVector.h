#ifndef BITV_H
#define BITV_H

#include <cstdlib>

// BIT SET

namespace bit {

	struct bitV {
		int size;
		bool *data;
	};
	
	bitV create(int);
	void insertElem(int, bitV&);
	void deleteElem(int, bitV&);
	bool isSubset(const bitV&, const bitV&);
	bool isEmpty(const bitV&);
	int size(const bitV&);
	bool member(int, const bitV&);
	void printB(const bitV&);
	void print(const bitV&);
	bitV toBin(char*, size_t);
	unsigned int toInt(const bitV&);

	bool operator == (const bitV&, const bitV&);
	bitV operator & (const bitV&, const bitV&);
	bitV operator | (const bitV&, const bitV&);
	bitV operator - (const bitV&, const bitV&);
	bitV operator ~ (const bitV&);
}

#endif
