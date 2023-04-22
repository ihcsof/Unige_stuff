#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <string>  
#include <chrono>        
#include "string-utility.h"
#include "list-array.h"

using namespace std::chrono; 
using namespace std; 

namespace tree{

enum Error {OK, FAIL};

typedef string Label;      

const Label emptyLabel = "$#$#$";

struct treeNode; // definita nel file tree.cpp

typedef treeNode* Tree; // un albero è identificato dal puntatore alla sua radice; useremo indistintamente "albero" e "puntatore a nodo"

const Tree emptyTree = NULL; 

bool isEmpty(const Tree&);
Error addElem(const Label, const Label, Tree&);     
Error deleteElemR(const Label, Tree&);
Error deleteElemI(const Label, Tree&);
Label father(const Label, const Tree&);
list::List children(const Label, const Tree&);
int degree(const Label, const Tree&);
list::List ancestorsR(const Label, const Tree&);
list::List ancestorsI(const Label, const Tree&);
Label leastCommonAncestor(const Label, const Label, const Tree&);
bool member(const Label, const Tree&);
int numNodes(const Tree&);
Tree createEmpty();
}


/* Funzioni che non caratterizzano il TDD Tree, ma che servono per input/output */
tree::Tree readFromFile(string);
void printTree(const tree::Tree&);
