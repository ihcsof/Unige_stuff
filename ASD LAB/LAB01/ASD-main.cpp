// File Main
// Compilare con g++ -Wall ASD-doubly-linked-list.cpp ASD-main.cpp -o ASD-labo1

// NON MODIFICARE QUESTO FILE

#include "ASD-doubly-linked-list.h"

const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono delle liste (inizialmente vuote).\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura di una lista da file terminato da -1000000 (2 operandi: nome_file indice);\nb: lettura di una lista da standard input (1 operando: indice);\nc: inserimento di un elemento alla fine di una lista (2 operandi: elem indice); \nd: inserimento di un elemento all'inizio di una lista (2 operandi: elem indice); \ne: inserimento di un elemento in una posizione data (3 operandi: pos elem indice); \nf: modifica dell'elemento in posizione pos (3 operandi: pos nuovoelem indice); \ng: accesso all'elemento in posizione pos (2 operandi: pos indice); \nh: cancellazione di un elemento in posizione pos da una lista (2 operandi: pos indice); \ni: cancellazione di un elemento elem da una lista (2 operandi: elem indice); \nl: verifica se la lista e' vuota (1 operando: indice);\nm: dimensione della lista (1 operando: indice); \nn: smantellamento di una lista (1 operando: indice); \no: stampa (1 operando: indice);\nr: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";

const int maxreg = 10;

int main() {
    try {
        // Sperimentiamo che l'information hinding funziona: cosa succede se tento di accedere alle componenti interne di una struttura di tipo node, 
        // oppure di un elemento di una lista (che e' un puntatore a node)? 
        // Decommentate le seguenti linee di codice per convincervi che dal main non si puo' accedere alle componenti di una struct node. 
        // E' proprio quello che vogliamo! Abbiamo nascosto il dettaglio implementativo di come sono fatti i blocchetti delle liste! 
        // Possiamo solo manipolare le liste usando le funzioni offerte dall'interfaccia, non accedendovi in modo diretto. 
        
     		/*
        list::node s;
        s.elem=3;
        
        list::List lista;
        lista->elem = 8;
        */
        
        vector<list::List> v(maxreg); // creo i registri
        for (int j=0; j<maxreg; ++j)  // inizializzo i registri in modo che tutti contengano all'inizio la lista vuota
           list::createEmpty(v[j]);
        
        list::Elem e;
        int i, pos;
        string nome_file;
        
        cout << menu;
        cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
        char ch;
        cin >> ch;
        while (ch!='q') {
           switch(ch) {
           case 'a':
               cin >> nome_file;
               if (!cin) throw runtime_error("Errore inserimento nome file\n");
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               readFromFile(nome_file, v[i]);
               print(v[i]);
           break;
        
           case 'b':
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               readFromStdin(v[i]);
               print(v[i]);
           break;
        
           case 'c':
               cin >> e >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::addRear(e, v[i]);
               print(v[i]);
           break;  
          
           case 'd':
               cin >> e >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::addFront(e, v[i]);
               print(v[i]);
           break;
        
           case 'e':
               cin >> pos >> e >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::add(pos, e, v[i]);
               print(v[i]);
           break;
        
           case 'f':
               cin >> pos >> e >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::set(pos, e, v[i]);
               print(v[i]);
           break;
        
           case 'g':
               cin >> pos >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               e = list::get(pos, v[i]);
               if (e == list::EMPTYELEM) 
                  cout << "\nNon esiste la posizione " << pos << " nella lista in posizione " << i << "\n";
               else 
                  cout << "\nL'elemento in posizione " << pos << " nella lista in posizione " << i << " e' " << e << endl;
               print(v[i]);
           break;
        
           case 'h':
               cin >> pos >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::removePos(pos, v[i]);
               print(v[i]);
           break;
        
           case 'i':
               cin >>  e >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::removeEl(e, v[i]);
               print(v[i]);
           break;
        
           case 'l':
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               if (list::isEmpty(v[i])) 
                  cout << "\nLa lista in posizione " << i << " e' vuota\n";
               else 
                  {cout << "\nLa lista in posizione " << i << " non e' vuota\n"; print(v[i]);}
           break;
        
           case 'm':
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               cout << "\nLa dimensione della lista in posizione " << i << " e' " << list::size(v[i]) << endl;
               print(v[i]);
           break;
        
           case 'n':
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               list::clear(v[i]);
           break;
        
           case 'o':
               cin >> i;
               if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
               print(v[i]);
           break;
        
           case 'r':
               for (int i=0; i<maxreg; ++i) {
                    cout << "\nLista in posizione " << i << ": ";
                    print(v[i]);
                }
           break;
        
           case 'p': 
               cout << menu;
           break;
        
           default: 
               cout << "\nOpzione non valida\n";
        } // switch
        cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
        cin >> ch;
       } // while
       return 0;
    } // try
    catch (runtime_error &msg) 
     {cerr << "Errore a runtime: " << msg.what() << endl;} 
    catch (...) 
     {cerr << "Eccezione non riconosciuta\n";} 
}

