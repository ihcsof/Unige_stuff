// Nei calcoli di complessita', n indica la dimensione del dizionario

#include "dictionary.h"

using namespace dict;

struct dict::nodo {
    Elem elem;
    nodo *precedente;
    nodo *prossimo;
};

typedef nodo *nodoPtr;

/****************************************************************/
Dictionary1 readFromFile1(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict1();}  
    // cout << "\n[dict::readFromFile] Apertura file completata\n";
    return readFromStream1(ifs);
}

/****************************************************************/
Dictionary1 readFromStream1(istream& str)
{
    Dictionary1 d = createEmptyDict1();      
    string key, kcopy;
    string value;
    getline (str, key, ':'); // cout << "\n[readFromStream] key: " << key;
    getline (str, value); // cout << "\n[readFromStream] value: " << value;
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


/****************************************************************/
// Inizializzazione della lista con creazione del nodo sentinella; obbligatorio dopo la dichiarazione di una lista
Dictionary1 dict::createEmptyDict1()
{
    // Crea il nodo sentinella
    nodoPtr l = new nodo;
    // Concatenalo circolarmente a se stesso
    l->precedente = l->prossimo = l;

    return l;
}


/****************************************************************/
// Inserimento di un record prima del nodo puntato da p 
void inserisci_prima(nodoPtr &p, Key k, Value v)
{
    nodoPtr q = new nodo;
    (q->elem).key = k;
    (q->elem).value = v;
    q->precedente = p->precedente;
    q->prossimo = p;
    p->precedente = q;
    q->precedente->prossimo=q;
}

/****************************************************************/
// Restituisce il puntatore al primo nodo nella lista che contiene una chiave >= k nella lista
nodoPtr maggiore_o_uguale(Key k, const Dictionary1& s){
    // "salta la sentinella" e va alla testa della lista
    nodoPtr q = s->prossimo;
    // avanza finche' non finisce la lista o non trovi una chiave >= k
    while (q != s && (q->elem).key < k )
	q = q->prossimo;
    return q;
}

/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary1& s)
{
    if (search(k, s) != emptyValue) return FAIL; // l'elemento e' gia' presente nel dizionario, non lo ri-inserisco

    // Cerco dove inserire n
    nodoPtr magg_uguale = maggiore_o_uguale(k, s);
    // Lo inserisco
    inserisci_prima(magg_uguale, k, v);
    return OK;
}


/****************************************************************/
Value dict::search(const Key k, const Dictionary1& s)
{
    nodoPtr last = s->precedente;
    if (last == s) return emptyValue; // il dizionario e' vuoto
    else if ((last->elem).key < k) return emptyValue; // il dizionario contiene tutte chiavi < k (l'ultimo elemento e' < k)

    // "salta la sentinella" e va alla testa della lista
    nodoPtr q = s->prossimo;
    // avanza finche' non finisce la lista o non trovi una chiave >= k
    while (q != s && (q->elem).key < k )
	q = q->prossimo;

    if (q==s || (q->elem).key < k) return emptyValue;
    else if ((q->elem).key == k) return (q->elem).value; 

    return emptyValue;
}

void erase_aux(Dictionary1& sFirst, Dictionary1& s) {
	if(s == sFirst) return;
	erase_aux(sFirst, s->prossimo);
	delete s;
}

void dict::erase(Dictionary1& s) {
	Dictionary1 aux = s->prossimo;
	erase_aux(s, aux);
	delete s;
	s = nullptr;
}
