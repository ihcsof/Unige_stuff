// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

/*
	GRUPPO 10
	---------
	Gianì Lorenzo 5008434 (progettazione)
	Pastorelli Patrick 5038958 (implementazione)
	Foschi Lorenzo 4989646 (testing)
																 */

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream& str, List& l) {
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != FINEINPUT)  {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
    }
}

/* legge il contenuto di una lista da file */
void readFromFile(string nome_file, List& l) {
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}


/* legge il contenuto di una lista da standard input */
void readFromStdin(List& l) {
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const List& l) {
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next; 
    }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

/* crea la lista vuota */

/*
	si è testato con valgrind che il data loss è solamente quello
	delle sentinelle (x bytes in 10 blocks).
*/

void list::createEmpty(List& l) {
	// Imposto la lista
	/* Si imposta la funzione come un "costruttore", assumendo che venga chiamata
		solamente su liste ancora non create. */
   l = new node;
	l->next = l;
	l->prev = l;
}

// Funzione ausiliaria per la clear ricorsiva
void clear_aux(const List& l, List& l_aux) {
	// CASO BASE ricorsione: lista ridotta alla sola sentinella
	if(l_aux == l) return;
	// chiamo clear_aux passando dummy e prossimo elemento
	clear_aux(l, l_aux->next);
	// dalla fine dello stack delle chiamate cancello l_aux
	delete l_aux;
}

void list::clear(const List& l) {
	// Chiamo la funzione ausiliaria passando dummy ed l->next
	clear_aux(l, l->next);
	// Imposto l (rimane solo il dummy) in modo corretto
	l->next = l;
	l->prev = l;
}

// Funzione ausiliaria per la get ricorsiva
Elem get_aux(const List& l, List& l_aux, int pos) {
	// Fine lista (pos non valida)
	if(l == l_aux) return EMPTYELEM;
	// Se arrivo alla pos (decrementandola) ritorno l'elem
	if(pos == 0) return l_aux->info;
	// Prossimo passo ricorsivo
	return get_aux(l, l_aux->next, pos-1);	
}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento 
	che per convenzione si decide che rappresenta l'elemento vuoto altrimenti */
Elem list::get(int pos, const List& l) {
	return get_aux(l, l->next, pos);
}

// Funzione ausiliaria per la set ricorsiva
void set_aux(const List& l, List& l_aux, Elem e, int pos) {
	// Fine lista: lancio eccezione che verrà raccolta dalla funzione "sottostante"
	if(l == l_aux) throw "Errore: posizione non ammissibile";
	// Arrivo alla posizione cercata (decrementandola): modifico l'elemento
	if(pos == 0) l_aux->info = e;
	// Sennò: prossimo passo ricorsivo
	else set_aux(l, l_aux->next, e, pos-1);
}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, Elem e, const List& l) {
	//Chiamo l'ausiliaria catturando la sua eccezione
	try {
   	set_aux(l, l->next, e, pos);
	}
	catch(const char* err) {
		std::cerr << err << std::endl;
	}
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, Elem e, const List& l) {                                               
	node* aux = l->next;
	// Assunto -1 indice della sentinella
	int i = -1;
	// L'ordine delle condizioni è importante: se valutassi prima aux != l,
	//	nel caso di inserimento in ultima pos, non avviene ++i
	while (++i < pos && aux != l)
		aux = aux->next;
	if(i != pos) return;
	// Chiamo addRear sulla sottolista
	addRear(e, aux);
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e,  const List& l) {
	// Preparo la cella
   node* aux = new node;
	aux->info = e;
	// Collego l'ultimo elemento della lista ->next ad aux
	l->prev->next = aux;
	// Collego il prev del nuovo elemento al preced. ultimo elemento
	aux->prev = l->prev;
	// Il next del nuovo elemento deve "tornare indietro"
	aux->next = l;
	// Il precedente della sentinella punta all'ultimo
	l->prev = aux;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List& l) {
	node* aux = new node;
	aux->info = e;
	// Salto dummy. Ora aux punta o al primo elem o a dummy stesso
	aux->next = l->next;
	// Il prev della nuova cella punta al dummy
	aux->prev = l;
	// l->next->prev esiste in ogni caso: punta ad aux
	l->next->prev = aux;
	// Il next del dummy deve puntare al nuovo elemento
	l->next = aux;
}

/*
OPPURE, invertendo le operazioni in addRead (in coda) e modificando
l->prev->next = aux; in aux->prev->next = aux; perchè allora l ora è
aux (PENSACI!), posso generalizzare la addRear come una "addBeforePointer"
e utilizzarla al posto della addFront per inserire al puntatore preced.
(se chiamo addBeforePointer (addRear) su l->next, il "puntatore precedente"
è proprio la sentinella --> quindi faccio una addFronta

void list::addRear(Elem e,  const List& l) {
	// Preparo la cella
   node* aux = new node;
	aux->info = e;
	// Collego il prev del nuovo elemento al preced. ultimo elemento
	aux->prev = l->prev;
	// Il next del nuovo elemento deve "tornare indietro"
	aux->next = l;
	// Il precedente della sentinella punta all'ultimo
	l->prev = aux;
	// Collego l'ultimo elemento della lista ->next ad aux
	aux->prev->next = aux;
}

void list::addFront(Elem e, const List& l) {
	addRear(e, l->next);
}

*/

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const List& l) {
	// Caso di posizione negativa
	if(pos < 0) return;
	node* aux = l->next;
	// Ciclo per arrivare all pos (decrementandola)
	while (pos > 0 && aux != l) {
		aux = aux->next;
		--pos;
	}
	if(aux == l) return;
	// Cancellazione elemento in posizione pos "saltandolo"
	aux->prev->next = aux->next;
	aux->next->prev = aux->prev;
	delete aux;
}

/* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(Elem e, const List& l) {
	node* aux = l->next;
	node* tmp;
	// Ciclo la lista, saltando aux con tmp
	while(aux != l) {
		tmp = aux->next;
		// Se ho trovato l'elemento lo salto e cancello
		if(aux->info == e) {
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			delete aux;
		}
		aux = tmp;
	}
}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List& l) {
 	return(l->next == l);
}

//Ausiliaria della funzione size
int size_aux(const List& l, List& l_aux) {
	// CASO BASE: lista finita
	if(l_aux == l) return 0;
	// Prossimo passo ricorsivo
   return 1 + size_aux(l, l_aux->next);
}

 /* restituisce la dimensione della lista */
int list::size(const List& l) {
   return size_aux(l, l->next);
}



