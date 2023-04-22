#include <iostream>
#include <bits/stdc++.h>
#include <climits>

using edge = std::pair<int, int>;
using graph = std::vector<std::vector<edge>>;

void dijkstra(const graph& g, int s) {
	std::vector<int> dist(g.size(), INT_MAX);
	std::vector<int> parent(g.size(), -1);
	dist[s] = 0;
	
	std::priority_queue<edge, std::vector<edge>, std::greater<edge>> q;
	q.emplace(s, 0);

	while(!q.empty()) {
		auto u = q.top().first;
		auto d = q.top().second;
		q.pop();

		if(d > dist[u]) continue;
		for(const auto& [v, vdis] : g[u]) {
			if(d + vdis < dist[v]) {
				dist[v] = d + vdis;
				q.emplace(vdis, v);
				parent[v] = u;
			}
		}
	}
	
}

int main() {
	int dim;
	std::cout << "dim: ";
	std::cin >> dim;
	graph g(dim, std::vector<edge>());

	/*g[0].emplace_back(1, 7);
	g[1].emplace_back(0, 7);
	g[0].emplace_back(2, 12);
	g[2].emplace_back(0, 12);
	g[1].emplace_back(2, 2);
	g[2].emplace_back(1, 2);
	g[1].emplace_back(3, 9);
	g[3].emplace_back(1, 9);
	g[2].emplace_back(4, 10);
	g[4].emplace_back(2, 10);
	g[3].emplace_back(5, 1);
	g[5].emplace_back(3, 1);
	g[3].emplace_back(4, 4);
	g[4].emplace_back(3, 4);
	g[4].emplace_back(5, 5);
	g[5].emplace_back(4, 5);*/

	g[0].emplace_back(1, 3);
	g[1].emplace_back(2, 4);
	g[2].emplace_back(0, 5);
	g[1].emplace_back(3, 5);
	g[2].emplace_back(3, 7);
	g[2].emplace_back(6, 2);
	g[3].emplace_back(6, 4);
	g[3].emplace_back(4, 1);
	g[4].emplace_back(5, 1);
	g[5].emplace_back(3, 4);
	g[1].emplace_back(0, 3);
	g[2].emplace_back(1, 4);
	g[0].emplace_back(2, 5);
	g[3].emplace_back(1, 5);
	g[3].emplace_back(2, 7);
	g[6].emplace_back(2, 2);
	g[6].emplace_back(3, 4);
	g[4].emplace_back(3, 1);
	g[5].emplace_back(4, 1);
	g[3].emplace_back(5, 4);
	dijkstra(g, 0);
}
