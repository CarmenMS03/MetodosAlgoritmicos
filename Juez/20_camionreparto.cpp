#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "GrafoValorado.h"

using namespace std;

bool dfs(GrafoValorado<int> const& g, int v, int fin, int ancho, vector<bool>& visitado) {
    if (v == fin) return true;
    visitado[v] = true;
    bool sol = false; //contendra la solucion final de si hay camino o no para ese ancho

    for (Arista<int> w : g.ady(v)) { //sacamos las aristas de v
        if (!visitado[w.otro(v)] && w.valor() >= ancho) { //se hace recursión si no se ha visitado el vértice y si la arista permite el paso del camión.
            sol = dfs(g, w.otro(v), fin, ancho, visitado);
        }
        if (sol) return sol; //cuando se llega al destino se para
    }
    return sol;
}



//La solución consiste en recorrer el grafo no dirigido y valorado en profundidad viendo si hay algún camino posible para el ancho dado

bool resuelve() {
    int V;
    cin >> V;
    if (!cin) return false;
    int E;
    cin >> E;
    GrafoValorado<int> g(V);

    int a, b, v;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> v;
        Arista<int> ar(a-1, b-1, v);//en la entrada se enumera de 1 a V pero en el grafo van desde el 0
        g.ponArista(ar);
    }


    int K; 
    cin >> K;
    
    int ini, fin, ancho;

    for (int i = 0; i < K; i++) {
        cin >> ini >> fin >> ancho;
        vector<bool> visitado(g.V(), false);
        bool res = dfs(g, ini - 1, fin - 1, ancho, visitado);//en la entrada se enumera de 1 a V pero en el grafo van desde el 0
        if (res) cout << "SI\n";
        else cout << "NO\n";
    }

    return true;
}

int main() {
    while (resuelve());
    return 0;
}