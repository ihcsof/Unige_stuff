#include "queueASD-array.h" 


const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono delle code inizialmente vuote.\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura degli elementi di una coda (con inserimento in fondo) da file terminato da -1000000 (2 operandi: nome_file indice);\nb: lettura degli elementi di una coda (con inserimento in fondo) da standard input (1 operando: indice);\nc: enqueue (2 operandi: elem indice);\nd: dequeue (1 operando: indice);\ne: first (1 operando: indice); \nf: isEmpty (1 operando: indice); \nn: stampa (1 operando: indice);\no: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";

const int MAXREG = 10;

int main()
{
try {
vector<queue::Queue> v(MAXREG);
int i;
for (i=0; i<MAXREG; ++i)
   v[i] = queue::createEmpty();
queue::Elem e;

string nome_file;

cout << menu;
cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
char ch;
cin >> ch;
while (ch!='q')
{
   switch(ch)
   {
   case 'a':
   cin >> nome_file;
   if (!cin) throw runtime_error("Errore inserimento nome file\n");
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   v[i] = readFromFile(nome_file);
   print(v[i]);
   break;


   case 'b':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   v[i] = readFromStdin();
   print(v[i]);
   break;


   case 'c':
   cin >> e >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   queue::enqueue(e, v[i]);
   print(v[i]);
   break;


   case 'd':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   e = queue::dequeue(v[i]);
   cout << "\nQueue in posizione " << i; 
   print(v[i]);
   if (e != queue::EMPTYELEM)
      cout << "\nElemento che era in testa alla queue " << i << ": " << e << endl; 
   else 
      cout << "\nQueue vuota\n";
   break;

   case 'e':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   e = queue::first(v[i]);
   cout << "\nQueue in posizione " << i; 
   print(v[i]);
   if (e != queue::EMPTYELEM)
      cout << "\nElemento in testa alla queue " << i << ": " << e << endl; 
   else 
      cout << "\nQueue vuota\n";
   break;

   case 'f':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   if (queue::isEmpty(v[i])) 
      cout << "\nLa queue in posizione " << i << " e' vuota\n";
   else 
      {cout << "\nLa queue in posizione " << i << " non e' vuota\n"; print(v[i]);}
   break;

   case 'n':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   print(v[i]);
   break;

   case 'o':
   for (int i=0; i<MAXREG; ++i)
       {
        cout << "\nQueue in posizione " << i;
        print(v[i]);
       }
   break;

   case 'p': 
   cout << menu;
   break;

   default: 
   cout << "\nOpzione non valida\n";
   }

cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
cin >> ch;
}
return 0;
} 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}

