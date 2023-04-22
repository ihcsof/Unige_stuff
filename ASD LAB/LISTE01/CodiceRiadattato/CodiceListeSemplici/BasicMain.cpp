#include <vector>
#include <iostream>
#include <fstream>

#include "BasicDataType.h"
#include "BasicList.h"

using namespace std;
using namespace lst;

int main(int argc, char* argv[])
{
	vector<DataType> all_data;
#ifdef BasicDataType
	ifstream my_input("SimpleInput.txt");
#else
	ifstream my_input("People.txt");
#endif
	// TESTING DATATYPE
	while (!my_input.eof())
	{
		DataType d;
		if (ReadData(my_input, d))
			all_data.push_back(d);
	}
	cout << "ho letto" << endl;
	for (int i = 0; i < all_data.size(); ++i) {
		WriteData(cout, all_data[i]);
		cout << endl;
	}
	for (int i = 1; i < all_data.size(); ++i) {
		WriteData(cout, all_data[0]);
		int comparison = DataComparer(all_data[0], all_data[i]);
		cout << " e' " << (comparison < 0 ? "minore di " : comparison>0 ? "maggiore di " : "uguale a ");
		WriteData(cout, all_data[i]);
		cout << endl;
	}
	// TESTING LIST
	lst::basic_list my_list = emptyList;
	lst::head_insert(my_list, all_data[0]);
	cout << "lista con solo il primo elemento del file" << endl;
	lst::print_list(cout, my_list);
	for (int i = 1; i < 5; ++i)
		lst::head_insert(my_list, all_data[i]);
	cout << "lista con i primi 5 elementi del file (in ordine invertito perche' inserisco in testa)" << endl;
	lst::print_list(cout, my_list);
	cout << "stessa lista avendo cancellato" << endl;
	WriteData(cout, all_data[0]);
	cout << endl;
	cout << endl;
	if (lst::remove(my_list, all_data[0], false))
		cout << "ho effettivamente rimosso" << endl;
	else
		cout << "non ho rimosso niente" << endl;
	cout << "e mi e'rimasta la lista" << endl;
	lst::print_list(cout, my_list);

	lst::delete_list(my_list);
	cout << "lista con tutti gli elementi del file (in ordine invertito perche' inserisco in testa)" << endl;
	my_input.clear();
	my_input.seekg(0, ios::beg);
	lst::read_list(my_input, my_list);
	lst::print_list(cout, my_list);
	lst::delete_list(my_list);
	my_input.close();
	my_list = emptyList;
	lst::head_insert(my_list, all_data[0]);
	lst::head_insert(my_list, all_data[0]);
	lst::head_insert(my_list, all_data[1]);
	lst::head_insert(my_list, all_data[0]);
	lst::head_insert(my_list, all_data[2]);
	lst::head_insert(my_list, all_data[0]);
	lst::head_insert(my_list, all_data[0]);
	lst::head_insert(my_list, all_data[1]);
	cout << endl;	cout << endl;	cout << endl;	cout << endl;
	cout << "rimuovo dalla seguente lista" << endl;
	lst::print_list(cout, my_list);
	cout << "tutte le occorrenze del record" << endl;
	WriteData(cout, all_data[0]);
	cout << endl;	cout << endl;	cout << endl;
	if (lst::remove(my_list, all_data[0], true))
		cout << "ho effettivamente rimosso" << endl;
	else
		cout << "non ho rimosso niente" << endl;
	cout << "e mi e'rimasta la lista" << endl;
	lst::print_list(cout, my_list);
	lst::delete_list(my_list);
}
