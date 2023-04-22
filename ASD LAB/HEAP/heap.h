#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 

using namespace std;
 
namespace heap {

const int BLOCKDIM = 4;
typedef int Elem;      // tipo base 

typedef struct {
    Elem* a;
    int size;
    int maxsize;
} array;

const int FINEINPUT = -1000000;
const int EMPTYELEM = -1000000;

array createEmpty();
bool isEmpty(const array&);
void insertElem(Elem, array&);
Elem deleteMax(array&);
Elem findMax(array&);

}


heap::array readFromFile(string);
heap::array readFromStdin();
heap::array readFromStream(istream&);
void print(const heap::array&);
