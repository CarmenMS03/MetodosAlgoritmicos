#include <iostream>
#include <queue>
#include <string>
#include <list>
using namespace std;

typedef struct paciente {
	string nombre;
	int gravedad;
	int pos;
};

bool operator<(paciente const& a, paciente const& b) {
	return a.gravedad < b.gravedad ||
		(a.gravedad == b.gravedad && a.pos > b.pos);
}
bool operator>(paciente const& a, paciente const& b) {
	return b < a;
}

void resuelveCaso(int eventos) {

	list<string> atendidos;
	priority_queue<paciente> urgencias;

	int pos = 1;
	while (eventos > 0) {
		
		char tipo;
		cin >> tipo;

		if (tipo == 'I') {
			paciente p;
			cin >> p.nombre >> p.gravedad;
			p.pos = pos;
			urgencias.push(p);
			pos++;
		}
		else {
			atendidos.push_back(urgencias.top().nombre);
			urgencias.pop();
		}
		eventos--;
	}

	for (string a : atendidos) {
		cout << a << endl;
	}
	cout << "---" << endl;
}


int main() {
	int N;
	cin >> N;
	while (N!=0) {
		resuelveCaso(N);
		cin >> N;
	}
	return 0;
}
