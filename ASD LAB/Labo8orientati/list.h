// Dettagli implementativi dei tipi necessari alla realizzazione di liste implementate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// NON MODIFICARE QUESTO FILE CHE COSTITUISCE L?INTERFACCIA DEL TIPOM DI DATO LISTE

#include <iostream>

using namespace std;


namespace list{
		typedef int Elem;

    struct node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
   	 Elem info;
   	 node *prev;
     node *next;
		};
    typedef node* List;     // List e' il tipo "puntatore a node", dove node e' la struct dichiarata ma non definita
    const int EMPTYELEM = -1;
    
    
    /* Nota: l'implementazione con strutture con sentinella ci consentirebbe di passare sempre la lista per valore (o per const reference) in quanto il puntatore alla sentinella, una volta creata la lista, non cambia piu'. Per come sono state implementate le funzioni ausiliarie nella soluzione preparata dai docenti, tuttavia, E' opportuno passare la lista per riferimento. Lasciamo quindi il prototipo delle funzioni che, dal punto di vista logico, modificano la lista (anche se non modificano l'indirizzo della sentinella) con passaggio della lista per riferimento) */ 
    /* prototipi di funzioni */
    List createEmpty();           	     		/* crea la lista vuota */
    void addRear(Elem, const List&);        /* inserisce l'elemento alla fine della lista */
    bool isEmpty(const List&);        	     /* restituisce true se la lista e' vuota */
	 void addFront(Elem, const List&);
}

void printList(const list::List&);           /* stampa la lista */

