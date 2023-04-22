#ifndef BITV_H
#define BITV_H

#include <cstdlib>

// BIT SET CON UNSIGNED

namespace bit {

	typedef char elem;

	struct bitV {
		elem* data;	
		int size;
		int nData;
	};

	bitV create(int);
	void insertElem(int, bitV&);
	void deleteElem(int, bitV&);
	bool isSubset(const bitV&, const bitV&);
	bool isEmpty(const bitV&);
	int size(const bitV&);
	bool member(int, const bitV&);
	void printB(const bitV&);

	bitV operator & (const bitV&, const bitV&);
	bitV operator | (const bitV&, const bitV&);
}

#endif
