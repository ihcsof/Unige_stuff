#include "stackASD-ptr.h"

using namespace stack;


struct stack::cell {
    Elem	elem;
    cell	*next;
};


/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
	return(s == EMPTYSTACK);
}


/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
	 // Creo una nuova cella, la aggiungo in testa
    cell* newElem = new cell;
	 newElem->elem = x;
	 newElem->next = s;
	 s = newElem;
}

/****************************************************************/
Elem stack::pop(Stack& s)
{
	// Se lo stack è vuoto, ritorno EMPTYELEM (si poteva lanciare eccezione)
   if(isEmpty(s)) return EMPTYELEM;
	// Salvo l'elemento, salto di una posizione, elimino e ritorno il suddetto
	Stack tmp = s;
	Elem toRet = s->elem;
	s = s->next;
	delete tmp;
	return toRet;
}


/****************************************************************/
Elem stack::top(Stack& s)
{
	 // Se lo stack è vuoto, ritorno EMPTYELEM (si poteva lanciare eccezione)
	 if(isEmpty(s)) return EMPTYELEM;
	 // Ritorno l'elemento in cima
    return(s->elem);
}



Stack readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}



Stack readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " <<  FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}



Stack readFromStream(istream& str)
{
    Stack s = EMPTYSTACK;
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia il numero  FINEINPUT
    {
    push(e, s);
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    }
return s;
}



void print(const Stack& s)
{
cell* aux = s;
cout << endl;
while (aux != EMPTYSTACK)
   {
   cout << aux->elem << "; "; 
   aux = aux->next;
   }
std::cout << endl;
}
