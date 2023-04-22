#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using v = std::vector<int>;

using edge = std::pair<int, int>;
using vedge = std::vector<edge>;
using graph = std::vector<std::vector<edge>>;

using gset = std::vector<v>;

#define NERO true
#define BIANCO false

void dfs3(const graph& g, int u, std::vector<bool>& mark, v& subset) {
	// std::cout << u << '\n';
	mark[u] = NERO;
	for(const auto& [v, w] : g[u])
		if(!mark[v]) dfs3(g, v, mark, subset);
	subset.push_back(u);
}

void dfs2(const graph& g, int u, int& time, std::vector<bool>& mark, vedge& end) {
	time++;
	// std::cout << u << '\n';
	mark[u] = NERO;
	for(const auto& [v, w] : g[u])
		if(!mark[v]) dfs2(g, v, time, mark, end);
	end[u].first = ++time;
}

// topological sort algoritmo DFS con timestamp
vedge topsort2(const graph& g) {
	std::vector<bool> mark(g.size(), BIANCO);
	vedge end(g.size(), std::pair(0, 0));
	for(int u = 0; u < g.size(); ++u)
		end[u].second = u;
	int aux = 0;
	for(int u = 0; u < g.size(); ++u)
		if(!mark[u]) dfs2(g, u, aux, mark, end);
	return end;
}

graph transpose(const graph& g) {
	graph gt(g.size(), std::vector<edge>());

	for(int i = 0; i < g.size(); ++i)
		for(const auto& [t, w] : g[i])
			gt[t].emplace_back(i, w);

	return gt;
}

gset cfc(const graph& g) {
	// Prendo top.sort con associati i nodi e ordino
	auto aux = topsort2(g);
	std::sort(aux.begin(), aux.end());

	graph gt = transpose(g);
	gset gs;
	std::vector<bool> mark(g.size(), 0);

	for(int i = aux.size()-1; i >= 0 ; --i) {
		if(mark[aux[i].second]) continue;
		v subset;
		dfs3(gt, aux[i].second, mark, subset);
		gs.push_back(std::move(subset));
	}
	
	return gs;
}

int main() {

	graph g(7, std::vector<edge>());

	g[0].emplace_back(1, 1);
	g[1].emplace_back(2, 1);
	g[2].emplace_back(0, 1);
	g[1].emplace_back(3, 1);
	g[2].emplace_back(3, 1);
	g[2].emplace_back(6, 1);
	g[3].emplace_back(6, 1);
	g[3].emplace_back(4, 1);
	g[4].emplace_back(5, 1);
	g[5].emplace_back(3, 1);

	gset gs = cfc(g);

	for(int i = 0; i < gs.size(); ++i) {
		std::cout << "C" << i+1 << ": ";
		for(int j = 0; j < gs[i].size(); ++j)
			std::cout << gs[i][j] << " ";
		std::cout << '\n';
	}
}
