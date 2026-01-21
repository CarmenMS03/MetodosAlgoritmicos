#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


template <typename Valor>
class Dijkstra {
public:

	Dijkstra(GrafoValorado<Valor> const& g, int orig) : origen(orig),
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

private:
	const Valor INF = 1000000000;
	int origen;
	std::vector<Valor> dist;
	std::vector<Arista<Valor>> ult;
	IndexPQ<Valor> pq;
	void relajar(Arista<Valor> a) {
		int v = a.uno(), w = a.otro(v);
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();  ult[w] = a;
			pq.update(w, dist[w]);
		}
		if (dist[v] > dist[w] + a.valor()) {
			dist[v] = dist[w] + a.valor();  ult[v] = a;
			pq.update(v, dist[v]);
		}
	}
};