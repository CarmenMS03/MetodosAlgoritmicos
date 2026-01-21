#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;


int resolver(int i, int j, vector<int> const& cubos, Matriz<int>& C) {

    if (i   == j ) return cubos[i];
    if (i > j) return 0;
    
    if (C[i][j] == -1) {
        int aux1, aux2;

        if (cubos[i + 1] > cubos[j]) aux1 = resolver(i + 2, j, cubos, C) + cubos[i];
        else  aux1 = resolver(i + 1, j-1, cubos, C) + cubos[i];

        if (cubos[j - 1] > cubos[i]) aux2 = resolver(i, j-2, cubos, C)+cubos[j];
        else aux2 = resolver(i+1, j-1, cubos, C)+cubos[j];
        
        C[i][j] = max(aux1, aux2);
    }
    return C[i][j];
}


bool resuelveCaso() {

    int N; 
    cin >> N;

    if (N==0) {
        return false;
    }

    vector<int> cubos;
    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        cubos.push_back(a);
    }

    Matriz<int> C(N + 1, N + 1, -1);
    int sol = resolver(0, N-1, cubos, C);
    
    cout << sol << endl;

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
