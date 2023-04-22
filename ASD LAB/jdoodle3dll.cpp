/*******************************/
/* PROVA DI LABORATORIO DI ASD */
/*******************************/

// Descrizione:
// In questo esercizio consideriamo le liste doppiamente collegate, circolari, con sentinella, non ordinate
// e le loro operazioni fondamentali

// scrivere sotto Nome, Cognome e Matricola:
// NOME:
// COGNOME:
// MATRICOLA:

#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 

using namespace std;

namespace list {

    typedef int Elem;   // gli elementi della lista sono degli int; astraggo mediante un typedef
    
    const int FINEINPUT = -1000000;
    const int EMPTYELEM = -1000000;
    struct node {  // descrivo qui come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
        Elem info;
        node *prev;
        node *next;
    };

    typedef node* List; // List e' il tipo "puntatore a node", dove node e' la struct dichiarata ma non definita
    
    void clear(const List&);            /* "smantella" la lista (tranne la sentinella) */
    Elem get(int, const List&);        	/* restituisce l'elemento in posizione pos */
    void set(int, Elem, const List&);   /* modifica l'elemento in posizione pos */
    void add(int, Elem, const List&);   /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
    void addRear(Elem,  const List&);   /* inserisce l'elemento alla fine della lista */
    void addFront(Elem, const List&);   /* inserisce l'elemento all'inizio della lista */
    void removePos(int, const List&);   /* cancella l'elemento in posizione pos dalla lista */
    void removeEl(Elem, const List&);   /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
    bool isEmpty(const List&);        	/* restituisce true se la lista e' vuota */
    bool isIn(const Elem, const List&);  /* restituisce true se l'elemento è contenuto nella lista */
    int  size(const List&);            	/* restituisce la dimensione della lista */
    void createEmpty(List&);           	/* crea la lista vuota */
    
    /******* LE SEGUENTI TRE FUNZIONI SONO QUELLE DA IMPLEMENTARE *******/ 
    void copyIfLowerThan(const List&, List&, const int); /* copia gli elementi della prima lista nella seconda solo se minori di una soglia */
    void copyIfGreaterThan(const List&, List&, const int); /* copia gli elementi della prima lista nella seconda solo se maggiori di una soglia */
    int sum(const List&); /* restituisce la somma degli elementi contenuti nella lista */

}

/*************************************************/
/* Implementazione delle operazioni di utilita' */
/*************************************************/

void readFromStream(istream& str, list::List& l) {
    createEmpty(l);
    list::Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != list::FINEINPUT)  {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
    }
}


/* legge il contenuto di una lista da standard input */
void readFromStdin(list::List& l) {
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << list::FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const list::List& l) {
    
   list::List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   
    while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next;
    }
}

/**************************************************/
/* Implementazione delle operazioni sulle liste */
/**************************************************/

list::node* goToPosition(const list::List l, int pos) {
    
    // Assumo che all'esterno sia stata verificata l'ammissibilità della posizione
   
    // salto la sentinella
    list::node *q = l->next;
    
    // procedo fino alla posizione che mi interessa
    for(int i = 0; i < pos; ++i)
        q = q->next;
    
    return q;
}

/* crea la lista vuota */
void list::createEmpty(list::List& l) {

    // Crea il nodo sentinella
    l = new node;
    // Sistema i puntatori, che puntano a se stesso
    l->next = l;
    l->prev = l;
    
}

