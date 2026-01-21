#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include "Matriz.h"

using namespace std;

struct Nodo {
    int k; //persona que estoy sentando
    vector<int> solparcial; //solucion parcial construida: indexado por persona en que asiento esta
    vector<bool> asientos_usados; //asioentos ya usados en la solucion construida
    int asientoslibres;
    int parejas; //parejas conseguidas
    int parejas_estimado;
    bool operator<(Nodo const& otro) const {
        return otro.parejas_estimado > parejas_estimado; //maximizar
    }
};

int calculo_estimacion(Nodo const& X, Matriz<bool> const& relaciones) {

    int parejas = X.parejas;

    for (int i = X.k + 1; i < relaciones.numfils(); i++) {
        for (int j = 0; j < i; j++) {
            if (relaciones[j][i]) parejas++;
        }
    }

    return parejas;
}

void restaurante_rp(Matriz<float> const& distancias, Matriz<bool> const&relaciones, int& parejas_mejor) {

    int N = distancias.numcols();//asientos
    int M = relaciones.numcols();//comensales
    Nodo Y;
    Y.asientos_usados = vector<bool>(N, false); //ninguno usado
    Y.k = -1;//llevo las personas
    Y.solparcial = vector<int>(M, -1);
    Y.parejas = 0;
    Y.asientoslibres = N;
    Y.parejas_estimado = calculo_estimacion(Y, relaciones);
    priority_queue<Nodo> cola;
    cola.push(Y);
    parejas_mejor = 0;

    while (!cola.empty() && cola.top().parejas_estimado > parejas_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        for (int j = 0; j < N; j++) { //j es el asiento

            if (!X.asientos_usados[j]) { //si el asiento esta libre

                int p = 0;
                for (int i = 0; i < X.k; i++) { //persona

                    if (relaciones[X.k][i]) { //allegados entre la persona que quiero sentar y la ya sentada
                        if (distancias[X.solparcial[i]][j] < 2.0) p++; //distancia entre el asiento en el que esta i y el asiento escogido actual j
                    }
                    else {// no allegados entre la persona que quiero sentar y la ya sentada
                        if (distancias[X.solparcial[i]][j] < 2.0) { //distancia entre el asiento en el que esta i y el asiento escogido actual j
                            p = -1;
                            break;
                        }
                    }
                    
                }

                if (p != -1) {
                    X.asientos_usados[j] = true;
                    X.asientoslibres--;
                    X.solparcial[X.k] = j; //persona k en asiento j
                    X.parejas = Y.parejas + p;
                    X.parejas_estimado = calculo_estimacion(X, relaciones);

                    if (X.parejas_estimado > parejas_mejor) {
                        if (X.k == M - 1) { //todo el mundo sentado
                            parejas_mejor = X.parejas;
                        }
                        else if(X.asientoslibres >=M-X.k-1) cola.push(X);
                    }
                }

                X.asientos_usados[j] = false;
                X.asientoslibres++;
            }
        }
    }
}


void resuelveCaso() {

    int N, M; //plazas, comensales
    cin >> N >> M;

    Matriz<float> distancias(N, N, 0);
    Matriz<bool> relaciones(M, M, false);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> distancias[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int a;
            cin >> a;
            relaciones[i][j] = (bool)a;
        }
    }
    
    int parejas_mejor; //maximizar
    restaurante_rp(distancias,relaciones, parejas_mejor);

    if (parejas_mejor != 0) cout << "PAREJAS "<< parejas_mejor << endl;
    else cout << "CANCELA\n";
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int N;
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
