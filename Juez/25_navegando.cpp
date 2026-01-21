#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include "DigrafoValorado.h"
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
    queue<Valor> camino(int v) const {
        queue<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
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
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelve() {
	int N;
	cin >> N;
	
	if (N==0) return false;

	vector<int> carga(N);
	for (int i = 0; i < N; i++) {
		cin>>carga[i];
	}

	DigrafoValorado<int> g(N);
	int M;
	cin >> M;
	int a, b, v;
	for (int i = 0; i < M; i++) {
        cin >> a >> b >> v;
		AristaDirigida<int> ar(a-1, b-1, v+carga[b-1]);
		g.ponArista(ar);
	}

    Dijkstra<int>  dj(g, 0);

    int sol = dj.distancia(N - 1) + carga[0];

    if (dj.hayCamino(N - 1))cout << sol << '\n';
    else cout << "IMPOSIBLE\n";

    return true;
}


int main() {
	while (resuelve());
	return 0;
}