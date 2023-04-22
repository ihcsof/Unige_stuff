#include <iostream>
#include <chrono>
#include <random>
#include <cassert>

typedef unsigned int uint;

// Distribuzione uniforme (meglio del rand)
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

uint powInMod(uint b, uint e, uint n) {
	uint r = 1;
	// porto la base in modulo n
	b %= n;
	
	// algoritmo per calcolare base^exp ma tenendomi in modulo (no overflow)
	while(e) {
		// se l'exp è dispari moltiplico il risultato per la base (mod n)
		if(e & 1) r = (r * b) % n;
		e >>= 1;
		b = (b * b) % n;
	}

	return r;
}

bool miller(int n) {
	// n >= 3 e n dispari
	assert(n >= 3 && n & 1);
	uint s = 0;
	uint q = n - 1;

	// Distribuzione uniforme valori
	std::uniform_int_distribution<int> distribution(2,n-2);
	// a = campionato uniformemente
	uint a = distribution(generator);

	// calcolo decomposizione q*2^s + 1 finchè pari
	while(!(q & 1)) {
		++s;
		q >>= 1;
	}
	
	// a^q (mod n)
	//uint x = (static_cast<int>(pow(a, q))) % n;
	uint x = powInMod(a, q, n);
	
	if(x == 1 || x == n - 1) return true;

	// finchè s-1 >= 0 risalgo (sx<--dx) quadrando
	while(s) {
		x = ((x*x) % n);
		// Annullamento quadrato --> -1
		if(x == (n - 1)) return true;
		--s;
	}
	return false;
}



int main() {
	uint c = 0;
	for(int i = 0; i < 100; ++i)
		c += miller(65);
	
	std::cout << c << '\n';
}
