#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "DigrafoValorado.h"
#include "GrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


template <typename Valor>
class Dijkstra {
public:

	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ult(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	
	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
	deque <Valor> camino(int v, int &npasos) const {
		deque <Valor> cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ult[v]; a.desde() != origen; a = ult[a.desde()]) {
			npasos++;
			cam.push_front(a.desde());
		}
		cam.push_front(a.desde());
		npasos++;
		return cam;
	}
	
private:
	const Valor INF = 1000000000;
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();  ult[w] = a;
			pq.update(w, dist[w]);
		}
	}
};


int bfs(int origen, int destino, GrafoValorado<int> const& g) {
	if (origen == destino) return 0;
	vector<int> distancia(g.V(), 0);
	vector<bool> visit(g.V(), false);
	distancia[origen] = 0; visit[origen] = true;
	queue<int> cola; cola.push(origen);
	while (!cola.empty()) {
		int v = cola.front(); cola.pop();
		for (Arista<int> ar: g.ady(v)){
			int w = ar.otro(v);
			if (!visit[w]) {
				distancia[w] = distancia[v] + 1;
				if (w == destino) return distancia[w];
				else cola.push(w);
			}
		}
	}
	return 0;
}


bool resuelve() {
	int N;
	cin >> N;

	if (!cin) return false;

	int C;
	cin >> C;

	GrafoValorado<int> g(N);
	DigrafoValorado<int> g1(N);

	int a, b, v;
	for (int i = 0; i < C; i++) {
		cin >> a >> b >> v;
		Arista<int> ar(a-1, b-1, v); //numerados de 1 a N
		g.ponArista(ar);
		AristaDirigida<int> ar1(a - 1, b - 1, v);
		AristaDirigida<int> ar2(b - 1, a - 1, v);
		g1.ponArista(ar1);
		g1.ponArista(ar2);
	}

	int K;
	cin >> K;
	int origen, destino;
	for (int i = 0; i < K; i++) {
		cin >> origen >> destino;
		origen--; destino--;//numerados de 1 a N

		Dijkstra<int> dj(g1, origen);
		if (!dj.hayCamino(destino)) cout << "SIN CAMINO\n";
		else {
			int pasos = 0;
			dj.camino(destino, pasos);
			if (pasos == bfs(origen, destino, g)) cout << dj.distancia(destino) <<' '<< "SI\n";
			else cout << dj.distancia(destino) <<' '<< "NO\n";
		}
	}

	cout << "---\n";
	return true;
}

int main() {
	while(resuelve());
	return 0;
}
