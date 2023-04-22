#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::cell {
   Elem	elem;
	cell	*next;
};


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int h1(Key s) // funzione di hash che considera unicamente il valore ascii del primo carattere della chiave (se esiste) e restituisce il resto della divisione di tale valore per tableDim 
{
	if(s.size() == 0)
		throw "Error: invalid key";
	return ((int)s[0] % tableDim);
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int h2(Key s) // funzione di hash che somma il codice ascii di ogni carattere nella chiave e restituisce il resto della divisione di tale somma per tableDim 
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
int h3(Key s) // funzione di hash diversa da h1 ed h2, che progettate e implementate voi seguendo qualche criterio che vi sembra ragionevole
{
	if(s.size() == 0)
		throw "Error: invalid key";
	int s1 = s.size()/2;
	int s2 = s.size()/3;
	int toRet = (unsigned) s.at(s1) * (unsigned) s.at(s2) % tableDim;
	return toRet;		
}

/****************************************************************/
/*    FUNZIONE DA MODIFICARE PER FARE ESPERIMENTI DIVERSI       */
/****************************************************************/
int h(Key s)
{
  	 return h1(s); // modificare questa chiamata per sperimentare l'utilizzo delle funzioni di hash h1, h2, h3, definite prima
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/

Error dict::deleteElem(const Key k, Dictionary& s)
{
	try {
		Bucket* b = &s[h(k)];
		if (*b == emptyBucket)
			return FAIL;
		while (((*b) -> elem).key != k && ((*b) -> next) != emptyBucket)
			b = &((*b) -> next);
		if (((*b) -> elem).key != k)
			return FAIL;
		cell* tmp = *b;
		*b = (*b) -> next;
		delete tmp;
		return OK;
	}
	catch(const char& err) {
		std::cout << err << std::endl;
		return FAIL;
	}	
} 

/* Versione normale
Error dict::deleteElem(const Key k, Dictionary& s)
{
	try {
		// Assegnazione con indirizzo per la modifica del punt. costante
		Bucket *b = &s[h(k)];
		Bucket cur = *b;
		Bucket prev = emptyBucket;

		//SCORRO LA LISTA fino alla prima occorrenza (o alla fine)
		while((cur != emptyBucket) && (cur->elem.key != k)) {
			prev = cur;
			cur = cur->next;
		}

		//Se sono arrivato all'indice di mio interesse e non alla fine ("oltre")
		if(cur != emptyBucket) {
			//se voglio eliminare la prima cella, punto dir. alla 2nda
			if(cur == *b)
				*b = (*b)->next;
			//Sennò "faccio un salto" (almeno una volta sono entrato nel ciclo)
			else
				prev->next = cur->next;
				
			delete cur;
			return OK;
		}
		return FAIL;
	}
	catch(const char& err) {
		std::cout << err << std::endl;
		return FAIL;
	}	
} */

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/

// Ausiliaria is_in
Value is_in(Bucket b, const Key &k) {
	// Caso : elem non trovato
	if(b == emptyBucket)
		return emptyValue;
	// Caso: elem trovato
	if(b->elem.key == k)
		return b->elem.value;
	return is_in(b->next, k);
}

Value dict::search(const Key k, const Dictionary& s)
{	
  try {
		// Riutilizzo di is_in in search per modularità
		Bucket b = s[h(k)];
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

Error dict::insertElem(const Key k, const Value v,  Dictionary& s)
{
	try {
		// Assegnazione con indirizzo per la modifica del punt. costante
		Bucket* b = &s[h(k)];
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


/****************************************************************/
Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict();}  
    return readFromStream(ifs);
}


/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}


/****************************************************************/
Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();     
    string key, kcopy;
    string value;
	 cin.ignore();
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


/****************************************************************/
int printBucket(Bucket b) // stampa il contenuto di un bucket e restituisce il numero di elementi contenuti nel bucket stesso
{  
   int counter = 0;
   while(b!=emptyBucket) {
        counter++;
        cout << (b->elem).key << ": " << (b->elem).value << "\n"; 
	b=b->next;
	}
   return counter;	
}


/****************************************************************/
void print(const Dictionary& s)
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
int bucketDim[tableDim];
int totalElem = 0;
for (unsigned int i=0; i<tableDim; ++i)
   {
    cout << "\nBucket " << i << "\n\n";
    bucketDim[i] = printBucket(s[i]);
    totalElem += bucketDim[i]; 
   }
float means = totalElem/(float)tableDim;
float standardDevSum = 0;
for (unsigned int i=0; i<tableDim; ++i)
     standardDevSum += (bucketDim[i]-means)*(bucketDim[i]-means);
   
/* Lo scarto tipo, deviazione standard, o scarto quadratico medio e' un indice di dispersione statistico, vale a dire una stima della variabilita' di una popolazione di dati o di una variabile casuale.
Lo scarto tipo e' uno dei modi per esprimere la dispersione dei dati intorno ad un indice di posizione, quale puo' essere, ad esempio, la media aritmetica. */

cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===\n";

for (unsigned int i=0; i<tableDim; ++i)
   cout << "\nBucket " << i << ": " << bucketDim[i] << " elementi";

cout << "\nIl numero totale di elementi memorizzati e' " << totalElem;
cout << "\nIl numero di bucket nel dizionario e' " << tableDim;
if (tableDim != 0) cout << "\nIl numero atteso di elementi per bucket e' " << means << "\nLa deviazione standard e' " << sqrt(standardDevSum/tableDim);
}



