#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>

/*
* cofres (1_N)
* oxígeno (0_T)
* 
    max_oro (i,j): máxima cantidad de oro recogida habiendo procesado los cofres del i_N y con j oxígeno restante.

    1) RECURSIÓN:

        - CASOS BASE:
            
            max_oro (0, j) = 0 con 0<=j<=T (no quedan más cofres)
            max_oro (i, 0) = 0 con 1<=i<=N (no queda oxígeno)

        - CASOS RECURSIVOS:
                                    max_oro(i-1,j) si j<prof[i] + 2*prof[i] (no hay suficiente oxígeno para coger ese cofre)
            max_oro(i,j) =         
                                    max(max_oro(i-1,j), max_oro(i-1,j - (prof[i] + 2*prof[i])) + valor[i] ) + tablero[i][j] si j>=prof[i] + 2*prof[i]

    2) LLAMADA INCIAL: max_suma(N,T)

    3) RELLENADO DE LA MATRIZ:
        0       j - (prof[i] + 2*prof[i])             j                N
        _________________________________________________________________
      0 |
        |
        |
     i-1|                    x                        x
        |                      \_____________________ |
     i  |                                             x
        |
      N |

    4) RECONSTRUCCIÓN

        La reconstrucción recorre la matriz desde N,T (donde está la solución) comparando cada posición i,j con i-1,j en caso de que ambas tengan al mismo valor significa, según está construida la
        recursión, que el cofre en la posición i-1 no forma parte de la solución. Si ambos valores cambian, significará que el cofre i-1 forma parte de la sollución y a su valor se debe la variación
        entre ambas posiciones de la matriz.
       
    5) COSTE

        -Tiempo: O(NxT) 

        -Espacio: O(NxT)

    6) MEJORA EN ESPACIO

*/


using namespace std;


int resolver(int i, int j, vector<int> const& prof, vector<int> const& oro, int const& N, int const& T, Matriz<int>& C) {

    if (C[i][j] == -1) {
        if (i==0) return 0; //Casos base
        if (j==0) return 0;

        //Casos recursivos
        if (prof[i]+2*prof[i] > j) {//no se puede alcanzar
            C[i][j] = resolver(i - 1, j, prof, oro, N, T, C);
            return  C[i][j];
        }

        else {//se puede alcanzar
            C[i][j] = max(resolver(i - 1, j, prof, oro, N, T, C), resolver(i - 1, j-(prof[i] + 2 * prof[i]), prof, oro, N, T, C) + oro[i]);
            return  C[i][j];
        }
    }

    return C[i][j];
}


int reconstruccion(vector<int> const& prof, int const& N, int const& T, Matriz<int> const& C, vector<bool>& sol) {

    int count = 0;
    int i = N, j = T; 
   
    while (i > 0 && j > 0) {
        if (C[i][j] != C[i-1][j] && C[i][j]!=0) {
            sol[i-1] = true; 
            j = j -(prof[i] + 2 * prof[i]);
            count++;
        }
        --i;
    }

    return count;

}


bool resuelveCaso() {

    int T;
    cin >> T;

    if (!cin) {
        return false;
    }

    int N;
    cin >> N;

    vector<int> prof, oro;
    prof.push_back(0);
    oro.push_back(0);
    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        prof.push_back(a);
        cin >> a;
        oro.push_back(a);
    }

    Matriz<int> C(N + 1, T + 1, -1);

    int num = resolver(N, T, prof, oro, N, T, C);
    vector<bool> sol(N+1, false);
    int count = reconstruccion(prof, N, T, C, sol);

    cout << num << endl;
    cout << count << endl;
    if (count != 0) {
        for (int i = 0; i < N; i++) {
            if (sol[i]) cout << prof[i + 1] << ' ' << oro[i + 1] << endl;
        }
    }
    cout << "---" << endl;
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
