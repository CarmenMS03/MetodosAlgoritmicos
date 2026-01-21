#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>

using namespace std;

bool resuelve() {

	int N;
	cin >> N;
	if (!cin) return false;

	vector<int> invadidas(N); 
	for (int i = 0; i < N; i++) {
		cin >> invadidas[i];
	}
	vector<int> defensa(N);
	for (int i = 0; i < N; i++) {
		cin >> defensa[i];
	}

	sort(invadidas.begin(), invadidas.end());
	sort(defensa.begin(), defensa.end());

	int numciudades = 0;

	int j = 0;
	for (int i = 0; i < N; i++) {

		while (j < N && defensa[j] < invadidas[i]) { //no puedo defender
			j++;
		}
		if (j < N) {
			numciudades++;
			j++;
		}
		
	}

	cout << numciudades << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}