#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Nodo {
    int k; //cancion que se procesa
    double tiempoA; //tiempo libre en cada cara
    double tiempoB;
    double puntuacion; //solucion parcial
    double puntuacion_estimado; //estimacion
    bool operator<(Nodo const& otro) const {
        return otro.puntuacion_estimado > puntuacion_estimado;  //maximizar
    }
};

struct tCancion {
    double dur;
    double punt;
    bool operator<(tCancion const& otro) const {
        return (punt / dur) > (otro.punt / otro.dur);
    }
};

//se hace una voraz fracionaria (por esto el double como tipo)

double cota_optimista(vector<tCancion> const& canciones, Nodo const& X) {
    double estimacion = X.puntuacion;
    double tiempo = X.tiempoA + X.tiempoB;

    int i = X.k + 1;

    while (i < canciones.size() && canciones[i].dur <= tiempo) {
        estimacion += canciones[i].punt;
        tiempo -= canciones[i].dur;
        i++;
    }

    if (i < canciones.size()) estimacion += (tiempo / canciones[i].dur) * canciones[i].punt; // Parte fraccionaria

    return estimacion;
}

/*
int cota_pesimista(vector<pair<int, int>> const& canciones, Nodo const& X) {
    int puntuacion = X.puntuacion;
    
    int tiempo = X.tiempoA;
    
    int i = X.k + 1;
    while (i < canciones.size() && tiempo >= canciones[i].second) {
        puntuacion += canciones[i].first;
        tiempo -= canciones[i].second;
        i++;
    }

    tiempo = X.tiempoB;

    while (i < canciones.size() && tiempo >= canciones[i].second) {
        puntuacion += canciones[i].first;
        tiempo -= canciones[i].second;
        i++;
    }

    return puntuacion;
}*/

void pepe_rp(vector<tCancion> const& canciones, double const& cinta, double& puntuacion_mejor) {

    int N = canciones.size();// canciones
    Nodo Y;
    Y.tiempoA = Y.tiempoB = cinta;
    Y.k = -1; //canion a procesar
    Y.puntuacion = 0;
    Y.puntuacion_estimado = cota_optimista(canciones, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    puntuacion_mejor = 0;

    while (!cola.empty() && cola.top().puntuacion_estimado > puntuacion_mejor) { //estrictos pq no se usa opt-pes
       
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        //rama de poner k en cara A
        if (X.tiempoA >= canciones[X.k].dur) {
            X.tiempoA -= canciones[X.k].dur;
            X.puntuacion = Y.puntuacion + canciones[X.k].punt;
            X.puntuacion_estimado = cota_optimista(canciones, X);

            if (X.puntuacion_estimado > puntuacion_mejor) {
                if (X.k == N - 1) {
                    puntuacion_mejor = X.puntuacion;
                }
                else cola.push(X);
                
            }
            X.tiempoA += canciones[X.k].dur;
        }

        //rama de poner k en cara B
        if (X.tiempoA != X.tiempoB && X.tiempoB >= canciones[X.k].dur) { //tiempo distinto en ambas caras para evitar soluciones simétricas
            X.tiempoB -= canciones[X.k].dur;
            X.puntuacion = Y.puntuacion + canciones[X.k].punt;
            X.puntuacion_estimado = cota_optimista(canciones, X);

            if (X.puntuacion_estimado > puntuacion_mejor) {
                if (X.k == N - 1) {
                    puntuacion_mejor = X.puntuacion;
                }
                else cola.push(X);
                
            }
            X.tiempoB += canciones[X.k].dur;
        }

        //rama de no poner la cancion k
        X.puntuacion = Y.puntuacion;
        X.puntuacion_estimado = cota_optimista(canciones, X);

        if (X.puntuacion_estimado > puntuacion_mejor) {
            if (X.k == N - 1) {
                puntuacion_mejor = X.puntuacion;
            }
            else cola.push(X);
            
        } 
    }
}


bool resuelveCaso() {
    int numcanciones;
    cin >> numcanciones;

    if (numcanciones == 0) return false;

    double cinta;
    cin >> cinta;
    
    vector<tCancion> canciones(numcanciones); //puntuacion,duracion

    for (int i = 0; i < numcanciones; i++) {
        cin >> canciones[i].dur; //duracion
        cin >> canciones[i].punt; //puntuacion
    }

    sort(canciones.begin(), canciones.end());

    double puntuacion_mejor;
    pepe_rp(canciones, cinta, puntuacion_mejor);
    cout << puntuacion_mejor << endl;
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
