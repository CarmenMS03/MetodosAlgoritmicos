#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "Digrafo.h"

using namespace std;


bool resuelve() {
	int V;
	cin >> V;
	if (!cin) return false;

	int A;
	cin >> A;

	Digrafo g(V);
	int a, b;
	for (int i = 0; i < A; i++) {
		cin >> a >> b;
		g.ponArista(a, b);
	}

	vector<bool> sinsalida(V, false);
	for (int i = 0; i < V; i++) {
		if (g.ady(i).size() == 0) sinsalida[i] = true;
	}

	Digrafo ginv = g.inverso();
	int sumidero;
	bool hay = false;
	for (int i = 0; i < V; i++) {
		if (sinsalida[i] && ginv.ady(i).size() == V-1) {
			sumidero = i;
			hay = true;
		}
	}

	if (hay) {
		cout << "SI" << ' ' << sumidero;
	}
	else {
		cout << "NO";
	}
	cout << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}