#include <iostream>
#include <queue>

using namespace std;

struct registro {
	int tiempo; 
	int id;
	int periodo;
};
bool operator<(registro const& a, registro const& b) {
	return a.tiempo < b.tiempo ||
		(a.tiempo == b.tiempo && a.id < b.id);
}
bool operator>(registro const& a, registro const& b) {
	return b < a;
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (N == 0) return false;
	priority_queue<registro,vector<registro>,greater<registro>> cola;
	
	for (int i = 0; i < N; ++i) {
		int id_usu, periodo;
		cin >> id_usu >> periodo;
		cola.push({ periodo, id_usu, periodo });
	}
	int envios;
	cin >> envios;
	while (envios--) {
		registro e = cola.top(); cola.pop();
		cout << e.id << '\n';
		e.tiempo += e.periodo;
		cola.push(e);
	}
	cout << "---" << endl;
	return true;
}


int main() {
	
	while (resuelveCaso());
	return 0;
}
