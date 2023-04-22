#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <chrono>          // necessario compilare con -std=c++11
#include <stdlib.h>        // srand, rand
#include <string>          // std::string

#include "string-utility.h"
#include "excel.h"


using namespace std::chrono; 
using namespace std; 

namespace dict {

// Codici di errore

enum Error {OK, FAIL};

// Tipi e costanti

typedef string Key;        // tipo base 
typedef string Value;      // tipo base 

const Key emptyKey = "###RESERVED KEYWORD### EMPTY KEY";
const Value emptyValue = "###RESERVED KEYWORD### EMPTY VALUE";

// Var
extern int tableDim;

typedef struct {
    Key	key;
    Value value;
} Elem;

// Implementazione basata su tabella hash

struct cell;
typedef cell* Bucket;
const Bucket emptyBucket = NULL;
typedef Bucket* Dictionary; // un Dictionary è un array di dimensione tableDim (che viene fissata in fase di inizializzazione), di puntatori a cell (che abbiamo chiamato "Bucket"); come già fatto in altre occasioni, la struttura di cell è definita nel file ausiliario per incapsulare il più possibile l'informazione

#ifndef USE_HASH_TABLE
// Implementazione basata su lista ordinata

struct nodo;
typedef nodo* Dictionary1;

// Implementazione basata su vettore ordinato

typedef vector<Elem> Dictionary2;

// Funzioni overloaded per liste dll
Error insertElem(const Key, const Value,  Dictionary1&);
Value search(const Key, const Dictionary1&);
Dictionary1 createEmptyDict1();
void erase(Dictionary1&);
// Funzioni overloaded per ordered vector
Error insertElem(const Key, const Value,  Dictionary2&);
Value search(const Key, const Dictionary2&);
Dictionary2 createEmptyDict2();

#endif

// Per hashtable
int h1(Key);
int h2(Key);
int h3(Key);
void deleteD(Dictionary&);

// Funzioni overloaded per hashtable
Error insertElem(const Key, const Value, Dictionary&, hashPointer);
Value search(const Key, const Dictionary&, hashPointer);
Dictionary createEmptyDict();

}  // end namespace Dict

// Funzioni overloaded per hashtable
dict::Dictionary readFromFile(string, hashPointer);
dict::Dictionary readFromStream(istream&, hashPointer);

#ifndef USE_HASH_TABLE

// Funzioni overloaded per liste dll
dict::Dictionary1 readFromFile1(string);
dict::Dictionary1 readFromStream1(istream&);
// Funzioni overloaded per ordered vector
dict::Dictionary2 readFromFile2(string);
dict::Dictionary2 readFromStream2(istream&);

#endif

// Per hashtable
void print(const dict::Dictionary&,  std::ostream& = cout);
