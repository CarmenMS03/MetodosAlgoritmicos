#include <iostream>
#include <queue>
using namespace std;


bool resuelveCaso() {

	int primero, num_parejas;
	cin >> primero >> num_parejas;

	if (primero == 0 && num_parejas == 0) return false;

	
	priority_queue<int, vector<int>, greater<int>> derecha;
	priority_queue<int> izquierda;
	

	for (int i = 0; i < num_parejas; ++i) {
		int edad1, edad2;
		cin >> edad1 >> edad2;
		if (edad1 <= primero && primero <= edad2) {
			izquierda.push(edad1);
			derecha.push(edad2);
		}
		else if (edad2 <= primero && primero <= edad1) {
			izquierda.push(edad2);
			derecha.push(edad1);
		}
		else if (edad1 < primero && edad2 < primero) {
			izquierda.push(edad1);
			izquierda.push(edad2);
			derecha.push(primero);
			primero = izquierda.top();
			izquierda.pop();
		}
		else if (edad1 > primero && edad2 > primero) {
			derecha.push(edad1);
			derecha.push(edad2);
			izquierda.push(primero);
			primero = derecha.top();
			derecha.pop();
		}
		cout << primero<<' ';
	}
	cout << endl;
	return true;
}

int main() {

	while (resuelveCaso());
	
	return 0;
}