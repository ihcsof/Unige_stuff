#include "dictionary.h"

using namespace dict;

struct dict::cell {
   Elem	elem;
	cell	*leftChild;
	cell	*rightChild;
};

// Ausiliaria per creare un nodo (non parte del namespace)

cell* createCell(const Key k, const Value v) {
	cell* newCell = new cell;
	newCell->elem.key = k;
	newCell->elem.value = v;
	newCell->leftChild = emptyBst;
	newCell->rightChild = emptyBst;
	return newCell;
}

//Ausiliaria deleteMin per la deleteElem
Elem deleteMin(Dictionary& s) {
	// Se non c'è un leftChild (siamo nella pos più a sx del sottoalbero dx)
	if(s->leftChild == emptyBst) {
		// Salvo il puntatore e l'elemento
		cell* aux = s;
		Elem toRet = s->elem;
		// Salto al figlio destro (se non c'è: emptyBst)
		s = s->rightChild;
		// Cancello la cella del min e lo ritorno per fargli assumere la nuova pos
		delete aux;
		return toRet;
	}
	return deleteMin(s->leftChild);
}

// Funzioni da implementare

Error dict::deleteElem(const Key k, Dictionary& s) {
	if(s == emptyBst) return FAIL;
	// Visita dell'albero
	if(k < s->elem.key)
		return deleteElem(k, s->leftChild);
	if(k > s->elem.key)
		return deleteElem(k, s->rightChild);
	// Entrambi i figli sono presenti
	if(s->leftChild && s->rightChild) {
		s->elem = deleteMin(s->rightChild);
		return OK;
	}
	cell* aux = s;
	// s punta o al sottoalbero corretto o a emptyBst (se siamo a foglia)
	s = (s->rightChild) ? s->rightChild : s->leftChild;
	// elimino il prec (che io abbia saltato un nodo o che fossi a una foglia)
	delete aux;
	return OK;
} 	

Value dict::search(const Key k, const Dictionary& s) {
	// Caso: elemento non trovato
	if(s == emptyBst) return emptyValue;
	// Visita dell'albero
	if(k < s->elem.key)
		return search(k, s->leftChild);
	if(k > s->elem.key)
		return search(k, s->rightChild);
	return s->elem.value;
}

Error dict::insertElem(const Key k, const Value v,  Dictionary& s) {
	// Caso base: sottoalbero vuoto
	if(s == emptyBst) {
		s = createCell(k, v);
		return OK;
	}
	
	// Visita dell'albero
	if(k < s->elem.key)
		return insertElem(k, v, s->leftChild);
	if(k > s->elem.key)
		return insertElem(k, v, s->rightChild);
	
	// elemento già presente
	return FAIL;
}


/****************************************************************/
Dictionary dict::createEmptyDict() {
	Dictionary newDict = emptyBst;
	return newDict;
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
void print(const Dictionary& s) {
	if(s == emptyBst) return;
	print(s->leftChild);
	std::cout << s->elem.key << " : " << s->elem.value << std::endl;
	print(s->rightChild);
}



