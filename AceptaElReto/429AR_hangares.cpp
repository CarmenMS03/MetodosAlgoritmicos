#include <iostream>
#include <queue>

using namespace std;


const int MAX_NAVES = 200;

bool resuelveCaso() {
	int hangares = 0;
	cin >> hangares;
	if (hangares == 0) return false;

	priority_queue<int> cola_hangares; //cola de max por defecto

	for (int i = 0; i < hangares; i++) {
		int tam =0 ;
		cin >> tam;
		cola_hangares.push(tam);
	}
	
	int naves = 0;
	cin >> naves;
	int arraynaves[MAX_NAVES];
	for (int i = 0; i < naves; i++) {
		int tam = 0;
		cin >> tam;
		arraynaves[i] = tam;
	}

	bool posible = true;
	for (int i = 0; i < naves && posible; i++) {
		int nave = arraynaves[i];
		int hangar = cola_hangares.top();
		int resta = hangar - nave;
		if (resta < 0) {
			posible = false;
		}
		else {
			cola_hangares.pop();
			cola_hangares.push(resta);
		}
	}
	if (posible) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0 ;
}
