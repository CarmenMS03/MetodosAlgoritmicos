#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;


int dfs(int origen, const Grafo& g, vector<bool>& visited) {
	int tam = 1; 
	visited[origen] = true;
	for (int v : g.ady(origen)) {
		if (!visited[v]) tam += dfs(v,g,visited);
	}

	return tam;
}

void resuelve() {
	
	int N = 0, M = 0;
	cin >> N >> M;
	Grafo g(N);

	int a = 0, b = 0;

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g.ponArista(a-1, b-1); //pone las aristas sabiendo que es un grafo no dirigido
	}

	vector<bool> visited;
	visited.assign(N, false);

	int tam = 0, maxtam = 0;
	for (int j = 0; j < N; j++) {
		if (!visited[j]) tam=dfs(j,g, visited);
		maxtam = max(tam, maxtam);
	}

	cout << maxtam << '\n';

}

int main() {
	int casos = 0;
	cin >> casos;
	while (casos > 0) {
		resuelve();
		casos--;
	}

	return 0;
}