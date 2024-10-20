#include <iostream>
#include <queue>

using namespace std;


bool resuelveCaso() {
	int N;
	cin >> N;
	if (N == 0) return false;

	priority_queue<long long int, vector<long long int>, greater<long long int>> cola;

	for (int i = 0; i < N; ++i) {
		long long int num;
		cin >> num;
		cola.push(num);
	}

	long long int min = 0;

	while (cola.size() > 1) {
		long long int sumando1 = cola.top();
		cola.pop();
		if (cola.size() > 0) {
			long long int sumando2 = cola.top();
			cola.pop();
			min += (sumando1 + sumando2);
			cola.push(sumando1 + sumando2);
		}
	}

	cout << min << endl;

	return true;
}


int main() {

	while (resuelveCaso());
	return 0;
}
