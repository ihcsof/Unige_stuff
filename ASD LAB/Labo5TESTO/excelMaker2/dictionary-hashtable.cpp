#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::cell {
   Elem	elem;
	cell	*next;
};

int dict::tableDim;

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int dict::h1(Key s) // funzione di hash che considera unicamente il valore ascii del primo carattere della chiave (se esiste) e restituisce il resto della divisione di tale valore per tableDim 
{
	if(s.size() == 0)
		throw "Error: invalid key";
	return ((int)s[0] % tableDim);
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int dict::h2(Key s) // funzione di hash che somma il codice ascii di ogni carattere nella chiave e restituisce il resto della divisione di tale somma per tableDim 
{
	if(s.size() == 0)
		throw "Error: invalid key";
	int ascii = 0;
	for(int i = 0; i < s.size(); ++i)
		ascii += s[i];
	return (ascii % tableDim);
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int dict::h3(Key s) // funzione di hash diversa da h1 ed h2, che progettate e implementate voi seguendo qualche criterio che vi sembra ragionevole
{
	if(s.size() == 0)
		throw "Error: invalid key";
	int s1 = s.size()/2;
	int s2 = s.size()/3;
	int toRet = (unsigned) s.at(s1) * (unsigned) s.at(s2) % tableDim;
	return toRet;
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/

// Ausiliaria is_in
Value is_in(Bucket b, const Key &k) {
	if(b == emptyBucket)
		return emptyValue;
	if(b->elem.key == k)
		return b->elem.value;
	return is_in(b->next, k);
}

Value dict::search(const Key k, const Dictionary& s, hashPointer p)
{	
  try {
		Bucket b = s[p(k)];
		return is_in(b, k);
	}
	catch(const char& err) {
		std::cout << err << std::endl;
		return emptyKey;
	}
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/

Error dict::insertElem(const Key k, const Value v,  Dictionary& s, hashPointer p)
{
	try {
		// Assegnazione con indirizzo per la modifica del punt. costante
		Bucket* b = &s[p(k)];
		// Se l'elemento esiste già: interpreto OK
		if(is_in(*b, k) != emptyValue)
			return FAIL;
		// Inserimento in testa
		cell* aux = new cell;
		aux->elem.key = k;
		aux->elem.value = v;
		aux->next = *b;
		*b = aux;
   	return OK;
	}
	catch(const char& err) {
		std::cout << err << std::endl;
		return FAIL;
	}
}


/****************************************************************/
Dictionary dict::createEmptyDict()
{
   Bucket* d = new Bucket[tableDim];
   for (int i=0; i < tableDim; ++i)
      d[i]=emptyBucket;
   return d;
}

// Ausiliarie per evitare mem leaks

void deleteBucket(Bucket& b) {
	if(b == emptyBucket) return;
	deleteBucket(b->next);
	delete b;
}

void dict::deleteD(Dictionary& d) {
	for (unsigned int i=0; i<tableDim; ++i)
		deleteBucket(d[i]);
	delete[] d;
	d = nullptr;
}

/****************************************************************/
Dictionary readFromFile(string nome_file, hashPointer p)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict();}  
    return readFromStream(ifs, p);
}

/****************************************************************/
Dictionary readFromStream(istream& str, hashPointer p)
{
    Dictionary d = createEmptyDict();   
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d, p); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline (str, key, ':'); 
        getline (str, value); 
    }
    str.clear();
    return d;
}


/****************************************************************/
int countBucket(Bucket b) // stampa il contenuto di un bucket e restituisce il numero di elementi contenuti nel bucket stesso
{  
   int counter = 0;
   while(b!=emptyBucket) {
         counter++;
		   b=b->next;
	}
   return counter;	
}

/****************************************************************/
void print(const Dictionary& s, std::ostream& o) {
	// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
	int bucketDim[tableDim];
	int totalElem = 0;
	for (unsigned int i=0; i<tableDim; ++i) {
		 bucketDim[i] = countBucket(s[i]);
		 totalElem += bucketDim[i]; 
	}
	float means = totalElem/(float)tableDim;
	float standardDevSum = 0;
	for (unsigned int i=0; i<tableDim; ++i)
		  standardDevSum += (bucketDim[i]-means)*(bucketDim[i]-means);
		
	/* Lo scarto tipo, deviazione standard, o scarto quadratico medio e' un indice di dispersione statistico, vale a dire una stima della variabilita' di una popolazione di dati o di una variabile casuale.
	Lo scarto tipo e' uno dei modi per esprimere la dispersione dei dati intorno ad un indice di posizione, quale puo' essere, ad esempio, la media aritmetica. */

	o << totalElem << ",";
	o << tableDim << ",";
	if (tableDim != 0) 
		o << means << "," << sqrt(standardDevSum/tableDim) << ",";
}



