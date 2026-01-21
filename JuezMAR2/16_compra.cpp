#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include "Matriz.h"

using namespace std;

static const int MAX_PROD = 3;

struct Nodo {
    vector<int> supermercados_marcados; //numero de productos comprados en cada supermercado
    int k;
    int coste;
    int coste_estimado;
    bool operator<(Nodo const& otro) const {
        return otro.coste_estimado < coste_estimado;
    }
};

int cota_optimista(Matriz<int> const& m,Nodo const& X) {
    int estimacion = X.coste;
    int min_precio = INT_MAX;

    for (int i = X.k + 1; i < m.numcols(); i++) {
        for (int j = 0; j < m.numfils(); j++) {
            if (m[j][i] < min_precio) { 
                min_precio = m[j][i];
            }
        }
        estimacion += min_precio;
        min_precio = INT_MAX;
    }
    return estimacion;
}

int cota_pesimista(Matriz<int> const& m, Nodo const& X) {
    vector<int> productos = X.supermercados_marcados;
    int coste = X.coste;

    for (int i = X.k + 1; i < m.numcols(); i++) {
        int j = 0;
        while (j < m.numfils() && productos[j] >= 3) j++; 
        productos[j]++;
        coste += m[j][i];
    }

    return coste;
}

void compra_rp(Matriz<int> const& m, int& coste_mejor) {

    int M = m.numfils(); // supermercados
    int N = m.numcols(); // productos
    Nodo Y;
    Y.supermercados_marcados = vector<int>(M, 0);
    Y.k = -1;
    Y.coste= 0;
    Y.coste_estimado = cota_optimista(m, Y );
    priority_queue<Nodo> cola;
    cola.push(Y);
    coste_mejor = cota_pesimista(m,Y);

    while (!cola.empty() && cola.top().coste_estimado <= coste_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        for (int j = 0; j < M; j++) {
            if (X.supermercados_marcados[j]< MAX_PROD) {
                X.supermercados_marcados[j] ++;
                X.coste = Y.coste + m[j][X.k];
                X.coste_estimado = cota_optimista(m,X);

                if (X.coste_estimado <= coste_mejor) {
                    if (X.k == N - 1) {
                        coste_mejor = X.coste;
                    }
                    else {
                        cola.push(X);
                        coste_mejor = min(coste_mejor, cota_pesimista(m, X));
                    }
                }
                X.supermercados_marcados[j]--;
            }
        }
    }
}

void resuelveCaso() {
    int supermercados, productos;
    cin >> supermercados >> productos;

    Matriz<int> m(supermercados, productos);
    
    for (int i = 0; i < supermercados; i++) {
        for (int j = 0; j < productos; j++) {
            cin >> m[i][j];
        }
    }

    int coste_mejor;
    compra_rp(m, coste_mejor);
    if(coste_mejor ==INT_MAX)cout << "Sin solucion factible\n";
    else cout << coste_mejor << endl;

}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int N = 0;
    cin >> N;
    while (N > 0) {
        resuelveCaso();
        N--;
    }
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
