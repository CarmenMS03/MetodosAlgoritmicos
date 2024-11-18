#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "GrafoValorado.h"
#include "PriorityQueue.h"

using namespace std;

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

template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
	ConjuntosDisjuntos cjtos;
public:
	Valor costeARM() const {
		return coste;
	}
	std::vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}
	int num_cjtos() const {
		return cjtos.num_cjtos();
	}
	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), cjtos(g.V()) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}
};

//La solución consiste en calcular el ARM usando el algoritmo de Kruskal previamente comprobando si es conexo el grafo y puede obtenerse
//el arbol de recubrimiento. Esta comprobación se hace con conjuntos disjuntos que ya se usan internamente en Kruskal viendo si el número 
// de ellos después de incluir todas las aristas es 1(conexo) o más de 1 (no es posible obtener el ARM). 

bool resuelve() {
	int I;
	cin >> I;
	if (!cin) return false;

	GrafoValorado<int> g(I);

	int P;
	cin >> P;

	int a, b, v;
	for (int i = 0; i < P; i++) {
		cin >> a >> b >> v;
		Arista<int> ar(a - 1, b - 1, v);//en la entrada se enumera de 1 a V pero en el grafo van desde el 0
		g.ponArista(ar);
	}

	ARM_Kruskal<int> arm(g);
	if(arm.num_cjtos() > 1) cout << "No hay puentes suficientes\n"; // el grafo no es conexo y no habrá ARM
	else {//el grafo es conexo buscaos el ARM
		cout << arm.costeARM() << '\n';
	}

	return true;
}


int main() {
	while (resuelve());
	return 0;
}