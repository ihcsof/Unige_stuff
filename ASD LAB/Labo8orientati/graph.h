#include <iostream>
#include <istream>
#include "list.h"

using namespace std;

namespace graph {

	typedef int Label;

	struct vertexNode;
	typedef vertexNode* Graph;

	const Graph emptyGraph = nullptr; 

	Graph createEmptyGraph();
	void createVertex(Graph&, list::Elem);
	bool isPath(graph::Graph&, list::List &);
}	

void printGraph(const graph::Graph&);
void leggi(istream&, graph::Graph&);

