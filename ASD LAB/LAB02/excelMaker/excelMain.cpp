/*
MAIN DEL PROGRAMMA DI AUTO-TESTING
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

#include <chrono>
#include "../labo2_sort.h"
#include "../labo2_aux.h"
#include "excel.h"
#include <iomanip>

using namespace std::chrono;
 
int main()
{
	// File csv
	std::ofstream excelFile;
	excelFile.open("test.csv");

	// Array di puntatori a funzione (v. header)
	std::vector<sortPointer> vFun = {&selectionSort,&insertionSort,&bubbleSort,&mergeSort,&quickSortTrivial,&quickSortRandom};
	
	// Vector ausiliari con i file e i nomi degli algoritmi
	std::vector<string> vStr = {"../in-10.txt","../in-10-ordinati.txt","../in-100.txt","../in-100-ordinati.txt","../in-1000.txt", "../in-1000-ordinati.txt","../in-10000.txt","../in-10000-ordinati.txt","../in-40000.txt","../in-40000-ordinati.txt" };
	std::vector<string> vSorts = {"selectionSort","insertionSort","bubbleSort","mergeSort","quickSortTrivial","quickSortRandom"};
	
	// Inizializzo l'output sul file excel
	initOutput(vSorts,excelFile);
	// Per il calcolo del tempo impiegato
	high_resolution_clock::time_point t1, t2;
   double duration;

	//Impostazione fixed per la virgola mobile
	excelFile << fixed;

	//Stampa e calcolo effettivo dei valori
	/*
		Per ogni file:
			Stampo quanto necessario e ottengo il vector con i dati
			Per ogni algoritmo di ordinamento:
				Per tre volte:
					Calcolo il tempo di ordinamento
					Calcolo la media e la stampo
	*/
	for(int i=0; i<vStr.size(); ++i) {
		//Stampo sul file (troncando i ../)
		excelFile << "Test" << i+1 << ": " << vStr[i].substr(3,vStr[i].back()) << ",";
		//Creo v leggendo dal file i
		std::vector<int> v (leggiVettoreDaFile(vStr[i]));
		for(int j=0; j<vFun.size(); ++j) {
			std::vector<double> vAverage;
			for(int k=0; k<3; ++k) {
				std::vector<int> aux(v);
				//Calcolo il tempo impiegato dall'alg. in posizione j nel vector di funzioni
				t1 = high_resolution_clock::now();
    			vFun[j](aux);
    			t2 = high_resolution_clock::now();
    			duration = duration_cast<microseconds>( t2 - t1 ).count();
				//Operazioni sulla media e sulla stampa
				vAverage.push_back(duration);
				excelFile << duration << ",";
			}
			excelFile << avg(vAverage) << ",";
		}
		excelFile << "\n";
	}
	
	excelFile.close();
	return 0;
}
