#include <iostream>
#include <bits/stdc++.h>
#include <climits>

using edge = std::pair<int, int>;
using graph = std::vector<std::vector<edge>>;

graph floyd(const graph& g) {
	graph m(g.size(), std::vector<edge>());
	for(int i = 0; i < g.size(); ++i)
		m[i].resize(g.size());
	
	for(int i = 0; i < g.size(); ++i) {
		for(int j = 0; j < g.size(); ++j) {
			bool test = false;
			if(i == j) {
				m[i][j].first = 0;
				m[i][j].second = -1;
			}
			else {
				m[i][j].first = INT_MAX >> 2;
				m[i][j].second = -1;
				for(const auto& [t, p] : g[i]) {
					if(j == t) {
						m[i][j].first = p;
						m[i][j].second = i;
					}
				}
			}
		}
	}

	for(int k = 0; k < g.size(); ++k)
		for(int i = 0; i < g.size(); ++i)
			for(int j = 0; j < g.size(); ++j)
				if(m[i][j].first > m[i][k].first + m[k][j].first) {
					m[i][j].first = m[i][k].first + m[k][j].first;
					m[i][j].second = m[k][j].second;
				}	
	
	
	return m;
}

int main() {
	int dim;
	std::cout << "dim: ";
	std::cin >> dim;
	graph g(dim, std::vector<edge>());

	g[0].emplace_back(1, 3);
	g[0].emplace_back(4, -4);
	g[0].emplace_back(2, 8);
	g[1].emplace_back(3, 1);
	g[1].emplace_back(4, 7);
	g[2].emplace_back(1, 4);
	g[3].emplace_back(2, -5);
	g[3].emplace_back(0, 2);
	g[4].emplace_back(3, 6);

	graph m = floyd(g);

	for(int i = 0; i < g.size(); ++i) {
			for(int j = 0; j < g.size(); ++j)
				std::cout << m[i][j].first << " " << m[i][j].second << '\n';
	}
	std::cout << '\n';
}
