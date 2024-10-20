#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <list>
using namespace std;


bool resuelveCaso() {

	int drones = 0, pilas9 = 0, pilas15 = 0;
	cin >> drones >> pilas9 >> pilas15;

	if (!cin) return false;

	priority_queue<int> colapila9;
	priority_queue<int> colapila15;

	for (int i = 0; i < pilas9; i++) {
		int t;
		cin >> t; 
		colapila9.push(t);
	}

	for (int j = 0; j < pilas15; j++) {
		int t;
		cin >> t;
		colapila15.push(t);
	}

	bool s= true;
	while (colapila15.size() > 0 && colapila9.size() > 0) {
		vector<int> upila9, upila15;
		for (int i = 0; i < drones && colapila15.size()>0 && colapila9.size() > 0; i++) {
			upila9.push_back( colapila9.top()); colapila9.pop();
			upila15.push_back(colapila15.top()); colapila15.pop();

		}
		int horas = 0;
		for (int i = 0; i < upila9.size(); i++) {
			int a = min(upila9[i], upila15[i]);
			horas += a;
			if ((upila9[i] - a) > 0) colapila9.push(upila9[i] - a);
			if ((upila15[i] - a ) > 0) colapila15.push(upila15[i] - a);
		}
		if (!s) cout << ' ';
		cout << horas;

		s = false;
	}

	cout << endl;

	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}


