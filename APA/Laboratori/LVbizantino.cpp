#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
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

/*
Nota sullo std della matrice
4 righe i (la quarta è il malizioso)
ogni colonna j è il bit ricevuto a proc. i da proc. j
[1, 1, 0, 0], 
[1, 1, 0, 0], 
[1, 1, 0, 1],
[...]] */


int main() {
	int r = pow(2, 10); // Round
	int t = 1; // Maliziosi
	int p = 7 * t + 1; // Affidabili
	int n = 8 * t + 1; // processi
	int L = 5 + t + 1; // soglia L
	int H = L + t; // soglia H
	mappa rounds; // Array di rounds
	bits b(n); // b (bit in trasmissione) di dimensione n

	// Distribuzione uniforme valori
	std::uniform_int_distribution<int> distribution(0,1);

	for (int i = 0; i < r; ++i) {
		// Creazione vettore bit casuali
		bits v(n);
		for(int j = 0; j < p; ++j) v[j] = distribution(generator);

		// Creazione matrice con split 2 a 1 (e diverso per i maliziosi)
		matrix m(p);
		for(int j = 0; j < p; ++j) m[j] = v;

		int cround = 0; // Contatore turni

		while(true) {
			bool coin = distribution(generator);
			cround++;

			for (int j = 0; j < p; ++j) {
				// Calcolo di maj e tally
				int mag = maj(m[j]);
				int tl = tally(m[j]);
				// Se ho raggiunto il consenso (sopra tally) metto maj, sennò "toss a coin"
				int soglia = ((coin) ? L : H);
				b[j] = (tl >= soglia ? mag : 0);
				if(tl >= p) b[j] = mag;
			}
			
			// Inserimento dei valori in ricezione
			for (auto& v : m) v = b;
			// Impostazione valori del malizioso (per ogni riga, terza colonna : 1 - sent)
			for (int j = 0; j < p; ++j) m[j].back() = !b[j];

			// Controllo terminazione
			bool term = true;
			for(int j = 1; j < p; ++j)
				if (m[0][j] != m[0][j-1]) term = false;
			if(term) break;
		}

		rounds[cround]++;
	}

	// stampo valori su file per plottare in py
	std::ofstream out;
	out.open("output.txt");
	for(const auto& [n, fqz] : rounds)
		out << n << " " << fqz << '\n';

	out.close();
}


