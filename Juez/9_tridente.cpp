#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <fstream>
#include "IndexPQ.h"
#include <unordered_map>

using namespace std;


typedef struct tema {
	string titulo = " ";
	int citas = 0;
	int vez = 0;
};

bool operator<(tema const& a, tema const& b) {
	return a.citas > b.citas || (a.citas == b.citas && b.vez<a.vez);
}
bool operator >(tema const& a, tema const& b) {
	return b > a;
}

/*
COSTES
función insert del mapa hash: promedio O(1), peor O(size())
función count del mapa hash: promedio O(1), peor O(size())
función at del mapa hash: promedio O(1), peor O(size())

*/

bool resuelveCaso() {

	
	int eventos = 0;
	cin >> eventos;

	if (!cin) return false;

	IndexPQ<tema> cola(eventos + 1);
	unordered_map < string, pair<int, tema> > mapa_indices; //guarda el índice asociado en la cola y su prioridad


	int ind = 1;

	for (int i = 0; i < eventos; i++) {

		string op;
		cin >> op;

		string nombre;
		if (op == "C") {

			cin >> nombre; //titulo del tema
			int n, v;
			cin >> n; //numero de citas a sumar

			if (mapa_indices.count(nombre) == 0) { //primera vez que sale el tema
				tema t;
				t.titulo = nombre;
				t.citas = n;
				t.vez = i;
				mapa_indices.insert({ t.titulo,{ind,t} });//asociamos al tema nuevo un indice y su prioridad
				cola.push(ind, t);
				ind++;
			}

			else {//ya ha salido el tema, incrementa el número de citas
				pair<int, tema> incr = mapa_indices.at(nombre);
				incr.second.citas += n;
				incr.second.vez = i;

				mapa_indices[nombre] = {incr.first,incr.second};//asociamos al tema con su indice de siempre y la prioridad con las citas incrementadas
				cola.update(incr.first, incr.second);
			}
			
		}

		else if (op == "E") {
			cin >> nombre; //titulo del tema
			int n;
			cin >> n; //numero de citas a restar

			pair<int, tema> incr = mapa_indices.at(nombre);
			incr.second.citas -= n;

			mapa_indices[nombre]= {incr.first,incr.second};//asociamos al tema con su indice de siempre y la prioridad con las citas decrementadas
			cola.update(incr.first, incr.second);
		}

		else {//TC
			pair<int, tema> par;
			vector <pair<int, tema>> podio;
			for (int j = 1; j <= 3 && !cola.empty(); j++) {
				if (cola.top().prioridad.citas > 0) {
					cout << j << ' ' << cola.top().prioridad.titulo << '\n';
					par.first = cola.top().elem;
					par.second = cola.top().prioridad;
					podio.push_back(par);
					cola.pop();
				}
			}

			for (int k = 0; k < podio.size(); k++) {
				cola.push(podio[k].first, podio[k].second);
			}

		}

	}
	cout << "---"<<'\n';
	return true;
	
}


int main() {

	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}
