#include <vector>
#include <iostream>
#include <fstream>

#include "BasicDataType.h"
#include "BasicList.h"

using namespace std;
using namespace lst;

int main(int argc, char* argv[])
{
char ch;
#ifdef BasicDataType
	ifstream my_input("SimpleInput.txt");
	// ifstream my_input("empty.txt");
	// ifstream my_input("onlyOne.txt");
#else
	ifstream my_input("People.txt");
#endif	
	basic_list my_list = emptyList;
    read_list(my_input, my_list);
	print_list(cout, my_list);
	cout << "\nInserire un carattere per andare avanti\n";
	cin >> ch;
	print_listOLD(cout, my_list);
}
