#include "bitVector.h"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace bit;

bitV bit::create(int s) {
	bitV v;
	v.size = s;
	v.nData = (s/8)+1;
	v.data = new char[(s/8)+1]{0};
	return v;
}

void bit::insertElem(int e, bitV& v) {
	if(e < 0 || (e/8) > (v.nData - 1))
		return;

	int index = (e/8);
	v.data[index] = v.data[index] | (char) 1 << (e % 8);
}

void bit::deleteElem(int e, bitV& v){
	if(e < 0 || (e/8) > (v.nData - 1))
		return;

	int index = (e/8);
	char aux = v.data[index] & (char) 1 << (e % 8);
	if(aux)
		v.data[index] -= aux;
}

void bit::printB(const bitV& v) {
	for(int i=0; i<v.nData; ++i)
		for(int j=0; j<8; ++j)
			if(v.data[i] & (char) 1 << j)
				std::cout << (i*8)+j << " ";
	std::cout << std::endl;
}

bool bit::isEmpty(const bitV& v) {
	for(int i=0; i<v.nData; ++i)
		for(int j=0; j<8; ++j)
			if(v.data[i] & (char) 1 << j)
				return false;
	return true;
}

int bit::size(const bitV& v){
	int count = 0;

	for(int i=0; i<v.nData; ++i)
		for(int j=0; j<8; ++j)
			count += (bool) (v.data[i] & (char) 1 << j);
	
	return count;
}

bool bit::member(int e, const bitV& v){
	if(e < 0 || (e/8) > (v.nData - 1))
		return false;
	int index = (e/8);
	return (v.data[index] & (char) 1 << (e % 8));
}

bitV bit::operator & (const bitV& v1, const bitV& v2)  {
	assert(v1.nData == v2.nData);
	
	bitV v3;
	v3.size = v1.size;
	v3.nData = v1.nData;
	v3.data = new char[v1.nData];

	for(int i=0; i<v3.nData; ++i)
		v3.data[i] = v1.data[i] & v2.data[i];
	
	return v3;		
}

bitV bit::operator | (const bitV& v1, const bitV& v2)  {
	assert(v1.nData == v2.nData);
	
	bitV v3;
	v3.size = v1.size;
	v3.nData = v1.nData;
	v3.data = new char[v1.nData];

	for(int i=0; i<v3.nData; ++i)
		v3.data[i] = v1.data[i] | v2.data[i];
	
	return v3;	
}

//shift a dx per onor di cultura: v1.data[i] >> 1 & (char) 1

bool bit::isSubset(const bitV& v1, const bitV& v2){
	if(v1.nData > v2.nData) return false;

	for(int i=0; i<v1.nData; ++i)
		for(int j=0; j<8; ++j)
			if((v1.data[i] & (char) 1 << j) && !(v2.data[i] & (char) 1 << j))
				return false;
	return true;
}
