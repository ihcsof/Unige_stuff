/*
AUX DEL PROGRAMMA DI AUTO-TESTING
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

#include "excel.h"

// Funzione per la media
double avg(std::vector<double>& v) {
	double sum = 0;
	for(int i=0; i<v.size(); ++i) 
		sum+=v[i];
	return (sum/v.size());
}

// Funzione di init dell'output su file excel
void initOutput(std::vector<std::string>& v, std::ofstream& o) {
	o << ",";
	for(int i=0; i<v.size(); ++i) {
		for(int j=0; j<4; ++j) {
			o << v[i];
			if(j < 3) 
				o << " (run" << j+1 << "),";
			else
				o << ": media,";
		}
	}
	o << "\n";
}