/* "smantella" la lista svuotandola */
void list::clear(const List& l) {
    
    // Salta la sentinella
    list::node *p = l->next;
    list::node *q;
    // va bene anche List aux, auxn;
    
    while(p != l) { // finchè ci sono elementi nella lista
        q = p->next; // tengo traccia del prossimo elemento in una variabile temporanea
        delete p; // cancello cella corrente
        p = q; // aux punta al prossimo elemento
    }
    // Notate che non serve perdere tempo ad aggiustare i puntatori next e prev, dato che stiamo svuotando la lista
    
    // la lista adesso è vuota, quindi i puntatori nella sentinella puntano alla sentinella stessa
    l->next = l;
    l->prev = l;

}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento 
che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
list::Elem list::get(int pos, const list::List& l) {
    
    // NOTA: le posizioni ammissibili vanno da 0 a N-1 dove N=size(l)
    
    // Se la posizione non è tra quelle possibili restuisce l'elemento vuoto
    if(pos >= size(l) || pos < 0)
        return EMPTYELEM;
    
    list::node* q = goToPosition(l, pos);
    
    return q->info;
    
}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, list::Elem e, const list::List& l) {
    
    // NOTA: le posizioni ammissibili vanno da 0 a N-1 dove N=size(l)
    
    // Mi conviene fare il controllo sull'ammissibilità della posizione cercando quelle ammissibili, dato che se la posizione non è ammissibile non devo fare niente
    if(pos < size(l) && pos >= 0) { // se la posizione è ammissibile...
        
        node* q = goToPosition(l, pos);
        
        // modifico l'elemento
        q->info = e;
    }
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, list::Elem e, const list::List& l) {
    
    // Identifichiamo alcuni casi:
    // Se pos == 0: aggiungo in testa
    // Se pos == size(l): aggiungo in coda
    // Aggiungo in una posizione intermedia se la posizione è ammissibile, ossia se è compresa tra 1 e size(l)-1
    // Altrimenti non faccio nulla (posizione non ammissibile)
    
    if(pos == 0)
        addFront(e, l);
    else if(pos == size(l))
        addRear(e, l);
    else if(pos >= 1 && pos <= size(l)-1 ) {
        
        list::node* q = goToPosition(l, pos-1);
        
        // creo un nuovo nodo
        list::List p = new node;
        p->info = e;
        
        // aggiusto i puntatori
        p->prev = q;
        p->next = q->next;
        q->next = p;
        p->next->prev = p;
    }
        
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(list::Elem e,  const list::List& l) {
   
    // creo un nuovo nodo
    list::List q = new node;
    q->info = e;
    
    // sistemo i puntatori del nuovo nodo e aggiorno quelli della sentinella
    q->prev = l->prev;
    q->prev->next = q;
    q->next = l;
    l->prev = q;
    
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(list::Elem e, const list::List& l) {
    list::List q = new node;
    q->info = e;
    q->next = l->next;
    q->next->prev = q;
    q->prev = l;
    l->next = q;
}

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const list::List& l) {
    
    // se pos è ammissibile...
    if(pos >= 0 && pos < size(l)) {
        
        list::node* q = goToPosition(l, pos);
        
        // aggiusto i puntatori dei nodi precedente e successivo a quello che sto per cancellare
        q->prev->next = q->next;
        q->next->prev = q->prev;
        
        // rimuovo l'elemento
        delete q;
    }

}

 /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(list::Elem e, const list::List& l) {
    
    // salto la sentinella e dichiaro una variabile node di supporto
    list::node *p = l->next, *q;
    
    // finchè ci sono elementi nella lista
    while(p != l) {
        if(p->info == e) { // se trovo un elemento da cancellare
            q = p->next; // tengo traccia della posizione seguente a quella corrente, da cui devo ripartire al controllo successivo
            
            // aggiusto i puntatori dei nodi precedente e successivo a quello che sto per cancellare
            p->prev->next = q;
            q->prev = p->prev;
            
            // cancello il nodo
            delete p;
            
            // riassegno elemento corrente
            p = q;
        } else // procedo con la scansione della lista
            p = p->next;
    }
}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const list::List& l) {
        return l->next == l;
}


bool list::isIn(const list::Elem E, const list::List& l) { /* restituisce true se l'elemento E è presente nella lista L */
    
    // salto la sentinella 
    list::node *p = l->next;
    while(p != l) {
        if(p->info == E)
            return true;
        p = p->next;
    }
    return false;
}

// implementazione ricorsiva della funzione per calcolare la lunghezza della lista
int size_iter(list::List& aux, const list::List l) {
    if(aux==l)
        return 0;
    return 1 + size_iter(aux->next, l);
}


/* restituisce la dimensione della lista */
int list::size(const list::List& l) {
    return size_iter(l->next, l);
}

/****************************************************************/
/* DESCRIZIONE FUNZIONE DA IMPLEMENTARE
/* Sviluppare una funzione C/C++ chiamata copyIfLowerThan che prende in input due liste l ed l1, ed un intero th
/* e copia in l1 gli elementi di l che sono strettamente minori dell'intero th
/*
/* ESEMPIO 1
/* (prima della chiamata della funzione copyIfLowerThan) l = 5 8 1 10 3 0 12
/* (dopo la chiamata della funzione copyIfLowerThan con th=8) l = 5 8 1 10 3 0 12, l1 = 5 1 3 0 
/* ESEMPIO 2
/* (prima della chiamata della funzione copyIfLowerThan) l = 5 8 1 10 3 0 12
/* (dopo la chiamata della funzione copyIfLowerThan con th=4) l = 5 8 1 10 3 0 12, l1 = 1 3 0 */
void list::copyIfLowerThan(const list::List& l, list::List& l1, const int th) {
    List aux = l->next;
    while(aux != l) {
        if(aux->info < th)
        addRear(aux->info, l1);
        aux = aux->next;
    }
} 

