#include "labo2_sort.h"
#include <time.h>

void scambia(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i; 
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            { 
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();
   
   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         } 
      
      if (indicesinistra == maxsin && indicedestra < maxdes)
         { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         { 
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }         
   } 
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{
   if (v.size() != 0)
      ms(v, 0, v.size()-1);
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/

int partition(std::vector<int>& v, int fst, int lst) {
	// Scelta del pivot banale in prima posizione
	int pivot = v[fst];
	int i = fst + 1;
	
	// Algoritmo di partition
	for(int j=i; j<=lst; ++j) {
		if(v[j] < pivot) {
			scambia(v, j, i);
			++i;
		}
	}
	// Porto il pivot nella sua posizione definitiva e ritorno il suo indice
	scambia(v, i-1, fst);
	return (i-1);
}

void qs(std::vector<int>& v, int fst, int lst) {
	if(fst < lst) {
		// Salvo l'INDICE del pivot chiamando partition con scelta banale
		int i_pivot = partition(v, fst, lst);
		// Chiamate ricorsive sulle sottoseq.
		qs(v, fst, i_pivot-1);
		qs(v, i_pivot+1, lst);
	}
}

void quickSortTrivial(vector<int>& v)
{
   /* Implementare quickSort banale con partizione in place */
	if(v.size() <= 1)
		return;
	qs(v, 0, v.size()-1);
}

/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/

/*
  --------------------------------------------------------------------------

			Il programma, nella cartella excelMaker, include, oltre al
			normale xls con i tempi di esecuzione, anche un nostro programma
			per eseguire un auto-test che lavori su un file csv.
			Su LibreOffice in ambiente linux l'apertura risulta immediata,
			nel caso di excel potrebbe essere necessaria l'operazione:
			Dati --> Da testo/CSV --> seleziona file -->
				delimitatore: virgola ; 
				Rilevamento del tipo di dati: non rilevare il tipo di dati

  --------------------------------------------------------------------------

	Si sceglie, a discapito della riusabilità di una funzione, per ragioni di
	efficienza, di non creare una funzione apposita per random, ma di includerla
	nella partition (meno chiamate nello stack).
	Inoltre il seme viene generato una sola volta alla prima chiamata della fun.

	int random(std::vector<int>& v, int fst, int lst) {
		
		int r = rand()%(lst-fst) + fst;
		scambia(v, r, fst);
		return partition(v, fst, lst);
	}
*/

int partition_r(std::vector<int>& v, int fst, int lst) {
	// Scelta randomica del pivot
	int r = rand()%(lst-fst) + fst;
	scambia(v, r, fst);

	int pivot = v[fst];
	int i = fst + 1;

	// Algoritmo di partition
	for(int j=i; j<=lst; ++j) {
		if(v[j] < pivot) {
			scambia(v, j, i);
			++i;
		}
	}
	// Porto il pivot nella sua posizione definitiva e ritorno il suo indice
	scambia(v, i-1, fst);
	return (i-1);
}

void qs_r(std::vector<int>& v, int fst, int lst) {
	if(fst < lst) {
		// Salvo l'INDICE del pivot chiamando partition con scelta randomica
		int i_pivot = partition_r(v, fst, lst);
		// Chiamate ricorsive sulle sottoseq.
		qs_r(v, fst, i_pivot-1);
		qs_r(v, i_pivot+1, lst);
	}
}

void quickSortRandom(vector<int>& v)
{
   /* Implementare quickSort randomizzato con partizione in place */
	if(v.size() <= 1)
		return;
	// Genero il seme all'inizio per ottimizzazione
	srand(time(NULL));
	qs_r(v, 0, v.size()-1);
}
