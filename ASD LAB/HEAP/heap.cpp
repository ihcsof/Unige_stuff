#include "heap.h"

using namespace heap;


/****************************************************************/
array heap::createEmpty()
{
	// Impostazione di una nuova coda vuota
   array q;
	q.a = new Elem[BLOCKDIM];
	q.size = 0;
	q.maxsize = BLOCKDIM;
   return q;
}

/****************************************************************/

// Funzione ausiliaria di Resize
void resize(array& l) {
	// Creiamo un nuovo array, copiamo i valori del vecchio
	Elem* newA = new Elem[l.maxsize];
	for(int i=0; i<l.size; ++i)
		newA[i] = l.a[i];
	// delete del vecchio e ritorniamo
	delete[] l.a;
	l.a = newA;
}

void swap(Elem& a, Elem& b) {
	Elem tmp = a;
	a = b;
	b = tmp;
}

void heap::insertElem(Elem e, array& l) // aggiunge e in coda
{
	// Se serve un resize, aumento di BLOCKDIM e chiamo l'ausiliaria
   if(l.size == l.maxsize) {
		l.maxsize += BLOCKDIM;
		resize(l);
	}
	// Dopo un eventuale resize, aggiungo l'elemento ( <--[][][]<-- )
	l.a[l.size++] = e;

	// Swap con formule per heap con partenza da 0 (floor(i-1)/2) (i = l.size-1)
	// j è il figlio (parte dall'ultima pos), i è il padre: verranno man mano aggiornati
	int j = l.size-1;
	int i = (l.size-2)/2;

	while(i >= 0 && l.a[i] < e) {
		swap(l.a[i], l.a[j]);
		j = i;
		i = (i-1) / 2;
	}
}


/****************************************************************/
Elem heap::deleteMax(array& l) // rimuove il primo elemento e lo restituisce
{
	if(isEmpty(l)) return EMPTYELEM;
	// Salvo l'elemento da ritornare e scambio radice con lastElem (decrementando size)
   Elem toRet = l.a[0];
	l.a[0] = l.a[--l.size];

	// Se ho necessità di un resize (scalare al precedente multiplo)
	if((l.size == l.maxsize - BLOCKDIM) && (l.maxsize > BLOCKDIM)) {
		// Scalo, effettuo il resize, e ritorno
		l.maxsize -= BLOCKDIM;
		resize(l);
	}

	// Salvo i (radice) e primo figlio
	int i = 0;
	int j = 2*i;

	// Ciclo fino all'ultimo nodo con 2 figli
	while(j + 2 < l.size) {
		// Aumento j con 1 o 2 a seconda del figlio maggiore (val. bool)
		j += 1 + (l.a[j+1] < l.a[j+2]);
		// Se a[i] è maggiore del figlio maggiore OK
		if(l.a[i] > l.a[j])
			return toRet;
		// Sennò swappo e aggiorno gli indici (padre->figlio, figlio->nuovo figlio)
		swap(l.a[i], l.a[j]);
		i = j;
		j = 2*i;
	}

	// Caso con un altro nodo con 1 solo figlio (prop. alb. bin. quasi compl.)
	if(++j < l.size && l.a[i] < l.a[j])
		swap(l.a[i], l.a[j]);
	
	return toRet;
}


/****************************************************************/
Elem heap::findMax(array& l) // restituisce il primo elemento
{
	// Se la coda è vuota, ritorniamo EMPTYELEM
	if(isEmpty(l)) return EMPTYELEM;
   return l.a[0];
}


/****************************************************************/
bool heap::isEmpty(const array& l)
{
   return (l.size == 0);
}

/****************************************************************/
array readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}


/****************************************************************/
array readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}


/****************************************************************/
array readFromStream(istream& str)
{
    array l = createEmpty();        
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        insertElem(dato, l);   // aggiunge l'elemento alla fine della coda
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return l;
}

/****************************************************************/
void print(const array& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << l.a[i] << "; "; 
cout << endl;
}
