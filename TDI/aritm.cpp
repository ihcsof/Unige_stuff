// g++ --std=c++2a per compilazione

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <limits>
#include <numeric>

void aritm() {
	std::string str = "10110100010110010110110111100010101011010110010101";
	int c0 = 0;
	int c1 = 0;
	std::cout << "length: " << str.length() << '\n';
	// Conto delle frequenze empiriche
	for(auto c : str) {
		if(c == '0') c0++;
		if(c == '1') c1++;
	}
	// Probabilità di 0 e di 1 nella stringa
	double p0 = (double)c0 / str.length();
	double p1 = (double)c1 / str.length();

	std::cout << "Prob di 0: " << p0 << " / Prob di 1: " << p1 << '\n';

	// Calcolo dell'intervallo
	std::pair<long double, long double> phi = {0, 1};
	for(int i = 0; i < str.length(); ++i) {
		double aux = phi.first;
		// interv_inf = interv_inf + length * cdf(xk - 1)
		// Se trovo 1 il val prec è 0 e lo peso / Se trovo 0 il valore prima non esiste nella cdf (p = 0)
		phi.first = aux + (phi.second - aux) * ((str[i]=='1') ? p0 : 0.);
		// interv_sup = interv_inf + length * cdf(xk)
		// Se trovo 1 la cdf vale sicuramente 1 (valore attuale xk), se trovo 0 serve la p di 0
		phi.second = aux + (phi.second - aux) * ((str[i]=='1') ? 1. : p0);
	}
	// Stampa dell'intervallo
	std::cout << std::setprecision(std::numeric_limits<long double>::digits10);
	std::cout << "[" << phi.first << ", " << phi.second << ")\n";

	// Calcolo valore compreso nell'intervallo phi (midpoint per evitare overflow)
	long double pmid = std::midpoint(phi.first, phi.second);
	// Iterazione per trovare una potenza di 2 (metodo di bisezione)
	while (pmid < phi.first || pmid >= phi.second) {
		if (pmid < phi.first) phi.first = pmid;
		else if (pmid >= phi.second) phi.second = pmid;
		pmid = std::midpoint(phi.first, phi.second);
	}

	std:: cout << "Punto medio: " << pmid;

	// Costruzione della stringa
	std::string decoded;
	for(int i = 0; i < str.length(); ++i) {
		// a seconda dell'interv. di probabilità scelgo 0 o 1 (inverso dell'esplosione)
		char trans = (pmid < p0) ? '0' : '1';
		decoded.push_back(trans);
		// Se il nuovo char trovato è 1 sottraggo cdf(xk-1)=p0 e divido per p(xk)=p1
		if(trans=='1') {
			pmid -= p0; 
			pmid /= p1;
		}
		// Se il nuovo char trovato è 0 "sottraggo cdf(xk-1)=0" (inutile) e divido per p(xk)=p0
		else pmid /= p0;
	}
	std::cout << '\n' << decoded << '\n';
	std::cout << ("10110100010110010110110111100010101011010110010101" == decoded) << '\n';
}

//std::string decode(long double num, int sz) {}

int main() {
	aritm();
}
