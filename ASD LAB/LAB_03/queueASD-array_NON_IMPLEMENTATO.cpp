#include "queueASD-array.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
Queue queue::createEmpty()
{
	// Impostazione di una nuova coda vuota
   Queue q;
	q.queue = new Elem[BLOCKDIM];
	q.size = 0;
	q.maxsize = BLOCKDIM;
   return q;
}

/****************************************************************/

// Funzione ausiliaria di Resize
void resize(Queue& q) {
	// Discriminante tra enqueue (j=0) e dequeue (j=1) per riutilizzo del codice
	// se enqueue: copia normale da 0
	// se dequeue: copia con shift escludendo il primo elem e copiando l'ultimo
	int j = (q.size == q.maxsize);
	// Creiamo un nuovo array, copiamo i valori del vecchio
	Elem* newQ = new Elem[q.maxsize];
	for(int i=0; i<q.size; ++i)
		newQ[i] = q.queue[j++]; // j must go on!
	// delete del vecchio e ritorniamo
	delete[] q.queue;
	q.queue = newQ;
}

void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
	// Se serve un resize, aumento di BLOCKDIM e chiamo l'ausiliaria
   if(l.size == l.maxsize) {
		l.maxsize += BLOCKDIM;
		resize(l);
	}
	// Dopo un eventuale resize, aggiungo l'elemento ( <--[][][]<-- )
	l.queue[l.size] = e;
	l.size++;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
	if(isEmpty(l)) return EMPTYELEM;
	// Salvo l'elemento da ritornare
   Elem toRet = l.queue[0];
	// Diminuisco la size
	l.size--;

	// Se ho necessità di un resize (scalare al precedente multiplo)
	if((l.size == l.maxsize - BLOCKDIM) && (l.maxsize > BLOCKDIM)) {
		// Scalo, effettuo il resize, e ritorno
		l.maxsize -= BLOCKDIM;
		resize(l);
		return toRet;
	}
	// Shift
	for(int i=0; i<l.size; i++)
		l.queue[i] = l.queue[i+1];
	
	return toRet;
}


/****************************************************************/
Elem queue::first(Queue& l) // restituisce il primo elemento
{
	// Se la coda è vuota, ritorniamo EMPTYELEM
	if(isEmpty(l)) return EMPTYELEM;
   return l.queue[0];
}


/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
   return (l.size == 0);
}

/****************************************************************/
Queue readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}


/****************************************************************/
Queue readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}


/****************************************************************/
Queue readFromStream(istream& str)
{
    Queue l = createEmpty();        
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        enqueue(dato, l);   // aggiunge l'elemento alla fine della coda
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return l;
}

/****************************************************************/
void print(const Queue& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << l.queue[i] << "; "; 
cout << endl;
}
