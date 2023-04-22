#include "token.h"

using namespace std;

// Implementa STACK con strutture collegate semplicemente mediante puntatori e tipo base Elem dotato di ordinamento
namespace stack{

typedef token Elem;
struct cell;
typedef cell *Stack;
const Stack EMPTYSTACK = nullptr;
const token EMPTYELEM = {" ",SCONOSCIUTO};

bool isEmpty(const Stack&);
void push(const Elem, Stack&);	/* aggiunge elem in cima (operazione safe, si può sempre fare) */
Elem pop(Stack&);	/* toglie dallo stack l'ultimo elemento e lo restituisce; se lo stack è vuoto la condizione è di errore. Lo segnaliamo restituendo EMPTYELEM (potremmo in alternativa sollevare un'eccezione) */
Elem top(Stack&);	/* restituisce l'ultimo elemento dello stack senza toglierlo; se lo stack è vuoto la condizione è di errore. Lo segnaliamo restituendo EMPTYELEM (potremmo in alternativa sollevare un'eccezione) */
}
