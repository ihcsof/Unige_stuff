// Nei calcoli di complessita', n indica la dimensione dell'insieme
#include "listASD-array.h"

using namespace list;


List copy(const List& l)
{ 
  Elem* aux = new Elem[l.maxsize];
  for (int i=0; i<l.size; ++i)
     aux[i]=l.list[i];
  List newL;
  newL.list=aux;
  newL.maxsize=l.maxsize;
  newL.size=l.size;
  return newL;
}

/****************************************************************/
/* 		  operazioni con side effect                    */
/****************************************************************/

void list::createEmpty(List& l){
    l.size = 0;
    l.maxsize = BLOCKDIM;
    Elem* aux = new Elem[BLOCKDIM];
    l.list = aux;
}


/****************************************************************/
void list::clear(List& l){
    l.size = 0;
    l.maxsize = BLOCKDIM;
    Elem* aux = new Elem[BLOCKDIM];
    delete[] l.list;

    l.list = aux;
}


/****************************************************************/
void list::set(int pos, Elem e, List& l) // "set" nel senso di "assegna un valore", non nel senso di "insieme"! E' una terminologia standard, non fate confusione con gli insiemi
{
   if (pos < 0 || pos > (l.size)-1) {cout << "\nPosizione fuori range, operazione ignorata\n"; return;}
   l.list[pos] = e;
}


/****************************************************************/
void list::add(int pos, Elem e, List& l) // aggiunge e nella posizione pos
{
   if (pos < 0 || pos > l.size) {cout << "\nPosizione fuori range, operazione ignorata\n"; return;}
   
   if (l.size == l.maxsize) // l'array e' pieno, per poter inserire un nuovo elemento devo ridimensionare l'array espandendolo; l'unico modo e' creare un array piu' grande e copiare in esso gli elementi di l
      {
      cout << "\nMessaggio di sistema: Espansione dell'array\n";
      List auxList;
      auxList.size = l.size+1;
      auxList.maxsize = l.maxsize + BLOCKDIM;
      Elem* auxArray = new Elem[auxList.maxsize];
      auxList.list = auxArray;
      for (int i=0; i<pos; ++i)
          auxList.list[i] = l.list[i];
      auxList.list[pos] = e;
      for (int i=pos+1; i<auxList.size; ++i)
          auxList.list[i] = l.list[i-1];
      delete[] l.list;
      l = auxList; 
      return;
      }

   // se la funzione non ha incontrato un return, vuole dire che pos e' nel range corretto e l'array non e' pieno; devo solo posizionare l'elemento in pos e shiftare a destra gli altri, aggiornando la size della lista
     l.size++;
     for (int i=l.size-1; i>pos; --i)
           l.list[i] = l.list[i-1];
     l.list[pos] = e;
}



/****************************************************************/
void list::addBack(Elem e, List& l) // aggiunge e in coda
{
   add(l.size, e, l);
}


/****************************************************************/
void list::addFront(Elem e, List& l) // aggiunge e in coda
{
   return add(0, e, l);
}

/****************************************************************/
void list::removePos(int pos, List& l)
{
   if (pos < 0 || pos >= l.size) 
     {
      cout << "\nPosizione fuori range, operazione ignorata\n"; 
      return;
     }
  
// se rimuovendo l'elemento si liberano BLOCKDIM celle, allora ridimensioniamo l'array; l'unico modo e' creare un array piu' piccolo e copiare in esso gli elementi di l
   if (l.maxsize-l.size+1==BLOCKDIM && l.maxsize>BLOCKDIM)
   {
      cout << "\nMessaggio di sistema: Contrazione dell'array\n";
      List auxList;
      auxList.size = l.size-1;
      auxList.maxsize = l.maxsize-BLOCKDIM;
      Elem* auxArray = new Elem[auxList.maxsize];
      auxList.list = auxArray;
      for (int i=0; i<pos; ++i)
          auxList.list[i] = l.list[i];
      for (int i=pos; i<auxList.size; ++i)
          auxList.list[i] = l.list[i+1];
      delete[] l.list;
      l = auxList; 
      return;
   }

// se la funzione non ha incontrato un return, vuole dire che pos e' nel range corretto e la lista non puo' essere ridotta di dimensione; devo solo shiftare a sinistra gli altri, aggiornando la size della lista.
     for (int i=pos+1; i<l.size; ++i)
           l.list[i-1]=l.list[i];
     l.size--;
}




/****************************************************************/
/* 		  operazioni senza side effect                    */
/****************************************************************/

List list::createEmpty(){
    List l;
    l.size = 0;
    l.maxsize = BLOCKDIM;
    Elem* aux = new Elem[BLOCKDIM];
    l.list = aux;
    return l;
}

/****************************************************************/
Elem list::get(int pos, const List& l)
{
   if (pos < 0 || pos >= l.size) 
     {
      cout << "\nPosizione fuori range, operazione ignorata, si restituisce " << EMPTYELEM << "\n"; 
      return EMPTYELEM;
     }
   
   return l.list[pos];
}


/****************************************************************/
List list::addF(int pos, Elem e, const List& l)
{
   List newL = copy(l);
   add(pos, e, newL);
   return newL;
}


/****************************************************************/
List list::addBackF(Elem e, const List& l)
{
   List newL = copy(l);
   addBack(e, newL);
   return newL;
}

/****************************************************************/
List list::addFrontF(Elem e, const List& l)
{
   List newL = copy(l);
   addFront(e, newL);
   return newL;
}

/****************************************************************/
List list::setF(int pos, Elem e, const List& l)
{
   List newL = copy(l);
   set(pos, e, newL);
   return newL;
}


/****************************************************************/
List list::removePosF(int pos, const List& l)
{
   List newL = copy(l);
   removePos(pos, newL);
   return newL;
}

/****************************************************************/
bool list::isEmpty(const List& l)
{
   return (l.size == 0);
}

/****************************************************************/
int list::size(const List& l)
{
   return l.size;
}

/****************************************************************/
List readFromStream(istream& str)
{
    List l = createEmpty();       
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        addBack(dato, l);   // aggiunge l'elemento alla fine della lista
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return l;
}

/****************************************************************/
List readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}


/****************************************************************/
List readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}

/****************************************************************/
void print(const List& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << l.list[i] << "; "; 
cout << endl;
}




