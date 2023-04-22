#include "tree-chsib.h"

using namespace tree;

/* Nota: nei commenti usiamo "albero" e "puntatore a un nodo" come sinonimi, scegliendo di volta in volta
la formulazione più adatta a dare la specifica di una funzione. 
Dal punto di vista tecnico, usiamo sempre il tipo Tree sia quando operiamo su un albero, sia quando operiamo, 
a livello concettuale, su un puntatore a un nodo dell'albero. 
Questo approccio e' corretto in quanto un albero (o sottoalbero) è un puntatore a una struct di tipo treeNode:
un albero è identificato univocamente dal puntatore alla sua radice */ 

/*******************************************************************************************************/
// il nodo di un albero è caratterizzato dall'etichetta, il puntatore al primo figlio e il puntatore al prossimo fratello
// NON manteniamo il puntatore al padre, anche se sarebbe comodo per alcune funzioni (ma del tutto inutile per altre)
struct tree::treeNode {
    Label label;    
    treeNode *firstChild;
    treeNode *nextSibling;
};

/*******************************************************************************************************/
// isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
bool tree::isEmpty(const Tree& t)
{ 
   return (t == emptyTree);
}

// Ausiliaria createChild
Error createChild(Tree& t, const Label labelOfNodeToAdd) {
	t = new treeNode;
	t->label = labelOfNodeToAdd;
	t->firstChild = emptyTree;
	t->nextSibling = emptyTree;
	return OK;
}

Tree getNodeAux(const Tree& t, const Label l) {
	if(t->label == l) return t;
	Tree aux = t->firstChild;
	while(!isEmpty(aux)) {
		Tree res = getNodeAux(aux, l);
		if(res != emptyTree)
			return res;
		aux = aux->nextSibling;
	}
	return emptyTree;
}

// Ausiliaria getNode
Tree getNode(const Tree& t, const Label l) {
	if(isEmpty(t)) return emptyTree;
	return getNodeAux(t, l);
}

/*******************************************************************************************************/
// addElem aggiunge il nodo etichettato con labelOfNodeToAdd come
// figlio del nodo etichettato con labelOfNodeInTree.
// Caso particolare: aggiunta della radice, che si ottiene
// con labelOfNodeInTree uguale a emptyLabel (= nessun padre), e ha successo
// solo se l'albero e' vuoto (in caso contrario restituisce FAIL 
// e non aggiunge nulla).
// Restituisce FAIL se non esiste un nodo nell'albero etichettato 
// con labelOfNodeInTree oppure se nell'albero esiste gia' un nodo 
// etichettato con labelOfNodeToAdd; aggiunge e restituisce OK altrimenti

Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree& t)
{
	if(labelOfNodeInTree == emptyLabel) {
		if(!isEmpty(t)) return FAIL;
		return createChild(t, labelOfNodeToAdd);
	}
	if(member(labelOfNodeToAdd, t)) return FAIL;
	
	Tree aux = getNode(t, labelOfNodeInTree);
	if(aux == emptyTree) return FAIL;
	if(isEmpty(aux->firstChild))
		return createChild(aux->firstChild, labelOfNodeToAdd);
	aux = aux->firstChild;
	// Visita
	while(!isEmpty(aux->nextSibling))
		aux = aux->nextSibling;

	return createChild(aux->nextSibling, labelOfNodeToAdd);
}

// Versione di addElem che non utilizza la traccia proposta a lezione
/*
bool addAux(Tree& t, const Label labelOfNodeInTree, const Label toAdd, Tree& aux) {
	// Caso: incontro già il nodo che devo aggiungere
	if(t->label == toAdd) return true;
	// Incontro il padre (punto di aggiunta); potrei ancora trovare "più sotto" il nodo già presente
	if(t->label == labelOfNodeInTree) aux = t;
	// Visita
	Tree temp = t->firstChild;
	while(!isEmpty(temp)) {
		if(addAux(temp, labelOfNodeInTree, toAdd, aux))
			return true;
		temp = temp->nextSibling;
	}
	return false;	
}

Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree& t)
{
	// Se voglio inserire la radice ed effettivamente il tree è vuoto: inserisco la radice
	if(labelOfNodeInTree == emptyLabel) {
		if(!isEmpty(t)) return FAIL;
		return createChild(t, labelOfNodeToAdd);
	}

	// Caso: vuoto
	if(isEmpty(t)) return FAIL;	

	// labelOfNodeToAdd è già presente nell'albero?
	// Cerco in contemporanea alla ricerca del punto in cui inserire per ottimizzare
	Tree aux = emptyTree;
	if(addAux(t, labelOfNodeInTree, labelOfNodeToAdd, aux))
		return FAIL;
	
	// Padre vuoto = non trovato punto di inserimento
	if(isEmpty(aux)) return FAIL;
	// Caso: non ha figli
	if(isEmpty(aux->firstChild))
		return createChild(aux->firstChild, labelOfNodeToAdd);

	// Inserisco infondo ai nextSibling del figlio del padre il nuovo nodo
	aux = aux->firstChild;
	// Visita
	while(!isEmpty(aux->nextSibling))
		aux = aux->nextSibling;
	
	return createChild(aux->nextSibling, labelOfNodeToAdd);
}*/

