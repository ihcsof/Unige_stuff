/////////////////////////////////////////////////////////////////////////////
//
// COME COMPILARE IL PROGRAMMA
//
// Per usare l'implementazione del dizionario basata su vettore ordinato:
//
// g++ -std=c++11 -Wall -DUSE_ORDERED_VECTOR dictionary-orderedvector.cpp string-utility.cpp dictionary-main.cpp
//
// Per usare l'implementazione del dizionario basata su lista doppiamente
// collegata con sentinella e ordinata:
//
// g++ -std=c++11 -Wall -DUSE_ORDERED_LIST dictionary-doublylinkedlist.cpp string-utility.cpp dictionary-main.cpp
//
// Per usare l'implementazione del dizionario basata su tabella hash:
//
// g++ -std=c++11 -Wall -DUSE_HASH_TABLE dictionary-hashtable.cpp string-utility.cpp dictionary-main.cpp
//
/////////////////////////////////////////////////////////////////////////////


#include "dictionary.h" 


const int maxreg = 10;
const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono dei dizionari [chiamati anche array associativi o mappe], inizialmente vuoti.\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura di un dizionario da file [le righe del file devono avere la sintassi --> key: value.<enter>] (2 operandi:   nome_file  indice);\nb: lettura di un dizionario da standard input (1 operando: indice);\nc: inserimento di una coppia (chiave, valore) in un dizionario, operazione stateful (3 operandi:  chiave   valore   indice); nota: inserire la chiave, il valore e l'indice separati da : e tutti sulla stessa linea, ad esempio -> gatto:mammifero peloso e affettuoso:3\nd: cancellazione di un elemento da un dizionario, operazione stateful (2 operandi: chiave   indice);\ne: ricerca (2 operandi: chiave   indice); \nf: stampa (1 operando: indice);\ng: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";


int main()
{
try {
vector<dict::Dictionary> v(maxreg);
for (int j=0; j<maxreg; ++j) {v[j] = dict::createEmptyDict();}
dict::Elem e;
dict::Key key, kcopy;
dict::Value value;
int i;
string nome_file,index;
high_resolution_clock::time_point t1, t2;
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
   t1 = high_resolution_clock::now();
   v[i] = readFromFile(nome_file);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nL'operazione ha richiesto " << duration << " microsecondi\n";
   break;


   case 'b':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   t1 = high_resolution_clock::now();
   v[i] = readFromStdin();
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nL'operazione ha richiesto " << duration << " microsecondi\n";
   break;


   case 'c':
   getline(cin, key, ':'); // cout << "\n[readFromStream] key: " << key;
   getline(cin, value, ':'); 
   getline(cin, index);
   i=index[0]-'0';
   if (i<0 || i>=maxreg) {cout << "\nIndice " << i << " fuori range. Inserire la chiave, il valore e l'indice separati da : e tutti sulla stessa linea e senza spazi dopo il : ad esempio    gatto:mammifero peloso e affettuoso:3\n"; break;}
   kcopy = key;
   removeBlanksAndLower(kcopy);
   t1 = high_resolution_clock::now();
   dict::insertElem(kcopy, value, v[i]);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nL'operazione ha richiesto " << duration << " microsecondi\n";
   break;


   case 'd':
   cin >> key >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   kcopy = key;
   removeBlanksAndLower(kcopy);
   t1 = high_resolution_clock::now();
   dict::deleteElem(kcopy, v[i]);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nL'operazione ha richiesto " << duration << " microsecondi\n";
   break;

   case 'e':
   cin >> key >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   kcopy = key;
   removeBlanksAndLower(kcopy);
   
   t1 = high_resolution_clock::now();
   value = dict::search(kcopy, v[i]);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nL'operazione di ricerca ha richiesto " << duration << " microsecondi\n";
   if (value == dict::emptyValue) cout << "Elemento non trovato\n";
   else cout << "Esito della ricerca \n" << value << "\n\n";

   break;

   case 'f':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   print(v[i]);
   break;

   case 'g':
   for (int i=0; i<maxreg; ++i)
       {
        cout << "\nDizionario in posizione " << i;
        print(v[i]);
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

