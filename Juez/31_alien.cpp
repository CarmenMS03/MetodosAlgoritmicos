#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

//hay que cubrir [C,F) con el menor número de tareas posible 

struct tarea {
	int inicio;
	int fin;
};


bool operator<(tarea const& a, tarea const& b) {
	return a.inicio < b.inicio;
}



bool resuelve() {

	int C, F, N;
	cin >> C >> F >> N;
	if (C == 0 && F == 0 && N == 0) return false;

	vector<tarea> tareas;

	int ini, fin;
	for (int i = 0; i < N; i++) {
		cin >> ini >> fin;
		tarea t{ ini,fin};

		tareas.push_back(t);
	}

	sort(tareas.begin(), tareas.end()); //se ordenan las tareas por inicio de menor a mayor

	int sol = 0;
	int cobertura = C;
	int i = 0;
	int mejorfin = 0;
	int escogida = 0;

	while (cobertura < F) { // iteramos hasta que se cubra todo el intervalo

		while (i < N && tareas[i].inicio <= cobertura) { //debemos cubrir todo el intervalo sin huecos (desde C)
			if (tareas[i].fin > mejorfin) { //escogemos la tarea que más avance
				mejorfin = tareas[i].fin;
				escogida = i;
			}
			i++;
		}

		if (mejorfin == cobertura) { // no se puede cubrir el intervalo porque no se ha encontrado ninguna tarea que avance más
			sol = -1;
			break;
		}

		cobertura = mejorfin; //esta cubierto hasta el fin de la tarea escogida que no deja huecos con las anteriores
		sol++;
		i = escogida + 1; //se sigue buscando desde la tarea escogida
	}

	if (sol == -1) cout << "Imposible\n";
	else cout << sol << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}