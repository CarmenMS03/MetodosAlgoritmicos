#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <algorithm>

/*
    puntuaciones (i,j): menor número de dardos usados para conseguir la puntuación T-j habiendo procesado los sectores de 1_i.

    1) RECURSIÓN:

        - CASOS BASE:
            puntuaciones (N+1, j) = +INF con 1<=j<=T
            puntuaciones (i, 0) = 0 con 1<=i<=N

        - CASOS RECURSIVOS:
                                    puntuaciones(i+1,j) si s[i]>j
            puntuaciones(i,j) =
                                    min(puntuaciones(i+1,j), puntuaciones(i,j-s[i])+1) si s[i]<=j 

    2) LLAMADA INCIAL: puntuaciones(1,T)

    3) RELLENADO DE LA MATRIZ: De izquierda a derecha para poder optimizar en espacio.

         0   j-s[i]  j          T
        ________________________
      0 |
        |
        |
    i   |      x -> x
        |           |  
   i +1 |           x   
        |
      N |


    4) RECONSTRUCCIÓN

        La reconstrucción dependerá de si se encuentra o no solución:
            -  Si en la poscición T hay un INF no hay solución
            - Si se encuentra un valor, la solución será la combinación de sectores que se ha ido recogiendo.

    5) COSTE

        -Tiempo: O (NxT)
        -Espacio: O (T)

    6) MEJORA EN ESPACIO

        - Como el valor (i,j) depende de (i+1,j) y de (i,j-s[i]) si se rellena una sola fila de izquierda a derecha y teniendo el valor previo de (i,j) que sería i+1,j este puede calcularse y 
        se machaca en la fila. Por esto, se pude reducir la matriz a una sola fila.

*/

using namespace std;

struct SolucionFinal {
    bool posible;
    int nDardos;
    vector<int> comb;
};


struct ComboSol {
    int nDardos;
    vector<int> comb;
};



SolucionFinal resolver(int T, int S, const vector<int>& sectores) {

    vector<ComboSol> puntuaciones(T + 1);
    puntuaciones[0].nDardos = 0;
    puntuaciones[0].comb = {};


    for (int v = 1; v <= T; ++v) {
        puntuaciones[v].nDardos = INT_MAX;
        puntuaciones[v].comb = {};
    }


    for (int v = 1; v <= T; ++v) {
        for (int s : sectores) {
            if (v - s >= 0 && puntuaciones[v - s].nDardos != INT_MAX) {
                int numDardos = puntuaciones[v - s].nDardos + 1;
                vector<int> candidatoComb = puntuaciones[v - s].comb;
                candidatoComb.push_back(s);
                sort(candidatoComb.begin(), candidatoComb.end(), greater<int>());

                if (numDardos < puntuaciones[v].nDardos) {
                    puntuaciones[v].nDardos = numDardos;
                    puntuaciones[v].comb = candidatoComb;
                }
                else if (numDardos == puntuaciones[v].nDardos) {
                    if (candidatoComb > puntuaciones[v].comb) {
                        puntuaciones[v].comb = candidatoComb;
                    }
                }
            }
        }
    }

    SolucionFinal sol;
    if (puntuaciones[T].nDardos == INT_MAX) {
        sol.posible = false;
    }
    else {
        sol.posible = true;
        sol.nDardos = puntuaciones[T].nDardos;
        sol.comb = puntuaciones[T].comb;
    }

    return sol;
}



bool resuelveCaso() {
    int T, S;
    std::cin >> T >> S;
    if (!cin) return false;

    std::vector<int> sectores(S);
    for (int i = 0; i < S; i++) {
        std::cin >> sectores[i];
    }

    SolucionFinal sol = resolver(T, S, sectores);

    if (!sol.posible) {
        std::cout << "Imposible\n";
    }
    else {
        cout << sol.nDardos << ":";
        for (int punt : sol.comb) {
            cout << " " << punt;
        }
        cout << "\n";
    }

    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {

    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);

#endif
    return 0;
}