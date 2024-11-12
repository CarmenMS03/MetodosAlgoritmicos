#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Grafo.h"
#include <vector>

using namespace std;
const int MAX = 10000;
const int INF = 1000000000;

int bfs(int o, int ttl, const Grafo& g, const int N) {
	int inalcanzables=0;
	vector<int> dist(MAX, 0);
	dist[o] = 0;
	vector<bool> visitados(MAX, false);
	int visit = 1;
	visitados[o] = true;
	queue<int> q; q.push(o);

	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : g.ady(v)) {
			if (!visitados[w]) {
				visit++;
				dist[w] = dist[v] + 1;
				if (dist[w] > ttl) inalcanzables++;
				visitados[w] = true;
				q.push(w);
			}
		}
	}

	inalcanzables = inalcanzables + (N - visit);
	return inalcanzables;
}

bool resuelve() {
	int N, C;
	cin >> N >> C;

	if (!cin) return false;
	
	Grafo g(N);
	for (int i = 0; i < C; i++) {
		int a, b;
		cin >> a >> b;
		g.ponArista(a - 1, b - 1); //no dirigido
	}
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int origen, ttl;
		cin >> origen >> ttl;
		cout << bfs(origen-1,ttl,g,N) << '\n';
	}
	cout << "---"<< '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}