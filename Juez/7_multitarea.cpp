#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <fstream>

using namespace std;

typedef struct tarea {
	long long int inicio;
	long long int fin;
	long long int repe = 0;
};

bool operator<(tarea const& a, tarea const& b) {
	return (a.inicio < b.inicio);
}
bool operator >(tarea const& a, tarea const& b) {
	return b < a;
}

bool resuelveCaso() {

	int tareasU = 0, tareasP = 0; long long int  minuto = 0;
	cin >> tareasU >> tareasP >> minuto;

	if (!cin) return false;

	priority_queue<tarea, vector<tarea>, greater<tarea>> cola;

	for (int i = 0; i < tareasU; i++) {
		tarea t;
		cin >> t.inicio >> t.fin;
		t.repe = 0;
		cola.push(t);
	}

	for (int j = 0; j < tareasP; j++) {
		tarea t;
		cin >> t.inicio >> t.fin>>t.repe;
		cola.push(t);
	}


	bool sinconf = true;

	while (sinconf && cola.size()>1 && cola.top().inicio <= minuto) {
		tarea cur = cola.top(); cola.pop();
		if (cur.repe != 0 && (cur.inicio + cur.repe) < minuto) {
				cola.push({cur.inicio+cur.repe, cur.fin+cur.repe, cur.repe});
		}
		if (cur.inicio == cola.top().inicio) sinconf = false;
		if (cur.fin > cola.top().inicio) sinconf = false;
		
	}


	if (sinconf) {
		cout << "NO\n";
	}
	else {
		cout << "SI\n";
	}

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


	