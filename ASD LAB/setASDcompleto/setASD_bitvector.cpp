#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 

using namespace std;

int main()
{
try {

unsigned int x1, x2;
x1 = 0;
x2 = ~0;
cout << "0: " << x1 << endl;
cout << "~0: " << x2 << endl;
cout << "~~0: " << ~x2 << endl;

x1 = 6;
x2 = 4;
cout << x1 << " | " << x2 << " = " << (x1|x2) << endl;

cout << x1 << " & " << x2 << " = " << (x1&x2) << endl;


x1 = 52;  // 0110100
x2 = 104; // 1101000
cout << x1 << " | " <<  x2 << " = " << (x1|x2) << endl; // 1111100
 
cout << x1 << " & " << x2 << " = " << (x1&x2) << endl;  // 0100000

	

return 0;
} 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}

