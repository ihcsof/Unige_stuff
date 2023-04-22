#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using seq = std::pair<int, std::pair<int,int>>;

void lcs(const std::vector<char>& v1, const std::vector<char>& v2) {
	int sz1 = v1.size() + 1;
	int sz2 = v2.size() + 1;
	
	seq** m = new seq*[sz1];
	for(int i = 0; i < sz1; ++i)
		m[i] = new seq[sz2];

	for(int i = 0; i < sz1; ++i) m[i][0].first = 0;
	for(int j = 0; j < sz2; ++j) m[0][j].first = 0;

	for(int i = 1; i < sz1; ++i) {
		for(int j = 1; j < sz2; ++j) {
			if(v1[i-1] == v2[j-1]) {
				m[i][j].first = 1 + m[i-1][j-1].first;
				m[i][j].second = std::make_pair(i-1, j-1);
			}
			else {
				if(m[i][j-1].first > m[i-1][j].first) {
					m[i][j].first = m[i][j-1].first;
					m[i][j].second = std::make_pair(i, j-1);
				}
				else {
					m[i][j].first = m[i-1][j].first;
					m[i][j].second = std::make_pair(i-1, j);
				}
			}
		}
	}

	// STAMPA
	std::cout << "\t\t";
	for(int j = 1; j < sz2; ++j)
		std::cout << "j: " << j << "(" << v2[j-1] << ") ";
	std::cout << '\n';
	for(int i = 0; i < sz1; ++i) {
		if(i)std::cout << "i: " << i << "(" << v1[i-1] << ") ";
		else std::cout << "i: " << i << "(x) ";
		for(int j = 0; j < sz2; ++j) {
			std::cout << m[i][j].first << "(";
			std::cout << m[i][j].second.first << " ";
			std::cout << m[i][j].second.second << ")  ";
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";

	/*int id1 = 7;
	int id2 = 6;
	std::string s;
	while(m[id1][id2].first) {
		if(m[id1][id2].second.first < id1 && m[id1][id2].second.second < id2) {
			id1--; id2--;
			s += v1[id1-1];
		}
		else if(m[id1][id2].second.first == id1 && m[id1][id2].second.second < id2) {
			id1--;
		}
		else {
			id2--;
		}
	}
	std::cout << s << '\n';*/
}


int main() {
	std::vector<char> v1 = {'A','T','C','B','A','B'};
	std::vector<char> v2 = {'B','A','C','A','T','B','A'};

	lcs(v2, v1);
}
