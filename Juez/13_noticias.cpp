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
		if (!visited[v]) tam += dfs(v, g, visited);
	}

	return tam;
}

class ConjuntosDisjuntos {
protected:
	int ncjtos; // número de conjuntos disjuntos
	mutable std::vector<int> p; // enlace al padre
	std::vector<int> tam; // tamaño de los árboles
public:
	// partición unitaria de N elementos
	ConjuntosDisjuntos(int N) : ncjtos(N), p(N), tam(N, 1) {
		for (int i = 0; i < N; ++i)
			p[i] = i;
	}
	void unir(int a, int b) {
		int i = buscar(a);
		int j = buscar(b);
		if (i == j) return;
		if (tam[i] >= tam[j]) { // i es la raíz del árbol más grande
			tam[i] += tam[j]; p[j] = i;
		}
		else {
			tam[j] += tam[i]; p[i] = j;
		}--ncjtos;
	}
	int buscar(int a) const {
		if (p.at(a) == a) // es una raíz
			return a;
		else
			return p[a] = buscar(p[a]);
	}
	bool unidos(int a, int b) const {
		return buscar(a) == buscar(b);
	}
	int cardinal(int a) const {
		return tam[buscar(a)];
	}
	int num_cjtos() const {
		return ncjtos;
	}
};

bool resuelve() {

	int N = 0, M = 0;
	cin >> N >> M;

	if (!cin) return false;

	ConjuntosDisjuntos conjs(N+1);

	int num, a, b;
	for (int i = 0; i < M; i++) {//leemos las componentes conexas
		cin >> num; 
		if (num > 0) {
			cin >> a; //id de la componente conexa
			for (int j = 1; j < num; j++) {
				cin >> b;
				conjs.unir(a, b);
			}
		}
	}

	for (int k = 1; k <= N; k++) {
		cout << conjs.cardinal(k) << ' ';
	}
	cout << '\n';
	/*
	Grafo g(N);

	for (int i = 0; i < M; i++) {//leemos las componentes conexas
		int num = 0;
		cin >> num; //numero de nodos en la componente
		if (num > 0) {
			int a = 0;
			cin >> a; //id de la componente conexa

			int b = 0;
			for (int j = 1; j < num; j++) {
				cin >> b;
				g.ponArista(a - 1, b - 1);//pone las aristas sabiendo que es un grafo no dirigido
			}
		}
	}

	vector<bool> visited;
	visited.assign(N, false);
	vector<int> sol;
	sol.assign(N, 1);//lo sabe él mismo

	int tam = 0;

	for (int k = 0; k < N; k++) {
		tam = dfs(k, g, visited); //nueva componente conexa a explorar
		cout<< tam<<' ';
		visited.assign(N, false);
	}
	
	cout << '\n';*/
	return true;
}

int main() {
	while (resuelve());

	return 0;
}