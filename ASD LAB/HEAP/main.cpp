#include <iostream>
#include "heap.h"

using namespace heap;

int main() {
	array h = createEmpty();
	
	for(int i=0; i<10; ++i)
		insertElem(i, h);
	insertElem(-1, h);

	print(h);
	deleteMax(h);
	print(h);
	deleteMax(h);
	print(h);
	deleteMax(h);
	print(h);
	deleteMax(h);
	print(h);
	deleteMax(h);
	print(h);
	deleteMax(h);
	print(h);
}
