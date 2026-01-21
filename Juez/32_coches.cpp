#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;


void resuelve() {

	int N,V;
	cin >> N>>V;

	vector<int> pilas;

	int v=0;
	for (int i = 0; i < N; i++) {
		cin >> v;

		pilas.push_back(v);
	}

	sort(pilas.begin(), pilas.end(), greater<int>()); //se ordenan las pilas de mayor a menor voltaje


	int sol = 0;

	int j = N - 1; //indice para recorrer las pilas de menor voltaje
	for (int i = 0; i < N; i++) { // i recorre las pilas de mayor voltaje

		while (j>i && pilas[i] + pilas[j] < V ) {
			j--;
		}
		if (j > i) {
			sol++;
			j--;
		}
		else {
			break;
		}

	}

	cout << sol << '\n';

}

int main() {
	int N;
	cin >> N;
	while (N > 0) {
		resuelve();
		N--;
	}
	return 0;
}