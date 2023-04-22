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
	ifstream my_input2("SimpleInput2.txt");
	// ifstream my_input("empty.txt");
	// ifstream my_input("onlyOne.txt");
#else
	ifstream my_input("People.txt");
#endif	
	lst::basic_list my_list; // non posso mettere my_list = emptyList!!! Devo creare la sentinella
	lst::create_empty(my_list);
  lst::read_list(my_input, my_list);
	lst::print_list(cout, my_list);
	cout << boolalpha << is_in(my_list, 23) << endl;
	cout << boolalpha << is_in(my_list, 26) << endl;
	cout << boolalpha << is_in(my_list, 789) << endl;

	lst::basic_list my_list2; // non posso mettere my_list = emptyList!!! Devo creare la sentinella
	lst::create_empty(my_list2);
  lst::read_list(my_input2, my_list2);
	lst::print_list(cout, my_list2);

	cout << endl << "\nCONCAT:\n";
	lst::basic_list newList = concatNew(my_list, my_list2);
	lst::print_list(cout, newList);

	delete_list(newList);
	cout << endl << "\nDopo delete:\n";
	lst::print_list(cout, newList);

	cout << endl << "\nCONCAT in place:\n";
	concat(my_list, my_list2);
	cout << endl << "\nlist1:\n";
	lst::print_list(cout, my_list);
	cout << endl << "\nlist2:\n";
	//lst::print_list(cout, my_list2);
}
