#include <iostream>

#include "bitVector.h"

using namespace bit;

int main() {
	bitV v = create(16);
	
	insertElem(3, v);
	insertElem(13, v);
	insertElem(0, v);
	insertElem(9, v);
	insertElem(2, v);
	insertElem(3, v);
	insertElem(15, v);

	printB(v);

	deleteElem(13, v);
	deleteElem(6, v);

	printB(v);
	std::cout << std::endl;
	
	bitV v2 = create(16);

	std::cout << std::boolalpha << isEmpty(v) << std::endl;
	std::cout << isEmpty(v2) << std::endl;

	int s = size(v);
	std::cout << "Size: " << s << std::endl;

	std::cout << "Is 10 member of v? " << member(10, v) << std::endl;
	std::cout << "Is 15 member of v? "<< member(15, v) << std::endl;

	insertElem(0, v2);
	insertElem(9, v2);
	insertElem(2, v2);

	std::cout << "Print ti v2 dopo inserimenti: \n";
	printB(v2);
	std::cout << "is v2 subset of v1? " << isSubset(v2, v) << "\n";
	std::cout << "is v1 subset of v2? " << isSubset(v, v2) << "\n";
	std::cout << "is v1 subset of v1? " << isSubset(v, v) << "\n";

	bitV v4 = v & v2;
	std::cout << "v & v2 \n";
	printB(v4);

	bitV v5 = (v & v2) | v2;
	std::cout << "(v & v2) | v2\n";
	printB(v5);

	bitV v6 = (v & v) | v2;
	std::cout << "(v & v) | v2\n";
	printB(v6);
}