/****************************************************************/
/* DESCRIZIONE FUNZIONE DA IMPLEMENTARE
/* Sviluppare una funzione C/C++ chiamata copyIfGreaterThan che prende in input due liste l ed l1, ed un intero th
/* e copia in l1 gli elementi di l che sono strettamente maggiori dell'intero th
/*
/* ESEMPIO 1
/* (prima della chiamata della funzione copyIfGreaterThan) l = 5 8 1 10 3 0 12
/* (dopo la chiamata della funzione copyIfGreaterThan con th=8) l = 5 8 1 10 3 0 12, l1 = 10 12 
/* ESEMPIO 2
/* (prima della chiamata della funzione copyIfGreaterThan) l = 5 8 1 10 3 0 12
/* (dopo la chiamata della funzione copyIfGreaterThan con th=7) l = 5 8 1 10 3 0 12, l1 = 8 10 12 */
void list::copyIfGreaterThan(const list::List& l, list::List& l1, const int th) {
    List aux = l->next;
    while(aux != l) {
        if(aux->info > th)
        addRear(aux->info, l1);
        aux = aux->next;
    }
} 

/****************************************************************/
/* DESCRIZIONE FUNZIONE DA IMPLEMENTARE
/* Sviluppare una funzione C/C++ chiamata sum che prende in input una lista e restituisce
/* il valore della somma dei suoi elementi 
/*
/* ESEMPIO
/* l = 5 8 1 10 3 0 12
/* sum(l) = 39 */
int list::sum(const list::List& l) {
    int s = 0;
    List aux = l->next;
    while(aux != l) {
        s += aux->info;
        aux = aux->next;
    }
    return s;
}


int main() {
    
    // Creiamo una lista vuota
    list::List L;
    createEmpty(L);
    
    // Leggiamo alcuni elementi da stdin, ad es. 10 5 7 12 1 -1000000
    readFromStdin(L); 
    
    cout << endl << "La lista contiene " << size(L) << " elementi" << endl;
    print(L);
    
    // Fissiamo una soglia a scelta
    int TH = 3;

    // Creiamo una nuova lista copiando in essa gli elementi di L minori della soglia
    list::List L1;
    createEmpty(L1);
    copyIfLowerThan(L, L1, TH);
    
    // Creiamo una nuova lista copiando in essa gli elementi di L maggiori della soglia
    list::List L2;
    createEmpty(L2);
    copyIfGreaterThan(L, L2, TH);

    // Output a video e test finale per verificare la correttezza delle funzioni
    cout << endl << endl << "Uso la soglia " << TH << endl;
    cout << "La somma degli elementi in L e' " << sum(L) << endl;
    cout << "La somma degli elementi in L1 e' " << sum(L1) << endl;
    cout << "La somma degli elementi in L2 e' " << sum(L2) << endl;
    
    // Se il valore assegnato a th è anche presente nella lista non verrà copiato dalle funzioni di copia, che implementano il minore o maggiore stretto
    // quindi la somma degli elementi in L deve essere uguale alla somma degli elementi di L1 + la somma degli elementi di L2 + il valore di th
    if(isIn(TH, L)) {
        if(sum(L)==(sum(L1)+sum(L2)+TH))
            cout << "--> TEST PASSATO (" << sum(L) << "==" << sum(L1) << "+" << sum(L2) << "+" << TH << ")" << endl;
        else
            cout << "--> TEST FALLITO (" << sum(L) << "!=" << sum(L1) << "+" << sum(L2) << "+" << TH << ")" << endl;
    } else { // la somma degli elementi in L deve essere uguale alla somma degli elementi di L1 + la somma degli elementi di L2
        if(sum(L)==(sum(L1)+sum(L2)))
            cout << "--> TEST PASSATO (" << sum(L) << "==" << sum(L1) << "+" << sum(L2) << ")" << endl;
        else
            cout << "--> TEST FALLITO (" << sum(L) << "!=" << sum(L1) << "+" << sum(L2) << ")" << endl;
    }
  
    
}


