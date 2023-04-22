// Nei calcoli di complessita', n indica la dimensione dell'insieme
#include "setASD-vector.h"

using namespace set;


void swap(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

/****************************************************************/
/* 		  operazioni con side effect                    */
/****************************************************************/

/****************************************************************/
void set::createEmpty(Set& s){
   s.clear();
}


/****************************************************************/
void set::deleteSetS(Set& s){
   s.clear();
}

/****************************************************************/
Error set::insertElemInOrderS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' se l'elemento non c'e' ed e' maggiore dell'ultimo elemento (oppure c'e' ed e' uguale all'ultimo elemento) devo scandire tutto il vector
{

    if (s.size()==0 || s[(int)s.size()-1] < x)
    	s.push_back(x);

    for (int i=0; i<(int)s.size(); ++i)
    {
    if (s[i]==x) 
       return OK;

    if (s[i]>x)
       {
       s.push_back(x);
       for (int j=(int)s.size()-1; j>i; j--)
          swap(s, j, j-1);
       return OK;
       }
    }
    return OK;
}


/****************************************************************/
Error set::insertElemS(const Elem x, Set& s) 
// Theta(n) nel caso peggiore perche' devo verificare se l'elemento e' gia' nell'insieme, per non ri-aggiungerlo: se l'elemento non c'e', member deve scandire tutta la lista collegata per restituire false.
{
    if (member(x, s)) 
       return OK; // l'elemento e' gia' presente, non lo aggiungo

    s.push_back(x);
    return OK;
}

/****************************************************************/
Error set::deleteElemS(const Elem x, Set& s)
// Theta(n) nel caso peggiore perche' devo cercare l'elemento per toglierlo; quando lo trovo, se voglio preservare l'ordine degli elementi (caratteristica non richiesta in un insieme) devo spostare tutti gli elementi di uno verso sinistra, fino al punto in cui ho trovato l'elemento; altrimenti posso scambiare l'elemento trovato con l'ultimo elemento e cancellare solo l'ultimo elemento (non preservo l'ordine). 
{
/* Implementazione che preserva l'ordine; inutile per come abbiamo implementato gli insiemi, ma potrebbe servire per altri tipi di dato */
/*    for (unsigned int i=0; i<s.size(); ++i)
    {
    if (s[i]==x) 
       {
       for (unsigned int j=i+1;j<s.size();j++)
          s[j-1]=s[j];
        s.resize(s.size()-1);
        return OK;
       }
    }
    return OK;
*/


/* Implementazione che NON preserva l'ordine; ok per la nostra rappresentazione degli insiemi in cui l'ordine degli elementi non interessa */
   for (unsigned int i=0; i<s.size(); ++i)
    {
    if (s[i]==x) 
       {
       swap(s, i, s.size()-1);
       s.pop_back();
       return OK;
       }
    }
    return OK;
}


/****************************************************************/
/* 		     operazioni funzionali                      */
/****************************************************************/

Set set::createEmpty(){
   Set v;
   return v;
}


Set shallowCopy(const Set& s) // serve a creare un nuovo set con gli stessi elementi di quello passato per argomento
{
// con i vettori la shallow copy viene fatta automaticamente se assegnamo a un vettore il valore di un altro... approfittiamone...
    Set v = s;
    return v;
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

if (isEmpty(s1)) 
    return shallowCopy(s2);

if (isEmpty(s2)) 
    return shallowCopy(s1);

Set s3 = shallowCopy(s1);

for (unsigned int i=0; i<s2.size(); ++i)
   if (!member(s2[i], s1))
      s3.push_back(s2[i]);

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

for (unsigned int i=0; i<s2.size(); ++i)
   if (member(s2[i], s1))
      s3.push_back(s2[i]);

return s3;
}


Set set::setDifference(const Set& s1, const Set& s2)
{
// Implementarla per esercizio
return set::createEmpty(); // implementazione farlocca, per permettere la compilazione
}


bool set::isSubset(const Set& s1, const Set& s2)
{
	// Ottimizzazione grazie all'accesso diretto
	if(set::size(s1) > set::size(s2))
		return false;
	// Ritorno falso se qualche elemento non è presente
	for (unsigned int i=0; i<set::size(s1); ++i)
   	if (!member(s1[i], s2))
      	return false;

	return true;
}


int set::size(const Set& s)
{
return s.size();  // anche qui approfittiamo volentieri di un'operazione che i vettori ci offrono!
}


bool set::isEmpty(const Set& s)
{
return (s.size()==0);
}


bool set::member(const Elem e, const Set& s) // non faccio assunzioni sul fatto che il vettore sia ordinato, quindi devo scandire tutto il vettore (Theta(n) nel caso peggiore in cui l'elemento non c'é)
{
for (unsigned int i=0; i<s.size(); ++i)
   if (s[i]==e) return true;

return false;
}


Set setReadFromStream(istream& str)
{
    Set v;        // vettore di dati (numeri interi diversi da  FINEINPUT
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= set::FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {          
        insertElemS(dato, v);   // put into vector
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
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return setReadFromStream((std::cin));
}


void setPrint(const Set& s)
{
cout << endl;
for (unsigned int i=0; i<s.size(); ++i)
   cout << s[i] << "; "; 
cout << endl;
}