/*******************************************************************************************************/
// deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
// e collega al padre di tale nodo tutti i suoi figli
// Restituisce FAIL se si tenta di cancellare la radice e questa ha 
// dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste 
// un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti

Error explode(Tree& t) {
	delete t;
	t = emptyTree;
	return OK;
}

Error removeChild(Tree& t) {
	// t è l'esatto nodo da cancellare: lo elimino sfruttando il passaggio per reference nella deleteElemAux
	Tree aux = t;
	// Salto e cancello il nodo
	Tree tmp = t->firstChild;
	t = t->nextSibling;
	delete aux;
	// Se il nextSibling del nodo eliminato non esiste, accodo il sottoalbero dei figli...
	if(!t)
		return (t = tmp), OK;
	//.. sennò scorro fino all'ultimo fratello e accodo lì il sottoalbero dei figli!
	aux = t;
	for(; aux->nextSibling; aux = aux->nextSibling);
	aux->nextSibling = tmp;
	
	return OK;
}

Error tree::deleteElemI(const Label l, Tree& t)
{
	if(isEmpty(t)) return FAIL;
	// Caso particolare: devo cancellare la radice (diversifico se la radice ha figli (FAIL) o no (la cancello))
	if(t->label == l) {
		if(t->firstChild)
			return FAIL;
		return explode(t);
	}
	// Recupero il puntatore al padre del nodo da eliminare
	Tree aux = getNode(t, father(l, t));
	if(isEmpty(aux)) return FAIL;
	// Se voglio eliminare il primo figlio:
	if(aux->firstChild->label == l)
		return removeChild(aux->firstChild);
	// Sennò cerco che fratello devo eliminare (esiste: lo sappiamo dalla getNode)
	aux = aux->firstChild;
	for(; aux->nextSibling->label != l; aux = aux->nextSibling);
	return removeChild(aux->nextSibling);
}

/*******************************************************************************************************/
// deleteElem (versione ricorsiva): stesso comportamento della versione iterativa, ma implementata ricorsivamente
// (può anche non essere ricorsiva la deleteElemR, ma deve fare uso di funzioni ausiliarie ricorsive)

Error deleteElemAux(Tree& t, const Label l) {
	// Sono sicuro che non è vuoto e non devo cancellare la root.. scendo e ciclo sui figli
	Tree* aux = &(t->firstChild);
	while(*aux != emptyTree) {
		// Se ho trovato la label rimuovo
		if((*aux)->label == l)
			return removeChild(*aux);
		// Se alla prossima chiamata ho ritornato OK: finito (riavvolgo le chiamate)
		if(!deleteElemAux(*aux, l))
			return OK;
		aux = &((*aux)->nextSibling);
	}
	return FAIL;
}

Error tree::deleteElemR(const Label l, Tree& t)
{
	if(isEmpty(t)) return FAIL;
	// Caso particolare: devo cancellare la radice (diversifico se la radice ha figli (FAIL) o no (la cancello))
	if(t->label == l) {
		if(t->firstChild)
			return FAIL;
		return explode(t);
	}
	
	return deleteElemAux(t, l);	  
}

/*******************************************************************************************************/
// father restituisce l'etichetta del padre del nodo con etichetta l se il nodo esiste nell'albero 
// (o sottoalbero) t e se il padre esiste. 
// Restituisce la costante emptyLabel altrimenti

Label fatherAux(const Label l, const Tree& t) {
	Tree currNode = t->firstChild;

   while(currNode != emptyTree){
		// Controllo sulla label (padre trovato)
      if(currNode->label == l) return t->label;
      
      Label tmp = fatherAux(l, currNode);
		// se è stato trovato il padre, ritorno la sua label e riavvolgiamo le chiamate
      if(tmp != emptyLabel) return tmp;

      currNode = currNode->nextSibling;
   }

   return emptyLabel;
}

