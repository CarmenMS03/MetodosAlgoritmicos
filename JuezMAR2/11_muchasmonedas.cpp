#include "Matriz.h"
#include "EntInf.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>
#include <algorithm> 

using namespace std;

bool operator <(pair<int,int> const& a, pair<int, int> const& b) {
    return a.first < b.first;
}

EntInf resolver(int i, int j, vector<pair<int, int>> const& monedas, int const& N, int const& P, Matriz<EntInf>& C) {

    C[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        C[i][0] = 0;
        for (int j = 1; j <= P; j++) {
            C[i][j] = C[i - 1][j];
            
            EntInf min = C[i][j];
            for (int k = 1; k <= monedas[i - 1].second && k * monedas[i - 1].first <= j; k++) {
                EntInf caso = C[i -1][j - (k * monedas[i - 1].first)] + k;
                if (min > caso) {
                    min = caso;
                    C[i][j] = caso;
                }
            }
            
            
        }
    }

    return C[N][P];
}

bool resuelveCaso() {

    int N;
    cin >> N;

    if (!cin) {
        return false;
    }

    vector<pair<int,int>> monedas(N);
    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        monedas[i].first = a;
    }
    for (int i = 0; i < N; i++) {
        cin >> a;
        monedas[i].second = a;
    }

    sort(monedas.begin(), monedas.end(),greater<pair<int,int>>());

    int P;
    cin >> P;

    Matriz<EntInf> C(N + 1, P + 1, Infinito);

    EntInf num = resolver(N, P, monedas, N, P, C);

    if (num != Infinito) {
        cout << "SI " << num << endl;
    }
    else cout << "NO"<< endl;
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
