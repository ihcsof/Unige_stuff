// Nei calcoli di complessita', n indica la dimensione dell'insieme
#include "setASD-array.h"

using namespace set;


void swap(List& v, int i, int j)
{ 
  Elem tmp = list::get(j, v);
  list::set(j, get(i, v), v);
  list::set(i, tmp, v);
}


Set shallowCopy(const Set& l) // serve a creare un nuovo set con gli stessi elementi di quello passato per argomento
{ 
  Elem* aux = new Elem[l.maxsize];
  for (int i=0; i<l.size; ++i)
     aux[i]=l.list[i];
  Set newL;
  newL.list=aux;
  newL.maxsize=l.maxsize;
  newL.size=l.size;
  return newL;
}

/****************************************************************/
/* 		  operazioni con side effect                    */
/****************************************************************/


void set::createEmpty(Set& s)
{ 
   list::createEmpty(s);
}

/****************************************************************/
void set::deleteSetS(Set& s)
{
   list::clear(s);
}

/****************************************************************/
set::Error set::insertElemInOrderS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' se l'elemento non c'e' ed e' maggiore dell'ultimo elemento (oppure c'e' ed e' uguale all'ultimo elemento) devo scandire tutto il vector
{
    for (int i=0; i<list::size(s); ++i)
    {
    if (list::get(i,s)==x) 
       return OK;

    if (list::get(i,s)>x)
       {
       list::addBack(x,s);
       for (int j=list::size(s)-1; j>i; j--)
          swap(s, j, j-1);
       return OK;
       }
    }
    return OK;
}


/****************************************************************/
set::Error set::insertElemS(const Elem x, Set& s) 
// Theta(n) nel caso peggiore perche' devo verificare se l'elemento e' gia' nell'insieme, per non ri-aggiungerlo: se l'elemento non c'e', member deve scandire tutta la lista collegata per restituire false.
{
    if (member(x, s)) 
       return OK; // l'elemento e' gia' presente, non lo aggiungo

    list::addBack(x, s);
    return OK;
}

/****************************************************************/
set::Error set::deleteElemS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' devo cercare l'elemento per toglierlo; quando lo trovo, se voglio preservare l'ordine degli elementi (caratteristica non richiesta in un insieme) devo spostare tutti gli elementi di uno verso sinistra, fino al punto in cui ho trovato l'elemento; altrimenti posso scambiare l'elemento trovato con l'ultimo elemento e cancellare solo l'ultimo elemento (non preservo l'ordine). 
{
/* Implementazione che preserva l'ordine; inutile per come abbiamo implementato gli insiemi, ma potrebbe servire per altri tipi di dato */
/*    for (int i=0; i<s.size(); ++i)
    {
    if (s[i]==x) 
       {
       for (int j=i+1;j<s.size();j++)
          s[j-1]=s[j];
        s.resize(s.size()-1);
        return OK;
       }
    }
    return OK;
*/


/* Implementazione che NON preserva l'ordine; ok per la nostra rappresentazione degli insiemi in cui l'ordine degli elementi non interessa */
   for (int i=0; i<list::size(s); ++i)
    {
    if (list::get(i, s) == x) 
       {
       swap(s, i, list::size(s)-1);
       list::removePos(list::size(s)-1, s); 
       return OK;
       }
    }
    return OK;
}



/****************************************************************/
/* 		     operazioni funzionali                      */
/****************************************************************/


Set set::createEmpty()
{ 
   return list::createEmpty();
}

Set set::insertElem(const Elem e, const Set& s) // resta definita nello stesso mode che con le liste semplici!!!!
{
    Set aux = shallowCopy(s); 
    insertElemS(e, aux);
    return aux;
}


Set set::deleteElem(const Elem e, const Set& s) // resta definita nello stesso mode che con le liste semplici!!!!
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

if (set::isEmpty(s1)) 
    return shallowCopy(s2);

if (set::isEmpty(s2)) 
    return shallowCopy(s1);

Set s3 = shallowCopy(s1);

for (int i=0; i<list::size(s2); ++i)
   if (!member(list::get(i, s2), s1))
      list::addBack(list::get(i, s2), s3);

return s3;
}


Set set::setIntersection(const Set& s1, const Set& s2)
{
// assumiamo che s1 ed s2 siano insiemi ben formati, ovvero privi di ripetizioni
if (set::isEmpty(s1)) 
    return set::createEmpty();

if (set::isEmpty(s2)) 
    return set::createEmpty();

Set s3 = set::createEmpty();

for (int i=0; i<list::size(s2); ++i)
   if (member(get(i, s2), s1))
      list::addBack(list::get(i, s2), s3);

return s3;
}


Set set::setDifference(const Set& s1, const Set& s2)
{
// Implementarla per esercizio
return set::createEmpty(); // implementazione farlocca, per permettere la compilazione
}


bool set::isSubset(const Set& s1, const Set& s2)
{
// Implementarla per esercizio
return true; // implementazione farlocca, per permettere la compilazione
}


int set::size(const Set& s)
{
return list::size(s);  
}


bool set::isEmpty(const Set& s)
{
return list::isEmpty(s);
}


bool set::member(const Elem e, const Set& s) // non faccio assunzioni sul fatto che il vettore sia ordinato, quindi devo scandire tutto il vettore (Theta(n) nel caso peggiore in cui l'elemento non c'é)
{
for (int i=0; i<list::size(s); ++i)
   if (list::get(i, s)==e) return true;

return false;
}


Set setReadFromStream(istream& str)
{
    Set v = set::createEmpty();      
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= set::FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  set::FINEINPUT
        {          
        insertElemS(dato, v);   // put into set
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return v;
}

Set setReadFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return setReadFromStream(ifs);
}


Set setReadFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << set::FINEINPUT << " per terminare\n";
    return setReadFromStream((std::cin));
}





void setPrint(const Set& s)
{
cout << endl;
for (int i=0; i<s.size; ++i)
   cout << s.list[i] << "; "; 
cout << endl;
}