Label tree::father(const Label l, const Tree& t) {
	// Caso per albero vuoto e per la radice (non ha padre)
   if(isEmpty(t) || t->label == l) return emptyLabel; 
   return fatherAux(l, t);
}

// Altra versione più compatta ma che sfrutta la caratteristica intrinseca di stringUtility
// ----------------------------------------------------------------------------------------
/*Label fatherAux(const Tree& t, const Label l) {
	if(isEmpty(t)) return emptyLabel;
	// Come convenzione usata dalla strUtility gli spazi non sono ammessi 
	if(t->label == l) return " ";
	Tree aux = t->firstChild;
	while(!isEmpty(aux)) {
		Label lf = fatherAux(aux, l);
		if(lf == " ") return t->label;
		if(lf != emptyLabel) return lf;
		aux = aux->nextSibling;
	}
	return emptyLabel;
}

Label tree::father(const Label l, const Tree& t) {
	if(isEmpty(t) || t->label == l) return emptyLabel; 
	return fatherAux(t, l);
}*/

/*******************************************************************************************************/
// children restituisce una lista di Label, contenente le etichette 
// di tutti i figli nell'albero t del nodo etichettato con l
// La lista può essere implementata usando una qualunque delle strutture dati viste a lezione
// (non un Vector!!!): si riusi una implementazione del TDD list, adattandola 
// a elementi di tipo string (nelle precedenti esercitazioni gli elementi erano int)
list::List tree::children(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   Tree aux = getNode(t, l);
	// Padre non presente unificato al caso Lista vuota
	if(isEmpty(aux)) return lst;
	aux = aux->firstChild;
	// Scorro i fratelli aggiungendoli
	for(; aux; aux = aux->nextSibling)
		list::addBack(aux->label, lst);
	return lst;
}

/*******************************************************************************************************/
// degree restituisce il numero di archi uscenti dal nodo etichettato con l; restituisce -1 se non esiste 
// nessuna etichetta l nell'albero
int tree::degree(const Label l, const Tree& t)
{
	Tree aux = getNode(t, l);
	if(isEmpty(aux)) return -1;
	int d = 0;
	aux = aux->firstChild;	
	// Scorro i fratelli contandoli
	for(; aux; ++d, aux = aux->nextSibling);
	return d;
}

/*******************************************************************************************************/
// ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
// (può anche non essere ricorsiva la ancestorsR, ma deve fare uso di funzioni ausiliarie ricorsive)

// Ausiliaria di ancestor
bool ancestorAux(const Tree& t, const Label l, list::List& lst) {
	if(t->label == l) return true;
	Tree aux = t->firstChild;
	while(!isEmpty(aux)) {
		if(ancestorAux(aux, l, lst)) {
			// Partendo "dal basso" aggiungo in coda --> il primo el. nella lista sarà il padre di "l"
			addBack(t->label, lst);
			return true;
		}
		aux = aux->nextSibling;
	}
	return false;
}

list::List tree::ancestorsR(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
	// Chiamo l'ausiliaria solo se l'albero non è vuoto
	t ? ancestorAux(t, l, lst) : FAIL;
   return lst;
}

/*******************************************************************************************************/
// ancestors (versione iterativa) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
list::List tree::ancestorsI(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
	Label aux = l;
	// Recupero il nodo di cui trovare gli antenati (arrivo fino alla radice (father ritorna emptyLabel)
	while((aux = father(aux, t)) != emptyLabel)
		addBack(aux, lst);

   return lst;
}

/*******************************************************************************************************/
// leastCommonAncestor restituisce l'etichetta del minimo antenato comune 
// ai nodi etichettati con label1 e label2

// Scorriamo dall'alto al basso; potremmo fare l'opposto ma in complessità non varia (dipende dalla pos dell'antenato)
Label tree::leastCommonAncestor(const Label label1, const Label label2, const Tree& t)
{
	list::List lst1 = ancestorsR(label1, t);
	list::List lst2 = ancestorsR(label2, t);

	// Caso particolare: cerco l'antenato comune degli stessi nodi
	if(get(0, lst1) == get(0, lst2))
		return get(0, lst1);

	int i = size(lst1)-1;
	int j = size(lst2)-1;
	// Parte dalla radice (in ultima pos della lista) e si ferma alla prima biforcazione 
	// NB: per la convenzione adottata dalle specifiche, la radice NON è antenata di se stessa
	while(get(i--, lst1) == get(j--, lst2));
	
	//Salvo la label per deallocare le liste e ritorno il leastCommonAncestor
	// i+2 perchè il ciclo while viene anche rifatto una seconda volta in più (dopo la biforcazione)
	Label toRet = get(i+2, lst1);
	clear(lst1);
	clear(lst2);
   return toRet;
}

