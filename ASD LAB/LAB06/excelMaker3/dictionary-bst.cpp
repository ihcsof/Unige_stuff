#include "dictionary.h"

using namespace dict;

struct dict::bst {
   Elem	elem;
	bst	*leftChild;
	bst	*rightChild;
};

// Ausiliaria per creare un nodo (non parte del namespace)

bst* createCell(const Key k, const Value v) {
	bst* newCell = new bst;
	newCell->elem.key = k;
	newCell->elem.value = v;
	newCell->leftChild = emptyBst;
	newCell->rightChild = emptyBst;
	return newCell;
}

//Ausiliaria deleteMin per la deleteElem
Elem deleteMin(Dictionary3& s) {
	// Se non c'è un leftChild (siamo nella pos più a sx del sottoalbero dx)
	if(s->leftChild == emptyBst) {
		// Salvo il puntatore e l'elemento
		bst* aux = s;
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

Error dict::deleteElem(const Key k, Dictionary3& s) {
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
	bst* aux = s;
	// s punta o al sottoalbero corretto o a emptyBst (se siamo a foglia)
	s = (s->rightChild) ? s->rightChild : s->leftChild;
	// elimino il prec (che io abbia saltato un nodo o che fossi a una foglia)
	delete aux;
	return OK;
} 	

Value dict::search(const Key k, const Dictionary3& s) {
	// Caso: elemento non trovato
	if(s == emptyBst) return emptyValue;
	// Visita dell'albero
	if(k < s->elem.key)
		return search(k, s->leftChild);
	if(k > s->elem.key)
		return search(k, s->rightChild);
	return s->elem.value;
}

Error dict::insertElem(const Key k, const Value v,  Dictionary3& s) {
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
Dictionary3 dict::createEmptyDict3() {
	Dictionary3 newDict = emptyBst;
	return newDict;
}


/****************************************************************/
Dictionary3 readFromFile3(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict3();}  
    return readFromStream3(ifs);
}

/****************************************************************/
Dictionary3 readFromStream3(istream& str)
{
    Dictionary3 d = createEmptyDict3();     
    string key, kcopy;
    string value;
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
void print(const Dictionary3& s) {
	if(s == emptyBst) return;
	print(s->leftChild);
	std::cout << s->elem.key << " : " << s->elem.value << std::endl;
	print(s->rightChild);
}

void erase3Aux(Dictionary3& s) {
	if(s == emptyBst) return;
	erase3Aux(s->leftChild);
	erase3Aux(s->rightChild);
	delete s;
}

// Erase per evitare mem.leak
void dict::erase3(Dictionary3& s) {
	erase3Aux(s);
	s = emptyBst;
}

