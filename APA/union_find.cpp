#pragma once

#include <vector>
#include <iostream>
#include <bits/stdc++.h>

// CLASSE UNION FIND
// -----------------

using v = std::vector<int>;

class Uf {
	private:
		// Sz max
		size_t size;
		// Numero di componenti(gruppi)
		size_t n;
		// vettore con le size dei set
		v sz;
		// ptr al padre (tipo array dei padri)
		// se sei padre di te stesso sei il rappresentante
		v id;

	public:
		Uf(size_t n) : n(n), size(n), sz(n, 1), id(n) {
			for(int i = 0; i < n; ++i)
				id[i] = i;
		}

		// find con path compress. di tutti i nodi del gruppo di e
		int find(int e) {
			int root = e;
			while(id[root] != root)
				root = id[root];
			while(e != root) {
				int aux = id[e];
				id[e] = root;
				e = aux;
			}
			return root;
		}

		bool areConnected(int e1, int e2) {
			return find(e1) == find(e2);
		}

		int sizeOfSet(int e) {
			return sz[find(e)];
		}

		int getSize() {
			return size;
		}

		int numberComponents() {
			return n;
		}

		void unify(int e1, int e2) {
			int t1 = find(e1);
			int t2 = find(e2);

			if(t1 == t2) return;

			(sz[t1] < sz[t2]) ? (id[t1] = t2, sz[t2] += sz[t1]) : (id[t2] = t1, sz[t1] += sz[t2]);
			n--;
		}

		~Uf() = default;
};

// KRUSKAL con U-F
// ---------------

using edge = std::pair<int, int>;
using graph = std::vector<std::vector<edge>>;

void kruskal(const graph& g) {
	Uf uf(g.size()); // UF

	// Vettore con pair(to, peso) + from --> arco
	std::vector<std::tuple<int, int, int>> ordEdges; // S
	for(int i = 0; i < g.size(); ++i) {
		for(const auto& [t, w] : g[i]) {
			ordEdges.emplace_back(w, i, t);
		}
	}
	// Ordino vettore di archi(peso, from, to) secondo il peso
	std::sort(ordEdges.begin(), ordEdges.end());

	graph forest(g.size(), std::vector<edge>()); // T

	// finchè s non è vuota union by need
	for(const auto& [w, f, t] : ordEdges) {
		if(!uf.areConnected(f, t)) {
			uf.unify(f, t);
			forest[f].emplace_back(t, w);
			forest[t].emplace_back(f, w);
		}
	}

	/*for(int i = 0; i < forest.size(); ++i) {
		for(const auto& [t, w] : forest[i]) {
			std::cout << i << " " << t << " " << w << "\n";
		}
	}*/
}

int main() {
	// Prova U-F
	Uf uf(12);
	
	uf.unify(1, 2);
	uf.unify(5, 3);
	uf.unify(2, 3);
	std::cout << uf.find(3) << "\n";
	std::cout << uf.sizeOfSet(3) << "\n";
	std::cout << uf.numberComponents() << "\n";
	// ------------------------------

	// Prova Kruskal
	graph g(6, std::vector<edge>());

	g[0].emplace_back(1, 6);
	g[1].emplace_back(0, 6);
	g[0].emplace_back(2, 5);
	g[2].emplace_back(0, 5);
	g[0].emplace_back(3, 1);
	g[3].emplace_back(0, 1);
	g[1].emplace_back(3, 5);
	g[3].emplace_back(1, 5);
	g[2].emplace_back(3, 5);
	g[3].emplace_back(2, 5);
	g[1].emplace_back(4, 3);
	g[4].emplace_back(1, 3);
	g[2].emplace_back(5, 2);
	g[5].emplace_back(2, 2);
	g[3].emplace_back(4, 6);
	g[4].emplace_back(3, 6);
	g[3].emplace_back(5, 4);
	g[5].emplace_back(3, 4);
	g[4].emplace_back(5, 6);
	g[5].emplace_back(4, 6);

	kruskal(g);
}
