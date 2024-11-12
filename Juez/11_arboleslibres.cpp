#include "Grafo.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool esArbolLibre(const Grafo& g) {
    int V = g.V();
    vector<bool> visitados(V, false);
    queue<int> q;
    q.push(0);
    visitados[0] = true;
    int visit = 0;
    int aristas = 0;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        visitados[v] = true;
        visit++;

        for (int w : g.ady(v)) {
            aristas++;
            if (!visitados[w]) {
                visitados[w] = true;
                q.push(w);
            }
        }
    }

    aristas /= 2; //no dirigido

    return (visit == V && aristas == V - 1);
}

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;
    if (!cin) return false;

    Grafo g(V);

    for (int i = 0; i < A; i++) {
        int u, w;
        cin >> u >> w;
        g.ponArista(u, w);
    }

    if (esArbolLibre(g)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
