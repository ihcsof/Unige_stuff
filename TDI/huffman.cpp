// g++ -std=c++17 huffman.cpp 

#include <iostream>
#include <fstream>
#include <unordered_map> // Per la mappa con occorrenze e per coppie char-cod
#include <queue>
#include <string>
#include <cmath> // Per log2

using std::tuple;
using std::vector;
using std::greater;
typedef std::unordered_map<char, int> map; // Mappa per salvare le occorrenze di char dall'input
typedef std::unordered_map<char, std::string> codMap; // Mappa per registrare coppie char-cod

struct node {
	char c; // carattere letto
	int freq; // frequenza del carattere
	node* sx;
	node* dx;

	// Costruttore
	node(char c, int freq = 0) : 
		c(c), freq(std::forward<int>(freq)),
		sx(nullptr), 
		dx(nullptr){}
	
};

typedef node* tree;
// heap è una prioritiy queue di triple(int, char, nodo) con specif. container default e funzione di comparazione
typedef std::priority_queue<tuple<int, char, tree>, vector<tuple<int, char, tree>>, greater<tuple<int, char, tree>>> heap;
// Queue di char-str per salvare char e cod. corrispondente in bfs
typedef std::queue<tuple<tree, std::string>> bfsq;

// Funzione di stampa ricorsiva
void stampa(const tree& t, int lvl) {
	if(!t) return;
	stampa(t->sx, lvl+1);
	if(t->c != '^')
		std::cout << t->c << " " << lvl << '\n';
	stampa(t->dx, lvl+1);
}

// Cancellazione albero per evitare mem_leak
void destroy_tree(tree aux){
	if (!aux) return;
	destroy_tree(aux->sx);
	destroy_tree(aux->dx);
	delete aux;
}

codMap huffman(const map& m) {
	heap h;
	tree aux;
	codMap cmp; // Compression map per registrare coppie char-codifica_bin_associata
	bfsq q; // Coda per visita bfs iterativa

	// Inserimento delle coppie carattere-frequenza nell'heap con annessa creazione nodi
	for(const auto& [ch, freq] : m)
		h.emplace(freq, ch, new node(ch, freq));

	for(int i = 0; i < m.size()-1; ++i) {
		auto t1 = h.top();
		h.pop();
		auto t2 = h.top();
		h.pop();
		// Creazione nuovo nodo interno con ch. dummy e freq. pari alla somma dei figli
		aux = new node('^', std::get<0>(t1) + std::get<0>(t2));
		// Inserimento figli a sx e dx e successivo inserimento nuovo nodo nell'heap
		aux->sx = std::get<2>(t1);
		aux->dx = std::get<2>(t2);
		h.emplace(aux->freq, aux->c, aux);
	}

	//stampa(aux, 0); // Stampa per debug

	// Inserisco la root dell'albero generato dall'algoritmo di huffman
	q.emplace(aux, "");
	// BFS iterativa
	while(!q.empty()) {
		// Prendo la coppia nodo(con char, sx, dx) e codice associato
		auto [n, cod] = q.front();
		q.pop();

		// Se entrambi null è una foglia: inserisco la sua codifica nella mappa alla posizione del char
		if(!n->sx && !n->dx) cmp[n->c] = cod;
		// Se mi trovo in un nodo interno...
		else {
			// Se vado a sinistra metto in coda il sinistro con la codifica precedente concatenata con "0"
			if(n->sx) q.emplace(n->sx, cod + "0");
			// Se vado a destra metto in coda il destro con la codifica precedente concatenata con "1"
			if(n->dx) q.emplace(n->dx, cod + "1");
		}
	}

	destroy_tree(aux);
	return cmp;
}

// Funzione di lettura da file
map fromFile(int& bits) {
	std::string str;
	std::ifstream fd("Genova.txt");
	map m;

	while(std::getline(fd, str)) {
		str.append("\n"); // Aumento del newline manuale dato dalla getline
		for(auto& c : str) {
			m[c]++; // Incremento della frequenza del valore c (char letto corrente)
			bits += 8; // Incremento di un byte
		}
	}

	fd.close();
	return m;
}

// Funzione di codifica e contestuale scrittura su file
int codifica(const codMap& cmp) {
	std::string str;
	std::ifstream fd("Genova.txt");
	std::ofstream out("codificato.txt");
	int bits = 0;

	while(std::getline(fd, str)) {
		str.append("\n"); // Aumento del newline manuale dato dalla getline
		for(char c : str) {
			out << cmp.at(c); // Scrittura su files
			bits += cmp.at(c).size(); // Aumento dei bit con la frequenza di questo char
		}
	}

	fd.close();
	out.close();
	return bits;
}

int main() {
	// Conto i bit e prendo il testo calcolando le freq nella mappa
	int bits = 0;
	map m = fromFile(bits);

	// Stampa char letti e rispettive frequenze
	for(const auto& [ch, fqz] : m)
		std::cout << ch << " " << fqz << '\n';
	std::cout << "--------------------------------------\n";

	// Entropia di Shannon
	double H = 0;
	double tot = 0;
	// Calcolo del totale (somma delle frequenze = #char)
	for(const auto& [ch, freq] : m)
		tot += freq;
	// Calcolo dell'entropia di shannon (H = p * log2(1/p))
	for(const auto& [ch, freq] : m)
		H += ((freq/tot) * log2(tot/freq));

	// Codifica di Huffman (ritorna mappa con char e rispettiva codifica)
	codMap cmp = huffman(m);

	// Lunghezza attesa (L = dimensione della str di bit * sua probabilità
	double L = 0;
	for(const auto& [ch, cod] : cmp)
		L += cod.size() * (m[ch]/tot);

	// Stampa codifiche per carattere
	for(const auto& [ch, cod] : cmp)
		std::cout << ch << " " << cod << '\n';
	// Stampa H, L e #bits
	std::cout << "Entropia Shannon: " << H << '\n'; // 4.35989
	std::cout << "Lunghezza Attesa: " << L << '\n'; // 4.39508
	std::cout << "Bit originali: " << bits << '\n'; // 29280
	// Codifica su file
	int bitsafter = codifica(cmp);
	std::cout << "\"Bit\"(realmente byte) dopo codifica: " << bitsafter << '\n'; // 16086
	
	/* Si osserva una lunghezza attesa molto vicina al limite inferiore rappresentato
		dall'entropia di Shannon. Inoltre si osserva come, assumendo ogni 0 od 1
		memorizzato in un bit, il #bit passa da 29280 a 16086 (~1.82 volte minore)
	*/
}
