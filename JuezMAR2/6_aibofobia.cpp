#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;


int resolver(int i, int j, string const& cadena, Matriz<int>& C) {

    if (C[i][j] == INT_MAX) {
        if (i >=j) return 0; //Casoos base

        //Casos recursivos
        else if (cadena[i] == cadena[j]) {
            C[i][j] = resolver(i + 1, j -1, cadena, C);
            return  C[i][j];
        }

        else {
            C[i][j] = min(resolver(i + 1, j, cadena, C), resolver(i, j - 1, cadena, C)) + 1 ;
            return  C[i][j];
        }
    }
    return C[i][j];
}

void reconstruccion(int i, int j, string const& cadena, Matriz<int> const& C, string& sol) {

    if (i > j) return;
    if (i == j) {
        sol.push_back(cadena[i]);
        return;
    }
    else if (cadena[i] == cadena[j]) {
        sol.push_back(cadena[i]);
        reconstruccion(i + 1, j - 1, cadena, C, sol);
        sol.push_back(cadena[i]);
        
    }

    else {
        if (C[i][j] == C[i + 1][j] + 1) {
            sol.push_back(cadena[i]);
            reconstruccion(i + 1, j, cadena, C, sol);
            sol.push_back(cadena[i]);
            
        }
        else {
            sol.push_back(cadena[j]);
            reconstruccion(i, j - 1, cadena, C, sol);
            sol.push_back(cadena[j]);
            
        }
    }
}


bool resuelveCaso() {

    string cadena;
    std::cin >> cadena;

    if (!std::cin) {
        return false;
    }

    Matriz<int> C(cadena.length(), cadena.length(), INT_MAX);
    int num = resolver(0, cadena.length() - 1, cadena, C);
    string sol;
    reconstruccion(0, cadena.length() - 1, cadena, C, sol);
    cout << num <<' '<<sol<< endl;

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
