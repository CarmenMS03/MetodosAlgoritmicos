#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>

using namespace std;

bool resuelve() {

	int N, L;
	cin >> N >> L;
	if (!cin) return false;

	vector<int> agujeros(N); //en orden creciente
	for (int i = 0; i < N; i++) {
		cin >> agujeros[i];
	}

	int numparches = 0;

	for (int i = 0; i < N; i++) {
		int j = i;
		while (j < N && agujeros[j] - agujeros[i] <= L) {//mientras que el agujero este a una distancia menor o igual a L, no se necesita otro parche
			j++;
		}
		numparches++; //se necesita un parche más
		i = j - 1; //se pone i en la posición del último agujero tapado (al incrrmentar será justo j que es el tapado)
	}

	cout << numparches << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}