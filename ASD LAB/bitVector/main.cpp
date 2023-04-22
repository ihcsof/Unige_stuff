#include <iostream>

#include "bitVector.h"

using namespace bit;

int main() {
	char c = 177;
	bitV v = toBin((char*)&c, sizeof(c));
	printB(v);
	std::cout << "\n";
	print(v);
	std::cout << "\n";

	v = ~v;
	std::cout << "v: ";
	printB(v);
	std::cout << "\n";
	print(v);

	char d = 233;
	bitV v2 = toBin((char*)&d, sizeof(d));
	std::cout << "v2: ";
	printB(v2);
	
	//NB: mem leak! NON USARE OPERATORI SU SE STESSI
	//v2 = v2 & v;

	bitV v3;
	v3 = v2 & v;
	printB(v3);

	bitV v4;
	v4 = v2 | v;
	printB(v4);

	bitV v5;
	v5 = v2 - v;
	printB(v5);

	bitV v6 = create(10);
	insertElem(3, v6);
	insertElem(5, v6);
	insertElem(6, v6);
	deleteElem(4, v6);
	deleteElem(5, v6);
	print(v6);
	int s = size(v6);
	std::cout << "size: " << s << "\n";
	std::cout << "isEmpty?: " << isEmpty(v6) << "\n";
	std::cout << "is 3 member: " << member(3, v6) << "\n";
	std::cout << "is 4 member: " << member(4, v6) << "\n";

	bitV v7 = create(11);
	insertElem(3, v7);
	insertElem(5, v7);
	insertElem(6, v7);
	std::cout << "is v6 subset of v7: " << isSubset(v6, v7) << "\n";
	std::cout << "is v7 subset of v6: " << isSubset(v7, v6) << "\n";
	
	bitV v8 = create(32);
	insertElem(28, v8);
	insertElem(30, v8);
	unsigned int x = toInt(v8);
	std::cout << "v8 to Int " << x << "\n";
}
