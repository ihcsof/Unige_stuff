#include <vector>
#include <iostream>
#include <fstream>

#include "BasicDataType.h"
#include "BasicList.h"


using namespace std;
int main(int argc, char* argv[])
{
	#ifdef BasicDataType
	ifstream my_input("SimpleInput.txt");
	// ifstream my_input("empty.txt");
	// ifstream my_input("onlyOne.txt");
#else
	ifstream my_input("People.txt");
#endif	
	basic_list my_list; // non posso mettere my_list = emptyList!!! Devo creare la sentinella
	create_empty(my_list);
    read_list(my_input, my_list);
	print_list(cout, my_list);
}
