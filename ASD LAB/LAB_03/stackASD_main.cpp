#include "stackASD-ptr.h" 


const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono degli stack inizialmente vuoti.\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura degli elementi di uno stack (con inserimento in cima) da file terminato da -1000000 (2 operandi: nome_file indice);\nb: lettura degli elementi di uno stack (con inserimento in cima) da standard input (1 operando: indice);\nc: push (2 operandi: elem indice);\nd: pop (1 operando: indice);\ne: top (1 operando: indice); \nf: isEmpty (1 operando: indice); \nn: stampa (1 operando: indice);\no: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";

const int MAXREG = 10;

int main()
{
try {
vector<stack::Stack> v(MAXREG);
int i;
for (i=0; i<MAXREG; ++i)
   v[i] = stack::EMPTYSTACK;
stack::Elem e;

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
   stack::push(e, v[i]);
   print(v[i]);
   break;


   case 'd':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   e = stack::pop(v[i]);
   cout << "\nStack in posizione " << i; 
   print(v[i]);
   if (e != stack::EMPTYELEM)
      cout << "\nElemento che era in testa allo stack " << i << ": " << e << endl; 
   else 
      cout << "\nStack vuoto\n";
   break;

   case 'e':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   e = stack::top(v[i]);
   cout << "\nStack in posizione " << i; 
   print(v[i]);
   if (e != stack::EMPTYELEM)
      cout << "\nElemento in testa allo stack " << i << ": " << e << endl; 
   else 
      cout << "\nStack vuoto\n";
   break;

   case 'f':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   if (stack::isEmpty(v[i])) 
      cout << "\nLo stack in posizione " << i << " e' vuoto\n";
   else 
      {cout << "\nLo stack in posizione " << i << " non e' vuoto\n"; print(v[i]);}
   break;

   case 'n':
   cin >> i;
   if (i<0 || i>=MAXREG) {cout << "\nIndice fuori range\n"; break;}
   print(v[i]);
   break;

   case 'o':
   for (int i=0; i<MAXREG; ++i)
       {
        cout << "\nStack in posizione " << i;
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

