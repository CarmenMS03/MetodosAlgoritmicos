#include <iostream>
#include <queue>
#include <string>
#include <list>
using namespace std;

typedef struct caja {
	int numero;
	int tiempo;
};

bool operator<(caja const& a, caja const& b) {
	return a.tiempo < b.tiempo ||
		(a.tiempo == b.tiempo && a.numero < b.numero);
}
bool operator>(caja const& a, caja const& b) {
	return b < a;
}

bool resuelveCaso() {

	int cajas = 0, clientes = 0;
	cin >> cajas >> clientes;

	if (cajas == 0 && clientes == 0)return false;

	queue<int> colaprincipal;

	for (int i = 0; i < clientes; i++) {
		int segundos=0;
		cin >> segundos;
		colaprincipal.push(segundos);
	}

	priority_queue<caja, vector<caja>, greater<caja>> cajasocupadas;

	for (int i = 1; i <= cajas; i++) {
		caja c;
		c.numero = i;
		c.tiempo = 0;
		cajasocupadas.push(c);
	}

	for (int i = 0; i <clientes; i++) {
		caja c = cajasocupadas.top(); cajasocupadas.pop();
		c.tiempo += colaprincipal.front();
		colaprincipal.pop();
		cajasocupadas.push(c);
	}

	int cajaismael = cajasocupadas.top().numero;

	cout << cajaismael << endl;

	return true;
	
}


int main() {
	while (resuelveCaso());
	return 0;
}
