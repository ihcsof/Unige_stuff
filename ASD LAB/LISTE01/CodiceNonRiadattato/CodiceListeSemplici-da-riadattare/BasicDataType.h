#ifndef DataType_H
#define DataType_H
//#define BasicDataType
#include <iostream>
#ifdef BasicDataType
typedef int DataType;
#else
typedef struct people_t
{
	std::string family_name;
	std::string first_name;
	int born_on;
	std::string born_in;
} DataType;
#endif
/*
Try to read a value of type DataType from the stream input_stream.
Each line in input_stream refers to a different data; thus, after reading a data from a line,
any further entry on the same line, if any, has to be ignored.
If the reading is successfull, the function assigns the reading result to the parameter value
and returns true; otherwise, it returns false
*/
bool ReadData(std::istream& input_stream, DataType& value);
/*
The function writes on output_stream its argument value
*/
void WriteData(std::ostream& output_stream, DataType value);
/*
The function returns a negative value if first is smaller than second, 0 if they are equal,
and a positive value if first is greater then second
*/
int DataComparer(DataType first, DataType second);
#endif

