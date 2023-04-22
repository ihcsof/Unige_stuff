/*
MAIN DEL PROGRAMMA DI AUTO-TESTING 2-01
(produce un file csv (comma-sep-val) con tutti i calcoli automatizzati)

Gianì Lorenzo 5008434
Foschi Lorenzo 4989646
Pastorelli Patrick 5038958

Su LibreOffice in ambiente linux l'apertura risulta immediata,
nel caso di excel potrebbe essere necessaria l'operazione:
	Dati --> Da testo/CSV --> seleziona file -->
		delimitatore: virgola ; 
		Rilevamento del tipo di dati: non rilevare il tipo di dati

!!! utilizzare USE HASH_TABLE per compilare questo specifico programma (excelMain1)
g++ -DUSE_HASH_TABLE excelMain1.cpp dictionary-hashtable.cpp string-utility.cpp excelAux.cpp 

*/
#include <iomanip>
#include "dictionary.h"

using namespace dict;
 
int main()
{
	// Vector di puntatori a funzioni e vector di files
	std::vector<hashPointer> vFun = {&h1, &h2, &h3};
	std::vector<std::string> vFiles = {"../engeng/ascii.txt", "../engeng/d.txt", "../engeng/h.txt"};
	std::vector<int> dims = {20, 100, 1000};

	// File csv
	std::ofstream excelFile;
	excelFile.open("test1.csv");

	if(!excelFile.is_open())
		return 1;

	excelFile << fixed << right;

	// Inizializzo l'output sul file excel
	initOutput(excelFile);
	
	// Per ogni file, chiama le diverse funzioni (3) per 3 volte (con 3 tableDim diverse)
	for(int i = 0; i < vFiles.size(); ++i) {
		for(int j = 0; j < vFun.size(); ++j) {
			for(int k = 0; k < dims.size(); ++k) {
				// Formattazione
				tableDim = dims[k];
				excelFile << "Test" << j+1+i*3 << "." << k+1 << ": " << vFiles[i].substr(10,vFiles[i].back());
				excelFile << " | tableDim = " << dims[k] << " | hash h" << j+1 << ",";
				Dictionary d = readFromFile(vFiles[i],vFun[j]);
				print(d, excelFile);
				// Cancella il dizionario
				deleteD(d);
				excelFile << "\n";
			}	
		}	
	}

	excelFile.close();
}
