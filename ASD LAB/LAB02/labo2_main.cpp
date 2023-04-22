// compilare con il comando seguente:
// g++ -Wall -std=c++11 labo2_main.cpp labo2_aux.cpp labo2_sort.cpp -o labo2

#include <stdexcept>
#include <vector>

#include "labo2_aux.h"   // funzioni ausiliarie per lettura/scrittura su file
#include "labo2_sort.h"  // vari algoritmi di ordinamento

using namespace std;


#include <chrono>        // Namespace e funzioni per misurare il tempo, utili per la valutazione delle prestazioni dei programmi e inclusi nello standard C++ dal 2011 in avanti.  Per usarli con il compilatore g++ e' necessario inserire l'opzione di compilazione -std=c++11.  Altri compilatori potrebbero richiedere opzioni diverse da questa.

using namespace std::chrono;


int main()
{
try {
    string nome_file;
    cout << "\nInserire il nome del file da cui leggere (es: in-1000.txt) > ";
    cin >> nome_file;
    if (!cin) throw runtime_error("Errore inserimento nome file\n"); 
    vector<int> v_disordinato = leggiVettoreDaFile(nome_file);
    cout << "\nInserire il nome del file su cui stampare le informazioni sull'esecuzione (es: out-1000.txt) > ";
    cin >> nome_file;
    if (!cin) throw runtime_error("Errore inserimento nome file\n"); 
    ofstream ofs(nome_file.c_str()); // apertura di uno stream associato ad un file, in scrittura    
    stampaVettoreEDurataSuStream(v_disordinato, "\n\n====== Vettore disordinato ======\n\n", 0, ofs);
    high_resolution_clock::time_point t1, t2;
    double duration;

    vector<int> v1 = v_disordinato;
    t1 = high_resolution_clock::now();
    selectionSort(v1);
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    stampaVettoreEDurataSuStream(v1, "\n\n====== Vettore ordinato con selection sort ======\n\n", duration, ofs);

    vector<int> v2 = v_disordinato;
    t1 = high_resolution_clock::now();
    insertionSort(v2);
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    stampaVettoreEDurataSuStream(v2, "\n\n====== Vettore ordinato con insertion sort ======\n\n", duration, ofs);

    vector<int> v3 = v_disordinato;
    t1 = high_resolution_clock::now();
    bubbleSort(v3);
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    stampaVettoreEDurataSuStream(v3, "\n\n====== Vettore ordinato con bubblesort ======\n\n", duration, ofs);


    vector<int> v4 = v_disordinato;
    t1 = high_resolution_clock::now();
    mergeSort(v4);
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    stampaVettoreEDurataSuStream(v4, "\n\n====== Vettore ordinato con mergesort ======\n\n", duration, ofs); 

    vector<int> v5 = v_disordinato; 
    t1 = high_resolution_clock::now();
    quickSortTrivial(v5); 
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>(t2-t1).count();
    stampaVettoreEDurataSuStream(v5, "\n\n====== Vettore ordinato con quicksort con scelta del pivot banale ======\n\n", duration, ofs); 

    vector<int> v6 = v_disordinato; 
    t1 = high_resolution_clock::now();
    quickSortRandom(v6); 
    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>(t2-t1).count();
    stampaVettoreEDurataSuStream(v6, "\n\n====== Vettore ordinato con quicksort randomizzato ======\n\n", duration, ofs); 

return 0;
     } 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}
