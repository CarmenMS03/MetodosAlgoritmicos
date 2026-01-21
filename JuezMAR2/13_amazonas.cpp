#include "Matriz.h"
#include "EntInf.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {

    int N;
    cin >> N;

    if (!std::cin) {
        return false;
    }

    Matriz<EntInf> G(N, N, Infinito); //se crea la matriz que representa el grafo
    for (int i = 0; i < G.numfils(); i++) {
        G[i][i] = 0;
    }

    int a; 
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cin >> a;
            G[i][j] = a;
        }
    }

    Matriz<EntInf> C(N, N, Infinito);

    Floyd(G, C);

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << C[i][j];
            if (j < N - 1) cout << ' ';
        }
        cout << endl;
    }


    return true;
}

int main() {
    // Ajustes para leer de un fichero (útil si estás usando DOMJUDGE o un archivo de test).
    // Si no lo necesitas, puedes quitar esta parte con #ifndef.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Bucle para procesar todos los casos
    while (resuelveCaso())
        /* vacío */;

    // Restaurar configuraciones iniciales (si usas DOMJUDGE).
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE"); // En algunos entornos, para pausar la consola
#endif
    return 0;
}
