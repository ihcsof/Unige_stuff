#include "dictionary.h"

using namespace std::chrono;

// Funzione di init dell'output su file excel
void initOutput(std::ofstream& o) {
	o << ",";
	o << "# elementi memorizzati,";
	o << "# bucket,";
	o << "# atteso di elementi per bucket (= fattore di carico),";
	o << "deviazione standard";
	o << "\n";
}

// Funzione di init dell'output su file excel
void initOutput2(std::ofstream& o, std::vector<std::string>& vFiles, std::vector<std::string>& vKeys) {
	o << ",";
	std::string f0 = vFiles[0].substr(10,vFiles[0].back());
	std::string f1 = vFiles[1].substr(10,vFiles[1].back());
	o << f0 << " lettura da file,";
	o << "a.txt inserimento (\"asas\" - \"prova\"),";
	for(int i = 0; i < 5; ++i)
		o << f0 << " ricerca chiave \"" << vKeys[i] << "\",";
	o << f1 << " lettura da file,";
	for(int i = 0; i < 3; ++i)
		o << f1 << " ricerca chiave \"" << vKeys[i+5] << "\",";
	o << "\n";
}

void testL(std::ofstream& o, std::vector<std::string>& vFiles, std::vector<std::string>& vKeys) {
	o << "Test2: liste collegate ordinate,";
	dict::Dictionary1 d;
	// Per il calcolo del tempo impiegato
	high_resolution_clock::time_point t1, t2;
   double duration;
	// Stringa dummy per ottenere risultati riconducibili a quelli del test manuale
	std::string a;

	t1 = high_resolution_clock::now();
	d = readFromFile1(vFiles[0]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	t1 = high_resolution_clock::now();
	dict::insertElem("asas", "prova", d);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 5; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	dict::erase(d);
	t1 = high_resolution_clock::now();
	d = readFromFile1(vFiles[1]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 3; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i+5], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	dict::erase(d);
	o << "\n";
}

void testV(std::ofstream& o, std::vector<std::string>& vFiles, std::vector<std::string>& vKeys) {
	o << "Test1: vector ordinato,";
	dict::Dictionary2 d;
	// Per il calcolo del tempo impiegato
	high_resolution_clock::time_point t1, t2;
   double duration;
	// Stringa dummy per ottenere risultati riconducibili a quelli del test manuale
	std::string a;

	t1 = high_resolution_clock::now();
	d = readFromFile2(vFiles[0]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	t1 = high_resolution_clock::now();
	dict::insertElem("asas", "prova", d);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 5; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	t1 = high_resolution_clock::now();
	d = readFromFile2(vFiles[1]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 3; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i+5], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	o << "\n";
}

void testB(std::ofstream& o, std::vector<std::string>& vFiles, std::vector<std::string>& vKeys) {
	o << "Test3: BST,";
	dict::Dictionary3 d;
	// Per il calcolo del tempo impiegato
	high_resolution_clock::time_point t1, t2;
   double duration;
	// Stringa dummy per ottenere risultati riconducibili a quelli del test manuale
	std::string a;
	
	t1 = high_resolution_clock::now();
	d = readFromFile3(vFiles[0]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	t1 = high_resolution_clock::now();
	dict::insertElem("asas", "prova", d);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 5; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	dict::erase3(d);
	t1 = high_resolution_clock::now();
	d = readFromFile3(vFiles[1]);
	t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
	o << duration << ",";
	for(int i = 0; i < 3; ++i) {
		t1 = high_resolution_clock::now();
		a = dict::search(vKeys[i+5], d);
		t2 = high_resolution_clock::now();
   	duration = duration_cast<microseconds>( t2 - t1 ).count();
		o << duration << ",";
	}
	dict::erase3(d);
	o << "\n";
}
