#include "avl.h"
#include <cmath>
#include <fstream>

using namespace avl;

int main() {
	AVL a;
	createEmpty(a);

	/*insert(a, 7);
	insert(a, 8);
	insert(a, 5);
	insert(a, 9);
	insert(a, 7);
	insert(a, 10);
	insert(a, 2);
	insert(a, 3);
	deleteAvl(a, 5);	
	deleteAvl(a, 7);
	deleteAvl(a, 999999);
	deleteAvl(a, 999999);
	deleteAvl(a, 999999);
	deleteAvl(a, 999999);
	deleteAvl(a, 11);
	deleteAvl(a, 11);*/
	
	std::ifstream chiola;
	chiola.open("file.txt");
	int n, i = 0;
	while(chiola >> n) {
		insert(a, n);
		//std::cout << i++ << std::endl;
		//printAvl(a);
	}

	chiola.close();
	std::ifstream chiola2;
	chiola2.open("file.txt");
	deleteAvl(a, 999999);
	deleteAvl(a, 999999);
	deleteAvl(a, 999999);
	while(chiola2 >> n) {
		deleteAvl(a, n);
		//printAvl(a);
		//std::cout << std::endl;
		//getchar();
	}

	/*int n = 1;
	while(n != 0) {
		std::cin >> n;
		if(n != 0) {
			insert(a, n);
			printAvl(a);
			getchar();
		}
	}*/

	printAvl(a);
	std::cout << std::endl;
}


