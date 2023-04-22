#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 

using namespace std;

// Implementa SET con strutture collegate mediante puntatori e tipo base Elem dotato di ordinamento

namespace set{

/**************************** Codici di errore ********************************************/
enum Error {OK, FAIL, EMPTY, FULL};

/**************************** Tipi e costanti *********************************************/

typedef int Elem;      // tipo base 
struct cell;
typedef cell *Set;
const int FINEINPUT = -1000000;
const Set emptySet = NULL;

/************************* operazioni stateful (con side effect) ******************************************/

void createEmpty(Set&);                 /* crea l'insieme vuoto */
void deleteSetS(Set&);                  /* "smantella" un insieme liberando la memoria allocata con le new */
Error insertElemS(const Elem, Set&);	/* inserisce un elemento nell'insieme, restituisce FAIL in caso di errore */
Error insertElemInOrderS(const Elem, Set&); /* inserisce un elemento nell'insieme, mantenendo l'ordine; restituisce FAIL in caso di errore */
Error deleteElemS(const Elem, Set&);	/* cancella un elemento dall'insieme, restituisce EMPTY se l'insieme è vuoto */


/************************* operazioni stateless (funzionali) ******************************************/

Set createEmpty();
Set insertElem(const Elem, const Set&);
Set deleteElem(const Elem, const Set&);
Set setUnion(const Set&, const Set&);
Set setIntersection(const Set&, const Set&);
Set setDifference(const Set&, const Set&);
bool isEmpty(const Set&);
bool isSubset(const Set&, const Set&);
int size(const Set&);
bool member(const Elem, const Set&);
}

set::Set setReadFromFile(string);
set::Set setReadFromStdin();
void setPrint(const set::Set&);
