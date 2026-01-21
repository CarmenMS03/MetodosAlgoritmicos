#include "Matriz.h"
#include "EntInf.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

/*
    max_suma (i,j): máxima suma acumulada en la fila i habiendo recorrido i_N y la columna j.

    1) RECURSIÓN:

        - CASOS BASE:

            max_suma (0, j) = 0 (está en la última fila)

        - CASOS RECURSIVOS:
                                    max(max_suma(i-1,j), max_suma(i-1,j-1)) + tablero[i][j] si j==N (ultima columna)
            max_suma(i,j) =         max(max_suma(i-1,j), max_suma(i-1,j+1)) + tablero[i][j] si j==1 (primera columna)
                                    max(max_suma(i-1,j), max_suma(i-1,j-1),  max_suma(i-1,j+1)) + tablero[i][j] si 1<j<N 

    2) LLAMADA INCIAL: max_suma(N,1)

    3) RELLENADO DE LA MATRIZ:
        0       j-1  j  j+1         N
        ______________________________
      0 |
        |
        |
    i-1 |         x  x  x
        |          \ | /
     i  |            x   
        |
      N |

    4) RECONSTRUCCIÓN

        Siempre hay solución y estará en max_suma[N - 1] en alguna de las columnas.
        La reconstruccióny búsqueda de la solución consiste en recorrer esa última fila de la matriz buscando el mayor valor almacenado, que será la posición y la columna en la que esté nos da la reconstrucción.

    5) COSTE

        -Tiempo: O(NxN) = O(N^2)

        -Espacio: O(NxN) = O(N^2)

    6) MEJORA EN ESPACIO

*/


using namespace std;


pair<EntInf,int> resolver(int N, Matriz<EntInf>& tablero) {
    
    Matriz<EntInf> max_suma(N+1,N+1,0);

    for (int j = 0; j < N; ++j) {
        max_suma[0][j] = tablero[0][j];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            EntInf max_prev = max_suma[i - 1][j];
            if (j > 0) {
                max_prev = max(max_prev, max_suma[i - 1][j - 1]);
            }
            if (j < N - 1) {
                max_prev = max(max_prev, max_suma[i - 1][j + 1]);
            }

            max_suma[i][j] = tablero[i][j] + max_prev;
        }
    }

    EntInf max_sum = max_suma[N - 1][0];
    int col = 0;
    for (int j = 1; j < N; ++j) {
        if (max_suma[N - 1][j] > max_sum) {
            max_sum = max_suma[N - 1][j];
            col = j;
        }
    }

    return { max_sum, col + 1 };

}

bool resuelveCaso() {

    int N;
    cin >> N;

    if (!cin) {
        return false;
    }

    Matriz<EntInf> tablero(N +1 ,N+1,-1);
    int a;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a;
            tablero[i][j] = a;
        }
    }
   
    pair<EntInf, int> sol;
    sol = resolver(N, tablero);


    cout << sol.first<<' '<<sol.second << endl;
    

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
