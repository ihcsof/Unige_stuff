#include <vector> 
#include <iostream>
#include <fstream> 
#include <stdexcept>

using namespace std;

vector<int> leggiVettoreDaFile(string);

void stampaVettoreEDurataSuStream(const vector<int>&, string, double, ofstream&);
