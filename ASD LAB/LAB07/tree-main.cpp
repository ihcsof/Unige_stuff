// Compilare con g++ -Wall -std=c++11 *.cpp -o tree 
 
#include "tree-chsib.h"


const int maxreg = 10;
const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono alberi inizialmente vuoti.\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura di un albero da file [la prima riga del file deve contenere solo l'etichetta della radice; le righe successive devono rispettare la sintassi labelPadre labelFiglio1 labelFiglio2 .... labelFiglioN] (2 operandi:   nome_file  indice); \nb: inserimento di un nodo etichettato labelFiglio attaccato a un padre etichettato labelPadre (3 operandi:  labelPadre   labelFiglio   indice); nota: assumiamo che le etichette non contengano spazi; l'etichetta vuota e' rappresentata da $#$#$\nc: cancellazione di un nodo etichettato label dall'albero (2 operandi: label   indice);\nd: individuazione del padre del nodo etichettato label (2 operandi: label   indice);\ne: individuazione delle etichette dei figli del nodo etichettato label (2 operandi: label   indice);\nf: calcolo del grado del nodo con etichetta label (2 operandi: label   indice);\ng: individuazione delle etichette degli antenati del nodo etichettato label (2 operandi: label   indice);\nh: individuazione dell'etichetta del minimo antenato comune a due nodi etichettati label1 e label2 (3 operandi: label1 label2   indice);\ni: appartenenza di un nodo con etichetta label all'albero (2 operandi: label   indice);\nl: calcolo del numero totale dei nodi dell'albero (1 operando: indice);\nm: stampa di un registro (1 operando: indice);\nn: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";

int main()
{
try {
vector<tree::Tree> v(maxreg);
for (int j=0; j<maxreg; ++j) {v[j] = tree::createEmpty();}
tree::Label l1, l2, l;
list::List lst;
high_resolution_clock::time_point t1, t2;
int i;
string nome_file,index;
double duration;

char ch;

cout << menu;

while (true)
{
   cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
   cin >> ch;
   cin.ignore();

   if (ch=='q')
      break;

   switch(ch)
   {
   case 'a':
   cin >> nome_file;
   if (!cin) throw runtime_error("Errore inserimento nome file\n");
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   v[i] = readFromFile(nome_file);
   break;

   case 'b':
   cin >> l1 >> l2 >> i;
   if (!cin) throw runtime_error("Errore inserimento dati\n");
   if (i<0 || i>=maxreg) {cout << "\nIndice " << i << " fuori range\n"; break;}
   removeBlanksAndLower(l1);
   removeBlanksAndLower(l2);
   tree::addElem(l1, l2, v[i]);
   break;

   case 'c':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   cout << "\nDigitare r per la delete ricorsiva e i per la delete iterativa: ";
   cin >> ch;
   if (ch=='r' || ch=='R') 
      {
      t1 = high_resolution_clock::now();
      if (tree::deleteElemR(l, v[i]) == tree::FAIL) 
          cout << "\nNodo non cancellato (motivo: l'etichetta e' quella della radice e la radice ha figli, oppure l'etichetta non e' presente nell'albero)\n";
      else 
         cout << "\nNodo " << l << " cancellato\n";
      t2 = high_resolution_clock::now();
      duration = duration_cast<microseconds>( t2 - t1 ).count();
      cout << "\nDeleteElem ricorsiva: " << duration << " microsecondi\n";
      }
   else if (ch=='i' || ch=='I') 
         {
         t1 = high_resolution_clock::now();
         if (tree::deleteElemI(l, v[i]) == tree::FAIL) 
             cout << "\nNodo non cancellato (motivo: l'etichetta e' quella della radice e la radice ha figli, oppure l'etichetta non e' presente nell'albero)\n";
         else 
            cout << "\nNodo " << l << " cancellato\n";
         t2 = high_resolution_clock::now();
         duration = duration_cast<microseconds>( t2 - t1 ).count();
         cout << "\nDeleteElem iterativa: " << duration << " microsecondi\n";
         }
         else cout << "\nCarattere non ammesso\n";
   break;

   case 'd':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   l1 = tree::father(l, v[i]);
   if (l1 == tree::emptyLabel) 
      cout << "\nPadre non trovato (motivo: l'etichetta e' quella della radice oppure non e' presente nell'albero)\n";
   else 
      cout << "\nIl padre di " << l << " e' " << l1 << endl;
   break;

   case 'e':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   lst = tree::children(l, v[i]);
   if (list::isEmpty(lst)) 
      cout << "\nFigli non trovati (motivo: l'etichetta e' quella di una foglia oppure non e' presente nell'albero)\n";
   else 
      {
      cout << "\nI figli di " << l << " sono"; 
      printList(lst);
      }
   break;

   case 'f':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   cout << "\nIl grado del nodo con etichetta " << l << " e' " << tree::degree(l,v[i]) << endl; 
   break;

   case 'g':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   t1 = high_resolution_clock::now();
   lst = tree::ancestorsR(l, v[i]);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nAncestor ricorsiva: " << duration << " microsecondi\n";
   if (list::isEmpty(lst)) 
      cout << "\nAntenati non trovati (motivo: l'etichetta e' quella della radice oppure non e' presente nell'albero)\n";
   else 
      {
      cout << "\nGli antenati di " << l << " sono"; 
      printList(lst);
      }

   t1 = high_resolution_clock::now();
   lst = tree::ancestorsI(l, v[i]);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nAncestor iterativa: " << duration << " microsecondi\n";
   if (list::isEmpty(lst)) 
      cout << "\nAntenati non trovati (motivo: l'etichetta e' quella della radice oppure non e' presente nell'albero)\n";
   else 
      {
      cout << "\nGli antenati di " << l << " sono"; 
      printList(lst);
      }
   break;

   case 'h':
   cin >> l1 >> l2 >> i;
   if (!cin) throw runtime_error("Errore inserimento dati\n");
   if (i<0 || i>=maxreg) {cout << "\nIndice " << i << " fuori range\n"; break;}
   removeBlanksAndLower(l1);
   removeBlanksAndLower(l2);
   l = tree::leastCommonAncestor(l1, l2, v[i]);
   if (l == tree::emptyLabel) 
      cout << endl << l1 << " e " << l2 << " non hanno antenati comuni (motivo: almeno una delle etichette e' la radice oppure almeno una di esse non esiste nell'albero)\n"; 
   else 
      cout << endl << l1 << " e " << l2 << " hanno " << l << " come minimo antenato comune\n"; 
   break;

   case 'i':
   cin >> l >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   removeBlanksAndLower(l);
   if (tree::member(l, v[i])) 
      cout << endl << l << " appartiene all'albero\n";
   else 
      cout << endl << l << " non appartiene all'albero\n";
   break;

   case 'l':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   cout << "\nNumero di nodi: " << numNodes(v[i]) << endl;
   break;

   case 'm':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   printTree(v[i]);
   break;

   case 'n':
   for (int i=0; i<maxreg; ++i)
       {
        cout << "\nAlbero in posizione " << i << endl;
        printTree(v[i]);
       }
   break;

   case 'p': 
   cout << menu;
   break;

   default: 
   cout << "\nOpzione non valida\n";
   }
}
return 0;
} 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}
