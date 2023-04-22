// g++ -O3 lvqs.cpp per > velocità

#include <algorithm> // std::shuffle
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
// Per il seed
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

// var globale per il confronto
int confr = 0;

// funzione di swap
void scambia(std::vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

int partition(std::vector<int>& v, int fst, int lst) {
	// Scelta del pivot banale in prima posizione
	int pivot = v[fst];
	int i = fst + 1;
	
	// Algoritmo di partition
	for(int j=i; j<=lst; ++j) {
		if(v[j] < pivot) {
			scambia(v, j, i);
			++i;
		}
		++confr;
	}
	// Porto il pivot nella sua posizione definitiva e ritorno il suo indice
	scambia(v, i-1, fst);
	return (i-1);
}

void qs(std::vector<int>& v, int fst, int lst) {
	if(fst < lst) {
		// Salvo l'INDICE del pivot chiamando partition con scelta banale
		int i_pivot = partition(v, fst, lst);
		// Chiamate ricorsive sulle sottoseq.
		qs(v, fst, i_pivot-1);
		qs(v, i_pivot+1, lst);
	}
}

void lvqs(std::vector<int>& v)
{
   /* shuffle della std lib dell'array per Las Vegas Quick Sort (shuffle con distrib. unif.)*/
	/* come seed si usa cloch prendendo il tempo trascorso dalla epoch */
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));

	if(v.size() <= 1)
		return;
	qs(v, 0, v.size()-1);
}

int main() {
	unsigned int sz = pow(10, 4);
	unsigned int r = pow(10, 3);
	// creazione arr con dim giuste per evitare resize con i push_back
	std::vector<int> a(sz);
	std::vector<int> aConfr(r);
	// sequenza S di 10^4 numeri
	for(int i = 0; i < sz; ++i)
		a[i] = i;
	
	// R = 10^5 run
	for(int i = 0; i < r; ++i) {
		 lvqs(a);
		 aConfr[i] = confr;
		 confr = 0;
	}

	// for debug purposes :)
	// for(int i = 0; i < sz; ++i) std::cout << a[i] << " ";
	// std::cout << std::is_sorted(a.begin(), a.end());

	// valore medio
	double sum = 0;
	for(int i = 0; i < r; ++i)
		sum += aConfr[i];
	double valmedio = sum / r;
	std::cout << "\nValore medio:" << valmedio << '\n';

	// varianza
	sum = 0;
	for(int i = 0; i < r; ++i)
	  sum += (aConfr[i] - valmedio) * (aConfr[i] - valmedio);
	double var = sum / (r-1);
	std::cout << "\nVarianza:" << var << '\n';
	
	// stampo valori su file per plottare in py
	std::ofstream out;
	out.open("out.txt");
	// almedio e varianza --> valori
	for(int i = 0; i < r; ++i)
		out << aConfr[i] << '\n';
	out << valmedio << '\n';
	out << var << '\n';
}
