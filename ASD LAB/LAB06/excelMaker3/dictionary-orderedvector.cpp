#include "dictionary.h"


using namespace dict;

/****************************************************************/
void swap(Dictionary2& v, int i, int j)
{ 
  Elem tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/****************************************************************/
Value binSearch(int start, int end, const Dictionary2& d, Key k)
// implementazione della ricerca binaria per rendere efficiente l'operazione search
{
if (start==end)
   {
   if (d[start].key==k) return d[start].value;
   else return emptyValue;
   }
  
int mid = (start+end)/2;

if (d[mid].key==k) return d[mid].value;

if (k > d[mid].key) return binSearch(mid+1,end,d,k); 
else return binSearch(start,mid,d,k); 
}


/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary2& s)
// inserisco in modo da mantenere l'ordine delle chiavi
{
   if (s.size()==0 || s[s.size()-1].key < k) // se il dizionario e' vuoto oppure se devo inserire dopo l'ultimo elemento (la chiave dell'ultimo elemento e' minore della chiave che voglio inserire), lo faccio senza scandire nulla e restituisco OK
      {
       Elem e; 
       e.key = k;
       e.value = v;
       s.push_back(e);   
       return OK;
      }

 for (int i=0; i<(int)s.size(); ++i)
    {
    if (s[i].key==k) // se trovo la chiave, non la re-inserisco
       return FAIL;

    if (s[i].key>k) // trovo il punto in cui devo inserire la coppia (chiave, valore)
       {
       Elem e; 
       e.key = k;
       e.value = v;
       s.push_back(e); // metto il nuovo elemento in fondo
       for (int j=(int)s.size()-1; j>i; j--) // lo scambio con i precedenti finche' non arriva al suo posto
          swap(s, j, j-1);
       return OK;
       }
    }
    return OK;
}

/****************************************************************/
Value dict::search(const Key k, const Dictionary2& s)
{

if (s.size() == 0 || s[s.size()-1].key < k) return emptyValue; // ottimizzazione: se il dizionario è vuoto non posso trovare nulla; se cerco qualcosa di più grande rispetto all'ultimo elemento, non posso trovarlo ed e' inutile cercare nel dizionario
return binSearch(0, s.size()-1, s, k);
}


/****************************************************************/
Dictionary2 dict::createEmptyDict2()
{
return Dictionary2(0);
}


/****************************************************************/
Dictionary2 readFromFile2(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict2();}  
    return readFromStream2(ifs);
}

/****************************************************************/
Dictionary2 readFromStream2(istream& str)
{
    Dictionary2 d = createEmptyDict2();     
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value);   
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d);
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}
