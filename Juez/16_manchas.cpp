#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

const int MAX = 1000;

int df[] = { 1,0,-1,0 }, dc[] = { 0,1,0,-1 };
bool visited[MAX][MAX];
char mapa[MAX][MAX];
int F, C;

bool ok(int i, int j) {
	return 0 <= i && i < F && 0 <= j && j < C;
}

int dfs(int i, int j) {
	int tam = 1; visited[i][j] = true;
	for (int k = 0; k < 4; ++k) {
		int ni = i + df[k], nj = j + dc[k];
		if (ok(ni, nj) && mapa[ni][nj] == '#' && !visited[ni][nj])
			tam += dfs(ni, nj);
	}
	return tam;
}

bool resuelveCaso() {
	cin >> F >> C;
	if (!cin) return false;
	char e = ' ';
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> e;
			mapa[i][j] = e;
			visited[i][j] = false;
		}	
	}

	int numero = 0, maximo = 0;
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			if (!visited[i][j] && mapa[i][j] == '#') {
				maximo = max(maximo, dfs(i, j));
				numero++;
			}
		}
	}
	cout << numero << ' ' << maximo << '\n';
	return true;
}
  
int main() {
	while (resuelveCaso());
	return 0;
}