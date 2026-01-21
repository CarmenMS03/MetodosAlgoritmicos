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

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito)
                A[i][j] = i;
        }
    }
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

bool resuelveCaso() {

    int nodos, relaciones;
    std::cin >> nodos >> relaciones;

    if (!std::cin) {
        return false;
    }

    Matriz<EntInf> G(nodos, nodos,Infinito); //se crea la matriz que representa el grafo
    for (int i = 0; i < G.numfils(); i++) {
        G[i][i] = 0;
    }
    unordered_map<string, int> mapa;

    string n1, n2;
    int ind = 0;
    for (int i = 0; i < relaciones; i++) {
        cin >> n1 >> n2;
        if (mapa.count(n1) == 0) { // no está en el mapa
            mapa.insert({ n1,ind });
            ind++;
        }
        if (mapa.count(n2) == 0) { // no está en el mapa
            mapa.insert({ n2,ind });
            ind++;
        }

        G[mapa.at(n1)][mapa.at(n2)] = 1;
        G[mapa.at(n2)][mapa.at(n1)] = 1;
    }
    Matriz<EntInf> C(nodos, nodos, Infinito);
    Matriz<int> A;
    Floyd(G,C,A);

    EntInf grado = 0;
    bool conectada = true;
    for (int i = 0; i < C.numfils() && conectada; i++) {
        for (int j = 0; j < C.numcols() && conectada; j++) {
            if (C[i][j] == Infinito) {
                conectada = false;
                break;
            }
            grado = max(C[i][j], grado);
        }
    }

    if (conectada) cout << grado << endl;
    else cout << "DESCONECTADA" << endl;
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
