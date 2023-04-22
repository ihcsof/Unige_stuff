// data.cpp (Lorenzo Foschi - 4989646)

#include "data.h"
#include "readUtility.h"
#include <iostream>

using namespace period;

// Creazione di una data, dati tre parametri interi
Date period::createDate(int y, int m, int d) {
	Date toRet = {y, m, d};
	return toRet;
}

bool period::isEmpty(const Date& d) {
	return (d == EMPTYDATE);
}

// Overloading operatore == sulla base di un triplo confronto
bool period::operator == (const Date& d1, const Date& d2) {
	return(d1.yyyy == d2.yyyy && d1.mm == d2.mm && d1.dd == d2.dd);
}

// Overloading dell'operatore != in termini dell'operatore ==
bool period::operator != (const Date& d1, const Date& d2) {
	return !(d1 == d2);
}

// Overloading dell'operatore > sulla base di una catena di controlli
// L'ordine con la quale vengono effettuati e' tale da finire con un..
// .. controllo unico comprendente due casistiche ( == e < )
bool period::operator > (const Date& d1, const Date& d2) {
	if(d1.yyyy > d2.yyyy) return true;
	if(d1.yyyy < d2.yyyy) return false;
	if(d1.mm > d2.mm) return true;
	if(d1.mm < d2.mm) return false;
	if(d1.dd > d2.dd) return true;
	return false;
}

// Overloading dell'operatore < in termini dell'operatore >
// ( d1 e' < di d2 sse d2 e' > di d1 )
bool period::operator < (const Date& d1, const Date& d2) {
	return (d2 > d1);
}

// Overloading dell'operatore >= in termini dell'operatore <
// ( d1 e' >= di d2 sse e' falso che d1 sia < di d2 )
bool period::operator >= (const Date& d1, const Date& d2) {
	return !(d1 < d2);
}

// Overloading dell'operatore <= in termini dell'operatore >
// ( d1 e' <= di d2 sse e' falso che d1 sia > di d2 )
bool period::operator <= (const Date& d1, const Date& d2) {
	return !(d1 > d2);
}

// Funzione ausiliaria (non presente nell'header dunque non esposta..
// al di fuori dell'interfaccia): verifica se l'anno e' bisestile
bool isBis(int y) {
	if((y % 4) != 0) return false;
	if((y % 100) != 0) return true;
	return ((y % 400) == 0);
}

// Funzione di verifica della Data, che si avvale di controlli sulla..
// .. validità dei range possibili + controllo sull'anno bisestile
// Convenzione sull'anno: >= anno mille fino a qualsiasi anno futuro (scalabilità)
bool period::verifyDate(const Date& d) {
	if(d.yyyy < 1000 || d.mm < 1 || d.mm > 12 || d.dd < 1) return false;
	if(d.mm == 4 || d.mm == 6 || d.mm == 9 || d.mm == 11)
		return (d.dd <= 30);
	if(d.mm == 2) {
		if(isBis(d.yyyy))
			return (d.dd <= 29);
		return (d.dd <= 28);
	}
	return (d.dd <= 31);
}

// Funzione (fuori dal namespace) di stampa formattata della data
bool printDate(const period::Date& d) {
	if(isEmpty(d)) return false;
	// Aggiunta dello zero se giorno (e poi mese) e' < 10 (per lo standard)
	if(d.dd < 10) std::cout << "0";
	std::cout << d.dd << "/";
	if(d.mm < 10) std::cout << "0";
 	std::cout << d.mm << "/" << d.yyyy;
	return true;
}

// Ausiliaria per la lettura della data da cin
// Si effettuano controlli sul buffer ad ogni lettura: se l'utente sbaglia ad
// inserire da stdin il programma si mantiene consistente
bool readDateCin(int& dd, int& m, int& y) {
	std::cout << "\nInserisci il giorno: ";
	std::cin >> dd;
	if(isError()) return false;
	std::cout << "\nInserisci il mese: ";
	std::cin >> m;
	if(isError()) return false;
	std::cout << "\nInserisci l'anno: ";
	std::cin >> y;
	return (!isError());
}
