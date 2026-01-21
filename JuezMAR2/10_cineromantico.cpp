#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <climits>
#include <string>
#include <algorithm> 

using namespace std;

struct tPelicula {
    int hora;
    int fin;
    int dur;
};

bool operator <(tPelicula const& a, tPelicula const& b) {
    return a.hora < b.hora;
}


int resolver(int i, vector<tPelicula> & pelis , int const& N, vector<int>& C) {

    if (i == N) return 0;

    if (C[i] == -1) {
        int inicio = pelis[i].hora;

        int siguiente = i + 1;
        while (siguiente < N && pelis[siguiente].hora<inicio+pelis[i].dur+10) {
            siguiente++;
        }
        C[i] = max(resolver(i + 1, pelis, N, C), resolver(siguiente, pelis, N, C) + pelis[i].dur);
        
    }
    return C[i];
}

bool resuelveCaso() {

    int N;
    cin >> N;

    if (N==0) {
        return false;
    }

    vector<tPelicula> pelis(N);
    char puntos;
    int horas, minutos, duracion;

    for (int i = 0; i < N; i++) {
        cin >> horas >> puntos >> minutos >> duracion;
        int inicio = horas*60 + minutos;
        int fin =inicio+duracion+10; 

        pelis[i] = { inicio, fin,duracion };
    }

    sort(pelis.begin(), pelis.end());

    vector<int> C(N + 1, -1);

    int num = resolver(0, pelis,N, C);

    cout << num << endl;
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
