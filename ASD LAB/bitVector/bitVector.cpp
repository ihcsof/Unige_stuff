#include "bitVector.h"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace bit;

bitV bit::create(int s) {
	bitV v;
	v.size = s;
	v.data = new bool[s]{false};
	return v;
}

void bit::insertElem(int e, bitV& v) {
	assert(e >= 0 && e < v.size);
	v.data[e] = true;
}

void bit::deleteElem(int e, bitV& v){
	assert(e >= 0 && e < v.size);
	v.data[e] = false;
}

bool bit::isSubset(const bitV& v1, const bitV& v2){
	if(v1.size > v2.size) return false;

	for(int i=0; i<v1.size; ++i)
		if(v1.data[i] && !v2.data[i])
			return false;
	return true;
}

bool isEmpty_aux(const bitV& v, int i) {
	if(i >= v.size) return true;
	if(v.data[i]) return false;
	return isEmpty_aux(v, i+1);
}

bool bit::isEmpty(const bitV& v) {
	return isEmpty_aux(v, 0);
}

int size_aux(const bitV& v, int i) {
	if(i >= v.size) return 0;
	return v.data[i] + size_aux(v, i+1);
}

int bit::size(const bitV& v){
	return size_aux(v, 0);
}

bool bit::member(int e, const bitV& v){
	assert(e >= 0 && e < v.size);
	return (v.data[e]);
}

void bit::printB(const bitV& v) {
	for(int i=0; i<v.size; ++i)
		std::cout << v.data[i] << " ";
	std::cout << std::endl;
}

void bit::print(const bitV& v) {
	for(int i=0; i<v.size; ++i)
		if(v.data[i])
			std::cout << i << " ";
	std::cout << std::endl;
}

bitV bit::toBin(char* p, size_t s) {
	bitV v;
	v.data = new bool[s*8];
	v.size = s*8;

	for(int i=0; i<s; ++i) {
		for(int j=0; j<8; ++j) {
			v.data[v.size-(j+(i*8))-1] = (*p & (char) 1 << j);
		}
		p++;
	}
	return v;
}

unsigned int bit::toInt(const bitV& v) {
	assert(v.size == 32);
	unsigned int x = 0;
	
	for(int i=0; i<v.size; ++i)
		if(v.data[i])
			x += pow(2, v.size-i-1);

	return x;
}

bool bit::operator == (const bitV& v1, const bitV& v2) {
	assert(v1.size == v2.size);
	for(int i=0; i<v1.size; ++i)
		if(v1.data[i] != v2.data[i])
			return false;
	return true;
}

bitV bit::operator & (const bitV& v1, const bitV& v2)  {
	assert(v1.size == v2.size);
	
	bitV v3;
	v3.data = new bool[v1.size];
	v3.size = v1.size;

	for(int i=0; i<v1.size; ++i)
		v3.data[i] = v1.data[i] && v2.data[i];

	return v3;
}

bitV bit::operator | (const bitV& v1, const bitV& v2)  {
	assert(v1.size == v2.size);
	
	bitV v3;
	v3.data = new bool[v1.size];
	v3.size = v1.size;

	for(int i=0; i<v1.size; ++i)
		v3.data[i] = v1.data[i] || v2.data[i];

	return v3;
}

bitV bit::operator - (const bitV& v1, const bitV& v2)  {
	assert(v1.size == v2.size);
	
	bitV v3;
	v3.data = new bool[v1.size];
	v3.size = v1.size;

	for(int i=0; i<v1.size; ++i)
		v3.data[i] = v1.data[i] && !v2.data[i];

	return v3;
}

bitV bit::operator ~ (const bitV& v)  {
	bitV vN;
	vN.data = new bool[v.size];
	vN.size = v.size;

	for(int i=0; i<vN.size; ++i)
		vN.data[i] = !v.data[i];

	return vN;
}
