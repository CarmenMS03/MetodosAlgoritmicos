#include "Matriz.h"
#include "EntInf.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

using namespace std;

/*

EntInf resolver(int i, int j, vector<int> const& potencias, vector<int> const& costes, int const& Pmax, int const& Pmin, Matriz<EntInf>& C, Matriz<EntInf>& pot) {

    if (j > Pmax) return Infinito; //Casos base
    if (j >= Pmin) return 0;
    if (i >= potencias.size()) return Infinito;
    if (C[i][j] == Infinito) {

        //Casos recursivos
        if (j + potencias[i] > Pmax) {
            C[i][j] = resolver(i + 1, j, potencias, costes, Pmax, Pmin, C, pot);
            return  C[i][j];
        }

        else {
            EntInf sol1 = resolver(i + 1, j, potencias, costes, Pmax, Pmin, C, pot);
            EntInf sol2 = resolver(i, j + potencias[i], potencias, costes, Pmax, Pmin, C, pot) + costes[i];

            if (sol1 < sol2) {
                C[i][j] = sol1;
                if (i + 1 < pot.numfils()) pot[i][j] = pot[i + 1][j];
            }
            else if (sol2 < sol1) {
                C[i][j] = sol2;
                if (j + potencias[i] <= Pmax) pot[i][j] = pot[i][j + potencias[i]] + potencias[i];
            }
            else {
                C[i][j] = sol1;
                if (i + 1 < potencias.size() && j + potencias[i] <= Pmax) {
                    pot[i][j] = min(pot[i + 1][j], pot[i][j + potencias[i]] + potencias[i]);
                }
            }
            return  C[i][j];
        }
    }

    return C[i][j];
}

EntInf resolver(int N, vector<int> const& potencias, vector<int> const& costes, int const& Pmax, int const& Pmin, Matriz<EntInf>& C, int& sol) {
    //de abajo a arriba, de derecha a izquierda

    for (int i = N - 1; i >= 0; i--) {//de abajo a arriba
        for (int j = Pmax; j >= 0; j--) {//de derecha a izquierda
            if (j >= Pmin) C[i][j] = 0;

            else {
                if (j - potencias[i] <Pmin) {
                    C[i][j] = C[i + 1][j];
                }

                else {
                    C[i][j] = min(C[i - 1][j], C[i][j + potencias[i]] + costes[i]);
                }
            }
        }
    }

    return C[0][0];

}

void reconstruccion(int i, int j, vector<int> const& potencias, vector<int> const& costes, int const& Pmax, int const& Pmin, Matriz<EntInf> const& C, int& sol) {

    if (j >= Pmin || j > Pmax || i == potencias.size()) return;

    else if (j + potencias[i] > Pmax) {
        reconstruccion(i + 1, j, potencias, costes, Pmax, Pmin, C, sol);
    }
    else {
        if (C[i][j] == C[i + 1][j]) { //no se coge del tipo i
            reconstruccion(i + 1, j, potencias, costes, Pmax, Pmin, C, sol);
        }

        else { //se coge del tipo i
            sol += potencias[i];
            reconstruccion(i, j + potencias[i], potencias, costes, Pmax, Pmin, C, sol);
        }
    }

}


bool resuelveCaso() {

    int N, Pmax, Pmin;
    cin >> N >> Pmax >> Pmin;

    if (!cin) {
        return false;
    }

    vector<int> potencias, costes;
    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        potencias.push_back(a);
    }
    for (int i = 0; i < N; i++) {
        cin >> a;
        costes.push_back(a);
    }

    Matriz<EntInf> C(N + 1, Pmax + 1, Infinito);
    Matriz<EntInf> pot(N + 1, Pmax + 1, 0);

    EntInf num = resolver(0, 0, potencias, costes, Pmax, Pmin, C, pot);
    if (num == Infinito) cout << "IMPOSIBLE" << endl;
    else {

        EntInf sol = pot[0][0];
        cout << num << ' ' << sol << endl;
    }

    return true;
}*/

struct Datos {
    int N;         // Número de tipos de bombillas
    int PMax;      // Potencia máxima permitida
    int PMin;      // Potencia mínima requerida
    vector<int> pot;  // Potencia de cada tipo de bombilla
    vector<int> cst;  // Coste de cada tipo de bombilla
};

pair<EntInf, int> resolver(const Datos& d) {
    Matriz<EntInf> coste(d.N + 1, d.PMax + 1, Infinito);

    coste[0][0] = 0;

    for (int i = 1; i <= d.N; ++i) {
        int potBomb = d.pot[i - 1];    // Potencia de la bombilla i.
        int cstBomb = d.cst[i - 1];      // Coste de la bombilla i.
        for (int p = 0; p <= d.PMax; ++p) {
            coste[i][p] = coste[i - 1][p];
            if (p >= potBomb) {
                EntInf opcion = coste[i][p - potBomb] + EntInf(cstBomb);
                if (opcion < coste[i][p]) {
                    coste[i][p] = opcion;
                }
            }
        }
    }

    EntInf mejorCoste = Infinito;
    int mejorPotencia = -1;
    for (int p = d.PMin; p <= d.PMax; ++p) {
        if (coste[d.N][p] < mejorCoste) {
            mejorCoste = coste[d.N][p];
            mejorPotencia = p;
        }
    }

    // Se devuelve el par (coste mínimo, potencia alcanzada).
    return { mejorCoste, mejorPotencia };
}


bool resuelveCaso() {
    Datos d;
    cin >> d.N >> d.PMax >> d.PMin;
    if (!cin) return false;

    d.pot.resize(d.N);
    d.cst.resize(d.N);

    for (int i = 0; i < d.N; ++i) {
        cin >> d.pot[i];
    }
    for (int i = 0; i < d.N; ++i) {
        cin >> d.cst[i];
    }
    pair<EntInf, int> sol;
    sol = resolver(d);

    if (sol.first == Infinito) {
        cout << "IMPOSIBLE" << "\n";
    }
    else {
        cout << sol.first << " " << sol.second << "\n";
    }

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
