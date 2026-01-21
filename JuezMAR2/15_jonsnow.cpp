
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
    //vector<bool> carros_marcados;
    vector<bool> caminos_marcados;
    int k;
    int calidad;
    int calidad_estimado;
    bool operator<(Nodo const& otro) const {
        return otro.calidad_estimado > calidad_estimado;
    }
};

int calculo_estimacion(Matriz<int> const& m, vector<int> const& carros, vector<int> const& caminos, Nodo const& X) {
    int estimacion = X.calidad;
    int max = 0;
    for (int i = X.k + 1; i < m.numfils(); ++i) {
        for (int j = 0; j < m.numcols(); ++j) {
            if (max < m[i][j] && !X.caminos_marcados[j] && carros[i] <= caminos[j]) {
                max = m[i][j];
            }
        }
        estimacion += max;
        max = 0;
    }
    return estimacion;
}

void invernalia_rp(Matriz<int> const& m, vector<int> const& carros, vector<int> const& caminos, int& calidad_mejor) {

    int N = m.numfils();
    int M = m.numcols();
    Nodo Y;
    Y.caminos_marcados = vector<bool>(M, false);
    Y.k = -1;
    Y.calidad = 0;
    Y.calidad_estimado = calculo_estimacion(m, carros, caminos, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    calidad_mejor = 0;

    while (!cola.empty() && cola.top().calidad_estimado > calidad_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        for (int j = 0; j < M; j++) {
            if (!X.caminos_marcados[j] && carros[X.k] <= caminos[j]) {
                X.caminos_marcados[j] = true;
                X.calidad = Y.calidad + m[X.k][j];
                X.calidad_estimado = calculo_estimacion(m, carros, caminos, X);

                if (X.calidad_estimado > calidad_mejor) {
                    if (X.k == N - 1) {
                        calidad_mejor = X.calidad;
                    }
                    else cola.push(X);
                }

                X.caminos_marcados[j] = false;
            }
     
        }

        X.calidad = Y.calidad;
        X.calidad_estimado = calculo_estimacion(m, carros, caminos, X);
        if (X.calidad_estimado > calidad_mejor) {
            if (X.k == N - 1) {
                calidad_mejor = X.calidad;
            }
            else cola.push(X);
        }
    }
}

bool resuelveCaso() {
    int num_carros, num_caminos;
    cin >> num_carros >> num_caminos;

    vector<int> carros(num_carros), caminos(num_caminos);
    for (int i = 0; i < num_carros; i++) {
        cin >> carros[i];
    }
    for (int i = 0; i < num_caminos; i++) {
        cin >> caminos[i];
    }

    Matriz<int> m(num_carros, num_caminos);
    for (int i = 0; i < num_carros; i++) {
        for (int j = 0; j < num_caminos; j++) {
            cin >> m[i][j];
        }
    }

    int calidad_mejor = 0;
    invernalia_rp(m, carros, caminos, calidad_mejor);
    cout << calidad_mejor << endl;
    return true;

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
