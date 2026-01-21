#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>

using namespace std;

struct edificio {
	int izq;
	int der;
};

bool operator<(edificio const& a, edificio const& b) { //para ordenar los edificios de menor a mayor extremo oriental
	return a.der < b.der;
}

bool resuelve() {

	int N;
	cin >> N;
	if (N==0) return false;

	vector<edificio> edificios(N);
	for (int i = 0; i < N; i++) {
		cin >> edificios[i].izq >> edificios[i].der;
	}

	vector<bool> tiene;
	tiene.assign(N, false);

	sort(edificios.begin(), edificios.end()); //se ordenan los edificios

	int tuneles = 1;//en el primero siempre debemos poner un tunel
	tiene[0] = true;

	int j = 1;
	for (int i = 0; i < N; i++) { 

		while (j < N && (edificios[j].izq <edificios[i].der && edificios[i].der <=edificios[j].der)) { // tiene tunel
			tiene[j] = true;
			j++;
		}
		if (j < N) {//se construye uno nuevo
			tuneles++;
			tiene[j] = true;
		}
		i = j-1;// i es donde habrá túnel (j-1 pq al hacer ++ será j que es donde hemos construido el nuevo)
		j++; //j+1 será el siguiente edificio a comprobar
	}

	cout << tuneles << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}