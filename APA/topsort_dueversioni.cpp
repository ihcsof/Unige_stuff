#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using v = std::vector<int>;

using edge = std::pair<int, int>;
using graph = std::vector<std::vector<edge>>;

#define NERO true
#define BIANCO false

// topological sort algoritmo pacco
v topsort1(const graph& g) {
	v in_degree(g.size(), 0);
	v ord;

	for(const auto& g_i : g)
		for(const auto& [t, w] : g_i)
			in_degree[t]++;
	// Sequenza riempita coi nodi sorgente
	std::queue<int> q;
	for(int i = 0; i < g.size(); ++i)
		if(!in_degree[i]) q.push(i);

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		// Aggiungo "in fondo" a ord il nodo u
		ord.push_back(u);
		// per ogni arco da u a v decremento indegree..
		//.. e se indegree scende a 0 inserisco nella seq.
		for(const auto& [v, w] : g[u])
			if(!(--in_degree[v])) q.push(v);
	}
	return ord;
}

void dfs(const graph& g, int u, int& time, std::vector<bool>& mark, v& end) {
	time++;
	// std::cout << u << '\n';
	mark[u] = NERO;
	for(const auto& [v, w] : g[u])
		if(!mark[v]) dfs(g, v, time, mark, end);
	end[u] = ++time;
}

// topological sort algoritmo DFS con timestamp
v topsort2(const graph& g) {
	std::vector<bool> mark(g.size(), BIANCO);
	v end(g.size());
	int aux = 0;
	for(int u = 0; u < g.size(); ++u)
		if(!mark[u]) dfs(g, u, aux, mark, end);
	return end;
}

int main() {

	graph g(8, std::vector<edge>());

	g[0].emplace_back(1, 1);
	g[0].emplace_back(2, 1);
	g[0].emplace_back(4, 1);
	g[1].emplace_back(5, 1);
	g[2].emplace_back(3, 1);
	g[3].emplace_back(4, 1);
	g[3].emplace_back(7, 1);
	g[4].emplace_back(5, 1);
	g[5].emplace_back(6, 1);
	g[6].emplace_back(7, 1);
	
	v ord1 = topsort1(g);
	// STAMPA GLI INDICI DEI NODI
	for(int i = 0; i < ord1.size(); ++i)
			std::cout << ord1[i] << " ";
	std::cout << '\n';

	v ord2 = topsort2(g);
	// STAMPA I VALORI TIME CORRISPONDENTI AI NODI
	// (da leggere al contrario)
	for(int i = 0; i < ord2.size(); ++i)
			std::cout << ord2[i] << " ";
	std::cout << '\n';
}
