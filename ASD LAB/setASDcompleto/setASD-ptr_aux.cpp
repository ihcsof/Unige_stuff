// Nei calcoli di complessita', n indica la dimensione dell'insieme
#include "setASD-ptr.h"

using namespace set;

struct set::cell {
    Elem	elem;
    cell	*next;
};

/****************************************************************/
/* 		  operazioni con side effect                    */
/****************************************************************/

void set::createEmpty(Set& s)
{
   deleteSetS(s);
   s = emptySet;
}

/****************************************************************/
void set::deleteSetS(Set& s){
// Theta(n) in qualunque caso perche' devo scandire tutta la lista collegata.
    Set temp;
    while(s != emptySet) {
        temp=s;
        s = temp->next;
        delete temp;
    }
}

/****************************************************************/
Error set::insertElemInOrderS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' se l'elemento non c'e' ed e' maggiore dell'ultimo elemento (oppure c'e' ed e' uguale all'ultimo elemento) devo scandire tutta la lista collegata
{
    cell *current;
    cell *prev;
    cell *aux;
    try  { aux = new cell; }
    catch(...) { return FAIL;} //heap esaurito
    aux->elem=x;
    aux->next=emptySet;
    
    if (s == emptySet || s->elem>x){
        aux->next=s;
        s=aux;
    }
    else {
        current=s ;
        
        while ((current!=emptySet)&& (current->elem<=x))
        {
            prev=current;
            current=current->next;
        }
        if (prev->elem==x) return OK; // se l'elemento è già presente non faccio nulla
        aux->next=current;
        prev->next=aux;

    }
    return OK;
}


/****************************************************************/
Error set::insertElemS(const Elem x, Set& s) 
// Theta(n) nel caso peggiore perche' devo verificare se l'elemento e' gia' nell'insieme, per non ri-aggiungerlo: se l'elemento non c'e', member deve scandire tutta la lista collegata per restituire false.
{
    if (member(x, s)) 
       return OK; // l'elemento e' gia' presente, non lo aggiungo

    cell *aux;
    try  { aux = new cell; }
    catch(...) { return FAIL;} //heap esaurito
    aux->elem=x;
    aux->next=s;
    s = aux;
    return OK;
}

/****************************************************************/
Error set::deleteElemS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' devo cercare l'elemento per toglierlo; il caso peggiore e' quello in cui l'elemento non c'e' e devo comunque scandire tutta la lista collegata. 
{
    cell* cur=s;
    cell* prev;
    if (s==emptySet)
        return(EMPTY);
    else
    {
        while (cur!=emptySet && cur->elem!=x)
        {
            prev=cur;
            cur=cur->next;
        }
        if (cur!=emptySet)
        {
            if (cur==s)
                s=s->next; //inizio
            else
                prev->next=cur->next;
            delete cur;
            return OK;
        }
        else
            return FAIL;
    }
}


/****************************************************************/
/* 		     operazioni funzionali                      */
/****************************************************************/

Set set::createEmpty()
{
   return emptySet;
}

Set shallowCopy(const Set& s) // serve a creare un nuovo set con gli stessi elementi di quello passato per argomento
// Theta(n), non esiste un caso peggiore: in qualunque caso devo scandire tutta la lista collegata. 
{
if (s == emptySet) 
    return createEmpty();
    
cell *current=s;
cell *aux,  *prev, *first;
try { aux = new cell; }
catch(...) {throw runtime_error("Heap esaurito\n");} //heap esaurito
aux->elem = current->elem;
aux->next = emptySet;
first=aux;
prev=aux;
current = current->next;
while (current != emptySet)
     {
     try { aux = new cell; }
     catch(...) {throw runtime_error("Heap esaurito\n");} 
     aux->elem = current->elem;
     aux->next = emptySet;
     prev->next = aux;
     prev=prev->next;
     current=current->next;
     }
return first;
}


Set set::insertElem(const Elem e, const Set& s)
// Theta(n)
{
    Set aux = shallowCopy(s); 
    insertElemS(e, aux);
    return aux;
}


Set set::deleteElem(const Elem e, const Set& s)
// Theta(n)
{
   Set aux = shallowCopy(s); 
   deleteElemS(e, aux);
   return aux;
}



