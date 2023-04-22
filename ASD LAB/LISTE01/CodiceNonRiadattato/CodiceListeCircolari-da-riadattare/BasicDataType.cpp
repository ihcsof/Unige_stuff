#include <iostream>
#include <sstream>
#include <string>

#include "BasicDataType.h"
using namespace std;

#ifdef BasicDataType
bool ReadData(std::istream& input_stream, DataType& value)
{
	string line;
	getline(input_stream, line);
	istringstream s(line);
	if (s >> value)	return true;
	return false;
}


void WriteData(std::ostream& output_stream, DataType value)
{
	output_stream << value;
}


int DataComparer(DataType first, DataType second)
{
	if (first < second)
		return -1;
	if (second < first)
		return 1;
	return 0;
}
#else
bool ReadData(std::istream& input_stream, DataType& value)
{
	string line;
	getline(input_stream, line);
	istringstream s(line);
	if (s >> value.family_name&&s >> value.first_name&&s >> value.born_on&&s >> value.born_in)	return true;
	return false;
}


void WriteData(std::ostream& output_stream, DataType value)
{
	output_stream << value.family_name << " " << value.first_name << ", nato nel " << value.born_on << " a " << value.born_in;
}
/*
Lexicographic order: family name, then first name, then age, then place of birth
*/
int DataComparer(DataType first, DataType second)
{
	if (first.family_name < second.family_name)
		return -1;
	if (second.family_name < first.family_name)
		return 1;
	if (first.first_name < second.first_name)
		return -2;
	if (second.first_name < first.first_name)
		return 2;
	if (first.born_on > second.born_on)
		return -3;
	if (second.born_on > first.born_on)
		return 3;
	if (first.born_in < second.born_in)
		return -4;
	if (second.born_in < first.born_in)
		return 4;
	return 0;
}
#endif
