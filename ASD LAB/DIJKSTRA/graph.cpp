#include "graph.h"
#include <climits>

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

vector<Graph> createVector(Graph g) {
	vector<Graph> aux;
	for(; g; g = g->next)
		aux.push_back(g);
	return aux;
}

int binarySearchAux(std::vector<Graph>& a, Label l, int first, int last) {
	if(last < first) return -1;
	
	int middle = (first + last) / 2;

	if(a[middle]->label > l) return binarySearchAux(a, l, first, middle-1);
	if(a[middle]->label < l) return binarySearchAux(a, l, middle+1, last);
	return middle;
}

int binarySearch(std::vector<Graph>& a, Label l) {
	return binarySearchAux(a, l, 0, a.size()-1);
}

int findMin(std::vector<int>& a, std::vector<bool>& mark) {
	int min = INT_MAX;
	int index;
	// Trovo il minimo tra i non ancora visitati
	for(int i = 0; i < a.size(); ++i)
		if(!mark[i] && a[i] < min) {
			min = a[i]; 
			index = i; 
		} 
	// VISITO IL NODO (marcato)
	mark[index] = true;
	return index;
}

void graph::findPath(Label v1, Label v2, list::List &path, int &len, const Graph& g) {
	// Inizializzazioni e creazione vector di nodi
	path = list::createEmpty();
	len = 0;
	vector<Graph> nodes = createVector(g);
	// Grazie alla conoscenza del numero di nodi posso inizializzare i vector ausiliari
	std::vector<bool> marked(nodes.size(), 0);
	std::vector<int> costs(nodes.size(), INT_MAX);
	std::vector<Label> prev(nodes.size(), ""); 

	// Ottengo l'indice del nodo di partenza e pongo il costo a zero
	int i = binarySearch(nodes, v1);
	if(i == -1) return;
	costs[i] = 0;
	marked[i] = true;
	
	for(int j = 0; j < nodes.size()-1; ++j) {
		// Per ogni adiacenza di i, se visitata...
		for(halfEdge* e = nodes[i]->edges; e; e = e->next) {
			int k = binarySearch(nodes, e->ptr->label);
			if(marked[k]) continue;
			//... mi chiedo se devo aggiornare i campi costo e prev (path minore)
			if(costs[k] > costs[i] + e->weight) {
				costs[k] = costs[i] + e->weight;
				prev[k] = nodes[i]->label;
			}
		}
		i = findMin(costs, marked);
	}

	// Stampa della tabella
	for(int j = 0; j < nodes.size(); ++j) {
		std::cout << nodes[j]->label << " | ";
		std::cout << std::boolalpha << marked[j] << " | ";
		std::cout << costs[j] << " | ";
		std::cout << prev[j] << std::endl;
	}
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