Set set::setUnion(const Set& s1, const Set& s2)
{
// assumiamo che s1 ed s2 siano insiemi ben formati, ovvero privi di ripetizioni, di dimensioni n1 ed n2 rispettivamente: 
// La complessita' e' O(max(n1*n2, n1, n2)) perché se uno dei due insiemi e' vuoto, devo solo copiare l'altro (Theta(n1) oppure Theta(n2) ma non so quale dei due sia vuoto quindi prendo il O(max(n1,n2))). 
// Se nessuno dei due e' vuoto prima devo cercare ogni elemento del secondo insieme (n2 elementi) nel primo insieme (la ricerca costa n1 e la ripeto n2 volte). Se non c'e', posso inserirlo nell'insieme nuovo in tempo costante perche' inserisco sempre in testa. Poi inserisco nell'insieme unione tutti gli elementi del primo insieme (sono n1 elementi). 
// n1*n2 >= n1 quindi la complessita' nel caso in cui siano entrambi non vuoti e' Theta(n1*n2).

if (isEmpty(s1)) 
    return shallowCopy(s2);

if (isEmpty(s2)) 
    return shallowCopy(s1);

Set s3 = createEmpty();

cell* s1_aux=s1;

while (s1_aux != emptySet) // scandisco s1 per inserirne gli elementi in s3 (non servono controlli, li faro' dopo)
   {   
    cell *aux;
    try  { aux = new cell; }
    catch(...) {throw runtime_error("Heap esaurito\n");} //heap esaurito
    aux->elem=s1_aux->elem;
    aux->next=s3;
    s3 = aux;
    s1_aux=s1_aux->next;
    }

cell* s2_aux=s2;
while (s2_aux != emptySet) // scandisco s2 per inserirne gli elementi in s3
   { 
    if (!member(s2_aux->elem, s1)) // controllando di non inserire elementi di s2 che siano anche in s1
      {cell *aux;
       try  { aux = new cell; }
       catch(...) {throw runtime_error("Heap esaurito\n");} //heap esaurito
       aux->elem=s2_aux->elem; 
       aux->next=s3;
       s3 = aux;
       }
     s2_aux=s2_aux->next;
    }   
return s3;
}


Set set::setIntersection(const Set& s1, const Set& s2)
{
// assumiamo che s1 ed s2 siano insiemi ben formati, ovvero privi di ripetizioni
if (isEmpty(s1)) 
    return createEmpty();

if (isEmpty(s2)) 
    return createEmpty();

Set s3 = createEmpty();

cell* s1_aux=s1;
while (s1_aux != emptySet) // scandisco s1 per inserirne gli elementi che stanno anche in s2, in s3
   {
    if (member(s1_aux->elem, s2)) // controllando di non inserire elementi di s2 che siano anche in s1
      {cell *aux;
       try  { aux = new cell; }
       catch(...) {throw runtime_error("Heap esaurito\n");} //heap esaurito
       aux->elem=s1_aux->elem;
       aux->next=s3;
       s3 = aux;
       }
     s1_aux=s1_aux->next;
    }   

return s3;
}


Set set::setDifference(const Set& s1, const Set& s2)
{
// Implementarla per esercizio
return createEmpty(); // implementazione farlocca, per permettere la compilazione
}





bool set::isSubset(const Set& s1, const Set& s2)
{
// Implementarla per esercizio
return true; // implementazione farlocca, per permettere la compilazione
}


int set::size(const Set& s)
{
int count = 0;
cell* aux = s;
while (aux != emptySet)
   {
   count++;
   aux = aux->next;
   }
return count;
}


bool set::isEmpty(const Set& s)
{
return (s==emptySet);
}


bool set::member(const Elem e, const Set& s)
{
cell* aux = s;
while (aux != emptySet)
   {
   if (aux->elem == e) 
       return true;
   aux = aux->next;
   }
return false;
}


Set setReadFromStream(istream& str)
{
    Set s = createEmpty();
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e!= set::FINEINPUT)  // assumiamo che il segnale di fine input nel file sia il numero  FINEINPUT
    {
    insertElemS(e, s);
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    }
return s;
}


Set setReadFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return setReadFromStream(ifs);
}


Set setReadFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " <<  set::FINEINPUT << " per terminare\n";
    return setReadFromStream((std::cin));
}


void setPrint(const Set& s)
{
cell* aux = s;
cout << endl;
while (aux != emptySet)
   {
   cout << aux->elem << "; "; 
   aux = aux->next;
   }
std::cout << endl;
}
