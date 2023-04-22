#include "graph.h"

using namespace std;
using namespace graph;
using namespace list;

struct halfEdge {
	vertexNode* ptr;
	halfEdge* next = nullptr;
};

struct graph::vertexNode {
	Label label;
	halfEdge* edges = nullptr;
	vertexNode* next;
	bool visited = false;
};

Graph graph::createEmptyGraph() {	
	return emptyGraph;
}

// Ausiliaria
void graph::createVertex(Graph& h, Elem e) {
	Graph g = new vertexNode;
	g->label = e;
	g->next = h;
	h = g;
}

void printGraph(const Graph& g) {
	Graph aux = g;
	// Ciclo su ogni vertice
	for(; aux; aux = aux->next) {
		cout << aux->label << " : ";
		halfEdge* e = aux->edges;
		// Ciclo su ogni mezz'arco
		for(; e; e = e->next)
			cout << "(" << e->ptr->label << ")";
		cout << endl;
	}
}

// Ausiliaria
void createEdge(Graph& from, Graph& to) {
	halfEdge** e = &(from->edges);
	for(; *e; e = &((*e)->next));
	*e = new halfEdge;
	(*e)->ptr = to;
	if(!from->edges) std::cout << "bella";
}

void leggi(istream& in, Graph& g) {
	Graph* aux = &g;
	int ero;
	bool eano;
	in >> ero;
	// Ciclo di aggiunta dei nodi con card. = num letto
	for(int i = 0; i < ero; ++i) {
		createVertex(*aux, i);
		aux = &((*aux)->next);
	}
	Graph aux2 = g;
	// Cicli innestati per inserire riga x riga (if(1) addEdge)
	for(int i = 0; i < ero; ++i) {
		Graph tmp = g;
		for(int j = 0; j < ero; ++j) {
			in >> eano;
			if(eano)
				createEdge(aux2, tmp);
			tmp = tmp->next;
		}
		aux2 = aux2->next;
	}
}

// Ausiliaria
Graph getVertex(const Label l, Graph g) {
	for(; g; g = g->next)
		if(g->label == l) return g;
	return emptyGraph;
}

// isPath RICORSIVA

/*bool isPathAux(Graph& a, list::List &l, list::List &laux) {
	if(l == laux) return true;
	for(halfEdge* e = a->edges; e; e = e->next)
		if(e->ptr->label == l->info)
			return isPathAux(e->ptr, l->next, laux);
	return false;
}

bool isPath(Graph& a, list::List &l) {
	Graph first = getVertex(l->next->info, a);
	if(!first) return false;
	return isPathAux(first, l->next->next, l);
}*/

//---------------------------------------------------------------

// isPath ITERATIVA
/*
	Partendo dal primo nodo (se esiste), ciclo sui suoi edges:
	fino alla fine degli edges AND del path (basta che finisca
	uno dei due per uscire, poi mi chiedo se sono uscito per la fine
	del path (-->true) o degli edges (-->false).
	Dentro il ciclo, se trovo la label, mando avanti il path e passo
	al prossimo nodo, sennò continuo a ciclare il path (lista di adiacenza)
*/

bool graph::isPath(Graph& a, list::List &l) {
	list::List laux = l->next;
	Graph aux = getVertex(laux->info, a);
	if(!aux) return false;
	laux = laux->next;
	halfEdge* e = aux->edges;
	while(laux != l && e) {
		if(e->ptr->label == laux->info) {
			laux = laux->next;
			e = e->ptr->edges;
			continue;
		}
		e = e -> next;
	}
	return l == laux;
}
