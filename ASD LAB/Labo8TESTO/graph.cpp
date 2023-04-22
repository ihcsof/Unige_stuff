#include "graph.h"

using namespace graph;

/*******************************************************************************************************/
// Grafo
/*******************************************************************************************************/

// Si sceglie un'implementazione con lista dei vertici ORDINATA

struct halfEdge {
	Weight weight;
	vertexNode* ptr;
	halfEdge* next = nullptr;
};

struct graph::vertexNode {
	Label label;
	halfEdge* edges = nullptr;
	vertexNode* next;
	bool visited = false;
};

// Restituisce il grafo vuoto
Graph graph::createEmptyGraph() {	
	return emptyGraph;
}

// Ausiliaria per addVertex
bool createFirst(Label l, Graph& g) {
	Graph aux = new vertexNode;
	aux->label = l;
	aux->next = g;
	g = aux;
	return true;
}

// Funzione di ausilio per ritornare vertice data label
Graph getVertex(const Label l, Graph g) {
	for(; g && g->label < l; g = g->next);
	if(g && g->label == l) return g;
	return emptyGraph;
}

// Aggiunge nuovo vertice con etichetta la stringa. Fallisce se gia' presente
bool graph::addVertex(Label l, Graph& g) {
	// Caso grafo vuoto o inserimento in testa
	if(isEmpty(g) || l < g->label)
		return createFirst(l, g);
	if(l == g->label) return false;

	Graph aux = g;
	// Ciclo fino al punto corretto (mantengo ordine)
	while(aux->next && aux->next->label < l)
		aux = aux->next;
	// Esiste già; sennò sono nel punto giusto (o alla fine)
	if(aux->next && aux->next->label == l) return false;
	// Creazione e inserimento vertice
	vertexNode* tmp = new vertexNode;
	tmp->label = l;
	tmp->next = aux->next;
	aux->next = tmp;
	return true;
}

void swap(Label& l1, Label& l2) {
	Label tmp = l1;
	l1 = l2;
	l2 = tmp;
}

void createEdge(Weight w, Graph& from, Graph& to) {
	// Creo l'halfEdge verso il vertice to
	halfEdge* edge = new halfEdge;
	edge->weight = w;
	edge->ptr = to;
	// Inserisco l'halfEdge nella lista di adiacenza di from
	edge->next = from->edges;
	from->edges = edge;
}

// Aggiunge un arco di peso "w" tra i nodi con etichetta "f" e "t". Fallisce se esiste gia' l'arco
// se i nodi non esistono nel grafo e se si tenta di inserire un arco tra un nodo ed esso stesso
bool graph::addEdge(Label from, Label to, Weight w, Graph& g) {
	// No cappio
	if(from == to) return false;
	// Assumo che from sia la minore per evitare controlli futuri
	if(from > to) swap(from, to);

	// Ciclo fino a from (tenendo il puntatore perchè potrebbe non esistere to) e poi fino a to:
	Graph aux = getVertex(from, g);
	// Non esiste from (fine lista o elemento maggiore)
	if(!aux) return false;
	
	Graph aux2 = getVertex(to, aux);
	// Non esiste to (fine lista o elemento maggiore)
	if(!aux2) return false;

	// Esistenza arco
	halfEdge* e = aux->edges;
	for(; e; e = e->next)
		if(e->ptr->label == to) return false; 

	createEdge(w, aux, aux2);
	createEdge(w, aux2, aux);
	return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g) { 
 return (g == emptyGraph);
}

// Ritorna il numero di vertici del grafo
int graph::numVertices(const Graph& g) {
	Graph aux = g;
	int i = 0;
	// Conto i nodi della lista di vertici
	for(; aux; i++, aux = aux->next);
	return i;
}

// Ritorna il numero di archi del grafo
int graph::numEdges(const Graph& g) {
 	Graph aux = g;
	int i = 0;
	// Per ogni vertice, aumento il contatore degli archi; ritorno / 2 (non orientato)
	for(; aux; aux = aux->next) {
		halfEdge* e = aux->edges;
		for(; e; i++, e = e->next);
	}
	return (i/2);
}

// Calcola e ritorna (nel secondo parametro) il grado del nodo. Fallisce
// se il nodo non esiste

bool graph::nodeDegree(Label l, int& degree, const Graph& g) {
	// Prendo il vertice corretto (se esiste) e ne calcolo il grado
	degree = 0;
	Graph aux = getVertex(l, g);
	if(!aux) return false;
	halfEdge* e = aux->edges;
	for(; e; degree++, e = e->next);
	return true;
}

// Verifica se i due vertici v1 e v2 sono adiacenti (ovvero se esiste un arco)
// Avendo implement. lista di vertici ordinata, si sceglie di ciclare ...
// ... la minore invece che ciclare in parallelo
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
	// No cappio
	if(v1 == v2) return false;
	// Ottimizz.: chiamo getVertex sulla label minore per ciclare meno
	if(v1 > v2) swap(v1, v2);
	Graph aux = getVertex(v1, g);
	if(!aux) return false;
	// Il grafo è non orientato, mi basta dunque ciclare sulla <e e cercare l'adiac.
	halfEdge* e = aux->edges;
	for(; e; e = e->next)
		if(e->ptr->label == v2)
			return true;
	return false;
}

// Restituisce la lista di adiacenza di un vertice
list::List graph::adjacentList(Label v1, const Graph& g) {
	list::List lst = list::createEmpty();
	// Trovo il vertice di cui devo restituire la lista di adiacenza
	Graph aux = getVertex(v1, g);
	if(!aux) return lst;

	halfEdge* e = aux->edges;
	// Ciclo su ogni mezz'arco e aggiungo i mezz'archi
	for(; e; e = e->next)
		addRear(e->ptr->label, lst);

	return lst;
}

// Ritorna un cammino tra una citta' ed un altra
// Il cammino da "v1" a "v2" alla fine sara' in "path"
// e la lunghezza sara' in "len".
// Si assume che il chiamante fornisca inizialmente un cammino vuoto.
//
// La funzione rappresenta una variante della visita DFS

bool pathAux(Graph g, Label to, list::List &path, int &len) {
	if(g->visited) return false;
	g->visited = true;
	if(g->label == to) return true;

	halfEdge* e = g->edges;
	for(; e; e = e->next) {
			if(pathAux(e->ptr, to, path, len)) {
				len += e->weight;
				addFront(e->ptr->label, path);
				return true;
			}
	}
	return false;
}

void graph::findPath(Label v1, Label v2, list::List &path, int &len, const Graph& g) {
	path = list::createEmpty();
	len = 0;
	// Caso di cammino nullo:
	if(v1 == v2) return;
	// Pongo tutti i vertici a non visitati
	for(Graph g1 = g; g1; g1->visited = 0, g1 = g1->next);
	Graph from = getVertex(v1, g);
	if(!from) return;
	// Aggiungo alla fine (in testa) il nodo di partenza
	if(pathAux(from, v2, path, len))
		addFront(v1, path);
}
/*******************************************************************************************************/
// Stampa il grafo
void printGraph(const graph::Graph& g) {
	Graph aux = g;
	// Ciclo su ogni vertice
	for(; aux; aux = aux->next) {
		cout << aux->label << " : ";
		halfEdge* e = aux->edges;
		// Ciclo su ogni mezz'arco
		for(; e; e = e->next)
			cout << "(" << e->ptr->label << "): " << e->weight << " -> ";
		cout << endl;
	}
}
