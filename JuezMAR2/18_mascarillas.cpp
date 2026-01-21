#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Nodo {
    int k;
    vector<int> facultades_marcadas;
    int mascarillas_restantes; //mascarillas que faltan por ser cubiertas
    int coste;
    int coste_estimado;
    bool operator<(Nodo const& otro) const {
        return otro.coste_estimado < coste_estimado;
    }
};

int calculo_estimacion(vector<pair<int,int>> const& suministradores,Nodo const& X) {

    int coste = X.coste;
    int restantes = X.mascarillas_restantes;

    int i = X.k + 1;
    while (i < suministradores.size() && restantes>0) {
        int cantidad = min(restantes, suministradores[i].first);
        restantes -= cantidad;
        coste += cantidad*suministradores[i].second;
        i++;
    }

    return coste;
}

void mascarillas_rp(vector<int> const& facultades, vector<pair<int, int>> const& suministradores, vector<int> const& mascarillasrapidas,int const& mfacultades, int& coste_mejor) {

    int N = suministradores.size();// suministradores
    int M = facultades.size(); //facultades
    Nodo Y;
    Y.facultades_marcadas = facultades;
    Y.k = -1;//llevo los suministradores
    Y.mascarillas_restantes = mfacultades;
    Y.coste = 0;
    Y.coste_estimado = calculo_estimacion(suministradores,Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    coste_mejor = INT_MAX;

    while (!cola.empty() && cola.top().coste_estimado < coste_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        for (int j = 0; j < M; j++) {
            
            int cantidad = min(suministradores[X.k].first, X.facultades_marcadas[j]); //para que no quede negativo
            X.facultades_marcadas[j] -= cantidad;
            X.mascarillas_restantes -= cantidad;
            X.coste = Y.coste + (cantidad * suministradores[X.k].second);
            X.coste_estimado = calculo_estimacion(suministradores,X);

            if (X.coste_estimado < coste_mejor) {
                if (X.k == N - 1 && X.mascarillas_restantes==0) { //solo es solucion si se ha cubierto todan las mascarillas
                    coste_mejor = X.coste;
                }
                else if(X.k < N - 1 && mascarillasrapidas[X.k]>=X.mascarillas_restantes) cola.push(X);
            }

            X.facultades_marcadas[j] += cantidad;
            X.mascarillas_restantes += cantidad;
            

        }

        X.coste = Y.coste;
        X.coste_estimado = calculo_estimacion(suministradores,X);
        if (X.coste_estimado < coste_mejor) {
            if (X.k == N - 1 && X.mascarillas_restantes == 0) {
                coste_mejor = X.coste;
            }
            else if (X.k < N - 1 && mascarillasrapidas[X.k] >= X.mascarillas_restantes) cola.push(X);
        }
    }
}


void resuelveCaso() {

    int N, M; //facultades, suministradores
    cin >> N>>M;

    vector<int> facultades(N,0);
    vector<pair<int,int>> suministradores(M, {0,0}); //cantidad, precio

    int mfacultades = 0, msum =0; //numero total de mascarillas que requieren las facultades y que tienen los suministradores

    for (int i = 0; i < N; i++) {
        cin >> facultades[i];
        mfacultades += facultades[i];
    }

    for (int i = 0; i < M; i++) {
        cin >> suministradores[i].first;
        msum += suministradores[i].first;
    }

    for (int i = 0; i < M; i++) {
        cin >> suministradores[i].second;
    }

    if (msum >= mfacultades) {

        vector<int> mascarillasrapidas(M, 0);
        mascarillasrapidas[0] = msum - suministradores[0].first;
        for (int i = 1; i < M; i++) {
            mascarillasrapidas[i] = mascarillasrapidas[i - 1] - suministradores[i].first;
        }

        int coste_mejor;
        mascarillas_rp(facultades, suministradores,mascarillasrapidas, mfacultades, coste_mejor);
        if (coste_mejor !=INT_MAX) cout << coste_mejor << endl;
        else cout << "NO\n";
    }
    else cout << "NO\n";
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int N;
    cin >> N;
    while (N>0) {
        resuelveCaso();
        N--;
    }
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
