// Dettagli implementativi dei tipi necessari alla realizzazione di liste implementate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// NON MODIFICARE QUESTO FILE CHE COSTITUISCE L?INTERFACCIA DEL TIPOM DI DATO LISTE

#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 

using namespace std;


namespace list{

    struct node;            // forward declaration: dichiaro che usero' una struct, ma non voglio far vedere come e' fatta dentro; la implementero' nel file listaASD-doubly-linked-list_aux.cpp; e' macchinoso ma e' il meglio di information hiding che possiamo ottenere in C++: i linguaggi a oggetti nascono per superare queste "macchinosita'"! 
    typedef int Elem;       // gli elementi della lista sono degli int; astraggo mediante un typedef
    typedef node* List;     // List e' il tipo "puntatore a node", dove node e' la struct dichiarata ma non definita
    const int FINEINPUT = -1000000;
    const int EMPTYELEM = -1000000;
    
    
    /* Nota: l'implementazione con strutture con sentinella ci consentirebbe di passare sempre la lista per valore (o per const reference) in quanto il puntatore alla sentinella, una volta creata la lista, non cambia piu'. Per come sono state implementate le funzioni ausiliarie nella soluzione preparata dai docenti, tuttavia, E' opportuno passare la lista per riferimento. Lasciamo quindi il prototipo delle funzioni che, dal punto di vista logico, modificano la lista (anche se non modificano l'indirizzo della sentinella) con passaggio della lista per riferimento) */ 
    /* prototipi di funzioni */
    void createEmpty(List&);           	     /* crea la lista vuota */
    void clear(const List&);                 /* "smantella" la lista (tranne la sentinella) */
    Elem get(int, const List&);        	     /* restituisce l'elemento in posizione pos */
    void set(int, Elem, const List&);        /* modifica l'elemento in posizione pos */
    void add(int, Elem, const List&);        /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
    void addRear(Elem,  const List&);        /* inserisce l'elemento alla fine della lista */
    void addFront(Elem, const List&);        /* inserisce l'elemento all'inizio della lista */
    void removePos(int, const List&);        /* cancella l'elemento in posizione pos dalla lista */
    void removeEl(Elem, const List&);        /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
    bool isEmpty(const List&);        	     /* restituisce true se la lista e' vuota */
    int  size(const List&);            	     /* restituisce la dimensione della lista */
}


void readFromFile(string, list::List&);  /* legge il contenuto di una lista da file */
void readFromStdin(list::List&);         /* legge il contenuto di una lista da standard input */
void print(const list::List&);           /* stampa la lista */

