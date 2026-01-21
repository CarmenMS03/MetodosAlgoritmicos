
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <sstream>
#include "Matriz.h"
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

struct Nodo {
    vector<bool> sol;
    int k;
    int tiempo; 
    int tiempo_estimado; 
    bool operator<(Nodo const& otro) const {
        return otro.tiempo_estimado < tiempo_estimado;
    }
};

int calculo_estimacion(Matriz<int> const& m, Nodo const& X) {
    int estimacion = X.tiempo;
    int min = INT_MAX;
    for (int i = X.k + 1; i < m.numfils(); ++i) {
        for (int j = 0; j < m.numcols(); ++j) {
            if (min>m[i][j] && !X.sol[j]) {
                min = m[i][j];
            }
        }
        estimacion += min;
        min = INT_MAX;
    }
    return estimacion;
}

void funcionarios_rp(Matriz<int> const& m, vector<bool>& sol_mejor, int& tiempo_mejor) {

    size_t N = m.numfils();
    Nodo Y;
    Y.sol = vector<bool>(N, false);
    Y.k = -1;
    Y.tiempo = 0;
    Y.tiempo_estimado = calculo_estimacion(m, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    tiempo_mejor = INT_MAX;
    
    while (!cola.empty() && cola.top().tiempo_estimado < tiempo_mejor) {
        Nodo Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        
        for (int j = 0; j < N ; j++) {
            if (!X.sol[j]) {
                X.sol[j] = true;
                X.tiempo = Y.tiempo + m[X.k][j];
                X.tiempo_estimado = calculo_estimacion(m, X);
                if (X.tiempo_estimado < tiempo_mejor) {
                    if (X.k == N - 1) {
                        sol_mejor = X.sol;
                        tiempo_mejor = X.tiempo;
                    }
                    else cola.push(X);
                }
                X.sol[j] = false;

            }
        }
        
    }
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false;
    Matriz<int> m(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> m[i][j];
        }
    }
    vector<bool> sol_mejor(m.numfils(),false);
    int tiempo_mejor = INT_MAX;
    funcionarios_rp(m, sol_mejor, tiempo_mejor);
    cout << tiempo_mejor << endl;
    return true;
    
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
