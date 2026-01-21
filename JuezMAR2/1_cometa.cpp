
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>

using namespace std;

struct Cordel {
    int longitud;
    int coste;
};

struct Datos {
    int N;
    int L;
    vector<Cordel> cordeles;
};


struct Solucion {
    bool posible;
    long long numFormas;     
    long long minCordeles;   
    long long minCoste;      // Mínimo coste
};


Solucion resolver(const Datos& datos) {
    Solucion sol;
    sol.posible = false;
    sol.numFormas = 0;
    sol.minCordeles = 0;
    sol.minCoste = 0;

    int N = datos.N;
    int L = datos.L;



    vector<long long> maneras(L+1, 0);
    vector<long long> minCordeles(L+1, INT_MAX);
    vector<long long> minCoste(L+1, INT_MAX);

    maneras[0] = 1;      
    minCordeles[0] = 0;  
    minCoste[0] = 0;    
    
    for(int i = 0; i < N; i++) {
        int longitud = datos.cordeles[i].longitud;
        int coste = datos.cordeles[i].coste;

        for(int j = L; j >= longitud; j--) {

            if(maneras[j - longitud] > 0) {
                maneras[j] += maneras[j - longitud];
            }

            if(minCordeles[j - longitud] != INT_MAX) {
                long long opcion = minCordeles[j - longitud] + 1;
                if(opcion < minCordeles[j]) {
                    minCordeles[j] = opcion;
                }
            }

            if(minCoste[j - longitud] != INT_MAX) {
                long long opcion = minCoste[j - longitud] + coste;
                if(opcion < minCoste[j]) {
                    minCoste[j] = opcion;
                }
            }
        }
    }

    if(maneras[L] > 0) {
        sol.posible = true;
        sol.numFormas = maneras[L];
        sol.minCordeles = minCordeles[L];
        sol.minCoste = minCoste[L];
    }
    else {
        sol.posible = false;
    }

    return sol;
}


bool resuelveCaso() {

    int N, L;
    std::cin >> N >> L;
    
    if (!std::cin) {
        return false;
    }

    Datos datos;
    datos.N = N;
    datos.L = L;
    datos.cordeles.resize(N);

    for(int i = 0; i < N; ++i) {
        int len, cost;
        std::cin >> len >> cost;
        datos.cordeles[i] = { len, cost };
    }

    Solucion sol = resolver(datos);

    if (!sol.posible) {
        std::cout << "NO\n";
    }
    else {
        std::cout << "SI " 
                  << sol.numFormas << " "
                  << sol.minCordeles << " "
                  << sol.minCoste
                  << "\n";
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