/*******************************************************************************************************/
// member restituisce true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
bool memberAux(const Label l, const Tree& t) {
	if(t->label == l) return true;
	Tree aux = t->firstChild;
	while(!isEmpty(aux)) {
		if(memberAux(l, aux))
			return true;
		aux = aux->nextSibling;
	}
	return false; 
}

bool tree::member(const Label l, const Tree& t)
{ 
  	if(isEmpty(t)) return false;
	// Ausiliaria per non ripetere il controllo isEmpty ad ogni chiamata
	return memberAux(l, t);
}

/*******************************************************************************************************/
// numNodes restituisce il numero di nodi nell'albero t mediante una visita ricorsiva in depthfirst

int numNodesAux(const Tree& t) {
	Tree aux = t->firstChild;
	int n = 1;
	while(!isEmpty(aux)) {
		n += numNodesAux(aux);
		aux = aux->nextSibling;
	}
	return n;
}

int tree::numNodes(const Tree& t)
{
   if(isEmpty(t)) return 0;
	return numNodesAux(t);
}

/*******************************************************************************************************/
// createEmptyTree restituisce l'albero vuoto
Tree tree::createEmpty()
{
   return emptyTree;
}

/*******************************************************************************************************/

// Ausiliaria di print per la formattazione
void printAux(const Tree& t, int level) {
	for(int i = 0; i < level; ++i)
		std:cout << "--";
	std::cout << t->label << std::endl;

	// Stampa gerarchica in preordine 
	Tree aux = t->firstChild;	
	while(!isEmpty(aux)) {
		printAux(aux, level+1);
		aux = aux->nextSibling;
	}
}

// Visualizzazione possibilmente strutturata come visto a lezione
void printTree(const Tree& t) {
	if(isEmpty(t)) return;
   printAux(t, 0);
}

/****************************************************************/
// Questa funzione NON richiede di conoscere come e' fatta la struttura dati che implementa l'albero: usa solo addElem e quindi e' ad 
// un alto livello di astrazione
// Vantaggi: codice compatto, leggibile, riutilizzabile per qualunque implementazione del TDD Tree
// Svantaggi: inefficiente: la addElem cerca ogni volta il nodo con etichetta fatherLabel, mentre basterebbe una chiamata sola per 
// trovarlo e poi si potrebbero attaccare tutti i figli a esso, senza ripetere la dispendiosa ricerca nell'albero; per renderla 
// efficiente dovrei pero' accedere direttamente alla struttura dati chiamando qualche funzione ausiliaria che operi 
// sui nodi dell'albero, rinunciando a scrivere codice modulare, chiaro e ad un ragionevole livello di astrazione... 
// Non esiste un'opzione migliore tra le due: se il codice deve essere efficiente, è opportuno scrivere una funzione ad hoc per 
// una determinata implementazione; se il codice deve essere riutilizzabile, bisogna limitarsi a usare le funzioni offerte dall'
// interfaccia del TDD in modo che la funzione continui ad andare bene anche se cambia l'implementazione
Tree readFromStream(istream& str)
{
    Tree t = createEmpty(); 
    string line;
    Label rootLabel, fatherLabel, childLabel;
    getline(str, line);  
    istringstream instream;            // uso una variabile di tipo istringstream per poter scandire i pezzi di ogni riga usando >>
    instream.clear();
    instream.str(line);
    instream >> rootLabel;             // il primo elemento che si incontra nel file e' l'etichetta della radice, per convenzione su come deve essere fatto il file
    addElem(emptyLabel, rootLabel, t); // la si inserisce nell'albero vuoto, indicando che il padre non c'e' (primo argomento emptyLabel)
    getline(str, line);                // poi si iniziano a scansionare le righe seguenti
    instream.clear();
    instream.str(line);
    while (!str.eof())  
        {        
	instream >> fatherLabel; // in ogni riga del file, il primo elemento e' l'etichetta del nodo padre e gli altri sono le etichette dei figli
        removeBlanksAndLower(fatherLabel); // normalizzo l'etichetta del padre
        while (!instream.eof())            // finche' la riga corrente non e' terminata
            { 
            instream >> childLabel;              // leggo la prossima etichetta
            removeBlanksAndLower(childLabel);    // la normalizzo
            addElem(fatherLabel, childLabel, t); // e la attacco al padre
            }
        getline(str, line);  
        instream.clear();
        instream.str(line);
        }
    str.clear();
    return t;
}

/****************************************************************/
Tree readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmpty();}  
    return readFromStream(ifs);
}

