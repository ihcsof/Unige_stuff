#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <unordered_map>

typedef std::vector<bool> bits;
typedef std::vector<bits> matrix;
typedef std::unordered_map<int, int> mappa;

// Distribuzione uniforme (meglio del rand)
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

// Ritorna il valore con più occorrenze
int maj(const bits& v) {
	int c1 = 0;
	int c0;

	for (auto bit : v) c1 += bit;
	c0 = v.size() - c1;

	return (c1 > c0);
}

// Ritorna il numero di occorrenze di maj
int tally(const bits& v) {
	int c1 = 0;
	int c0;

	for (auto bit : v) c1 += bit;
	c0 = v.size() - c1;

	return (c1 > c0) ? c1 : c0;
}

int main() {
	int r = pow(2, 10); // Round
	int t = 1; // Maliziosi
	int p = 7 * t + 1; // Affidabili
	int n = 8 * t + 1; // processi
	int L = 5 * t + 1; // soglia L
	int H = L + t; // soglia H
	mappa rounds; // Array di rounds
	bits b(n); // b (bit in trasmissione) di dimensione n

	// Distribuzione uniforme valori
	std::uniform_int_distribution<int> distribution(0,1);
	// Variabile per il valore medio
	double E = 0;

	for (int i = 0; i < r; ++i) {
		// Creazione vettore bit casuali
		bits v(n);
		for(int j = 0; j < p; ++j) v[j] = distribution(generator);

		// Creazione matrice con valori casuali generati a riga precedente
		matrix m(p);
		for(int j = 0; j < p; ++j) {
			m[j] = v;
			m[j].back() = !v[j];
		}

		int cround = 0; // Contatore turni

		while(true) {
			// Lancio della moneta
			bool coin = distribution(generator);
			cround++;

			// Controllo terminazione (tutti i valori uguali su riga)
			bool term = true;
			for(int j = 1; j < p; ++j)
				if (m[0][j] != m[0][j-1]) term = false;
			if(term) break;

			for (int j = 0; j < p; ++j) {
				// Calcolo di maj e tally
				int mag = maj(m[j]);
				int tl = tally(m[j]);
				// Scelta random della soglia L o H e inserimento bit (maggioranza o 0)
				int soglia = (coin ? L : H);
				b[j] = (tl >= soglia ? mag : 0);
				if(tl >= p) b[j] = mag;
			}
			
			// Inserimento dei valori in ricezione
			for (auto& v : m) v = b;
			// Impostazione valori del malizioso (per ogni riga, terza colonna : 1 - sent)
			for (int j = 0; j < p; ++j) m[j].back() = !b[j];
		}

		rounds[cround]++;
	}

	// stampo valori
	for(const auto& [n, fqz] : rounds)
		std::cout << n << " " << fqz << '\n';
	// Calcolo del valore medio del #round
	for(const auto& [n, fqz] : rounds)
		E += (n * fqz);
	E /= r;

	// val medio
	std::cout << "Valore medio del #round: " << E << '\n';
}


