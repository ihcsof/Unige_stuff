#include "graph.h"

using namespace graph;

int main() {
	Graph a = createEmptyGraph();
	leggi(std::cin, a);
	printGraph(a);
	
	list::List l = list::createEmpty();
	addRear(2, l);
	addRear(1, l);
	addRear(0, l);

	list::List l1 = list::createEmpty();
	addRear(0, l1);
	addRear(1, l1);
	addRear(2, l1);
	addRear(0, l1);

	if(isPath(a, l)) std::cout << "c'è l";
	if(isPath(a, l1)) std::cout << "c'è l1";
}
