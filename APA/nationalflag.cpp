#include <iostream>
#include <vector>

void flag(std::vector<char>& v) {
	int u = 0;
	int w = v.size();
	int b = v.size();

	// Inv: Red(1, u-1) & White(w, b-1) & Blu(b, n) & u <= w

	// Pre: u = 1 & w = b = n+1
	while(u < w) {
		switch(v.at(w-1)) {

			case 'R':
				std::swap(v.at(u), v.at(w-1));
				u++;
				break;

			case 'W':
				w--;
				break;

			case 'B':
				std::swap(v.at(w-1), v.at(b-1));
				w--;
				b--;
		}
	}
	// Post: Red(1, w-1) & White(w, b-1) & Blu(b, n)
}

int main() {
	
	std::vector<char> v = {'R','W','R','R','B','W','B','B','R','W','R','W','B','B','W','W','R'};

	flag(v);
	for(int i = 0; i < v.size(); ++i)
		std::cout << v.at(i);
	std::cout << "\n";
}
