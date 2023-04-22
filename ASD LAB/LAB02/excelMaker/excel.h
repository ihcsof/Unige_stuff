/*
HEADER DEL PROGRAMMA DI AUTO-TESTING
(produce un file csv (comma-sep-val) con tutti i calcoli automatizzati)

Gianì Lorenzo 5008434
Foschi Lorenzo 4989646
Pastorelli Patrick 5038958

Su LibreOffice in ambiente linux l'apertura risulta immediata,
nel caso di excel potrebbe essere necessaria l'operazione:
	Dati --> Da testo/CSV --> seleziona file -->
		delimitatore: virgola ; 
		Rilevamento del tipo di dati: non rilevare il tipo di dati

NB: se eseguito su VM (o comunque su dispositivi non molto performanti)
	 il programma potrebbe impiegare alcuni minuti
*/

#include <vector>
#include <fstream>

#ifndef AUX_EXCEL
#define AUX_EXCEL

#include <string>

// typedef per l'array di puntatore a funzioni:
// (funzioni void con parametro std::vector<int>&))
typedef void(*sortPointer)(std::vector<int>&);

void initOutput(std::vector<std::string>&, std::ofstream&);

double avg(std::vector<double>&);

#endif



