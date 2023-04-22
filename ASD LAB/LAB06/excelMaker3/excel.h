/*
HEADER DEL PROGRAMMA DI AUTO-TESTING 2
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
#include <string>
#include <chrono>

#ifndef AUX_EXCEL
#define AUX_EXCEL

// typedef per l'array di puntatori a funzione int x (key)
typedef int(*hashPointer)(std::string);
void initOutput(std::ofstream&);

void initOutput2(std::ofstream& o, std::vector<std::string>&, std::vector<std::string>&);
void testL(std::ofstream&, std::vector<std::string>&, std::vector<std::string>&);
void testV(std::ofstream&, std::vector<std::string>&, std::vector<std::string>&);
void testB(std::ofstream&, std::vector<std::string>&, std::vector<std::string>&);

#endif
