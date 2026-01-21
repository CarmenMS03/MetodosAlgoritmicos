#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;

int resolver(vector<int> const& cortes, int const& L) {
    int n = cortes.size() - 1;
    Matriz<int> esfuerzo(n + 1, n + 1, 0);
    
    for (int d = 2; d <= n; ++d) { 
        for (int i = 0; i <= n-d; ++i) { 
            int j = i + d;
            esfuerzo[i][j] = INT_MAX;
            for (int k = i + 1; k < j; ++k) { 
                int cost = 2*(cortes[j] - cortes[i]) + esfuerzo[i][k] + esfuerzo[k][j];
                if (cost < esfuerzo[i][j]) {
                    esfuerzo[i][j] = cost;
                }
            }
        }
    }
    return esfuerzo[0][n];
}

bool resuelveCaso() {

    int L, N;
    cin >> L>>N;

    if (L==0 && N==0) {
        return false;
    }

    vector<int> cortes;
    int c;
    for (int i = 0; i < N; i++) {
        cin >> c;
        cortes.push_back(c);
    }

    cortes.insert(cortes.begin(), 0);
    cortes.push_back(L);
    int num = resolver(cortes,L);
    
    cout << num << endl;

    return true;
}

int main() {
    // Ajustes para leer de un fichero (util si estas usando DOMJUDGE o un archivo de test).
    // Si no lo necesitas, puedes quitar esta parte con #ifndef.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Bucle para procesar todos los casos
    while (resuelveCaso())
        /* vacio */;

    // Restaurar configuraciones iniciales (si usas DOMJUDGE).
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE"); // En algunos entornos, para pausar la consola
#endif
    return 0;
}
