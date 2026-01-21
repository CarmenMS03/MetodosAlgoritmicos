#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;


int resolver(int i, int j, string const& cadena1, string const& cadena2, Matriz<int>& C) {
    
    if (C[i][j] == -1) {
        if (i >= cadena1.length() || j >= cadena2.length()) return 0;

        else if (cadena1[i] == cadena2[j]) {
            C[i][j] = resolver(i + 1, j + 1, cadena1, cadena2, C) + 1;
            return  C[i][j];
        }

        else {
            C[i][j] = max(resolver(i + 1, j, cadena1, cadena2, C), resolver(i, j + 1, cadena1, cadena2, C));
            return  C[i][j];
        }
    }
    return C[i][j];
}

void reconstruccion( int i, int j, string const& cadena1, string const& cadena2, Matriz<int> const& C, string& sol) {
    
    if (i >= cadena1.length() || j >= cadena2.length()) return;

    else if (cadena1[i] == cadena2[j]) {
        sol.push_back(cadena1[i]);
        reconstruccion(i + 1, j + 1, cadena1, cadena2, C, sol);
    }

    else {
        if (C[i][j] == C[i + 1][j]) {
            reconstruccion(i + 1, j, cadena1, cadena2, C, sol);
        }
        else {
            reconstruccion(i, j+1, cadena1, cadena2, C, sol);
        }
    }
}


bool resuelveCaso() {

    string cadena1, cadena2;
    std::cin >> cadena1 >> cadena2;

    if (!std::cin) {
        return false;
    }
    
    Matriz<int> C(cadena1.length()+1, cadena2.length()+1, -1);
    resolver(0, 0, cadena1, cadena2, C);
    string sol;
    reconstruccion(0, 0, cadena1, cadena2, C, sol);
    cout <<sol << endl;

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
