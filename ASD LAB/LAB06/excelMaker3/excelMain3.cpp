/*
MAIN DEL PROGRAMMA DI AUTO-TESTING 3
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

!!! NON utilizzare USE HASH_TABLE per compilare questo specifico programma (excelMain3)
g++ excelMain3.cpp dictionary-hashtable.cpp string-utility.cpp excelAux.cpp dictionary-orderedvector.cpp dictionary-doublylinkedlist.cpp dictionary-bst.cpp 

*/
#include <iomanip>
#include "dictionary.h"

using namespace dict;
 
int main()
{
	// Vector di puntatori a funzioni e vector di files
	std::vector<hashPointer> vFun = {&h1, &h2, &h3};
	std::vector<std::string> vFiles = {"../engeng/a.txt", "../engeng/s.txt"};
	std::vector<int> dims = {20, 100, 1000};
	std::vector<std::string> vKeys = {"asas", "azure", "aieie", "avulso", "zoom", "summit", "sissignore", "allegro"};

	// File csv
	std::ofstream excelFile;
	excelFile.open("test3.csv");

	if(!excelFile.is_open())
		return 1;

	excelFile << fixed << right;

	// Inizializzo l'output sul file excel
	initOutput2(excelFile, vFiles, vKeys);

	// Per i vector
	testV(excelFile, vFiles, vKeys);
	// Per le dll
	testL(excelFile, vFiles, vKeys);
	// Per i bst
	testB(excelFile, vFiles, vKeys);
	
	high_resolution_clock::time_point t1, t2;
   double duration;
	Dictionary d;
	// Stringa dummy per ottenere risultati riconducibili a quelli del test manuale
	std::string a;

	// Per l'hash
	for(int i = 3; i < 12; ++i) {
		tableDim = dims[i%3];
		excelFile << "Test" << i+1 << ": hash table con dim " << tableDim << " h" << i/3 << ",";
		
		t1 = high_resolution_clock::now();
		d = readFromFile(vFiles[0], vFun[i/3-1]);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>( t2 - t1 ).count();
		excelFile << duration << ",";
		t1 = high_resolution_clock::now();
		dict::insertElem("asas", "prova", d, vFun[i/3-1]);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>( t2 - t1 ).count();
		excelFile << duration << ",";
		for(int k = 0; k < 5; ++k) {
			t1 = high_resolution_clock::now();
			a = dict::search(vKeys[k], d, vFun[i/3-1]);
			t2 = high_resolution_clock::now();
			duration = duration_cast<microseconds>( t2 - t1 ).count();
			excelFile << duration << ",";
		}
		deleteD(d);
		t1 = high_resolution_clock::now();
		d = readFromFile(vFiles[1], vFun[i/3-1]);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>( t2 - t1 ).count();
		excelFile << duration << ",";
		for(int k = 0; k < 3; ++k) {
			t1 = high_resolution_clock::now();
			a = dict::search(vKeys[k+5], d, vFun[i/3-1]);
			t2 = high_resolution_clock::now();
			duration = duration_cast<microseconds>( t2 - t1 ).count();
			excelFile << duration << ",";
		}
		excelFile << "\n";
		deleteD(d);
	}
	excelFile.close();
}
