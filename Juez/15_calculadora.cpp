#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
const int MAX = 10000;
const int INF = 1000000000;

int bfs(int o, int d) {
	if (o == d) return 0;
	vector<int> dist(MAX, INF);
	dist[o] = 0; 
	queue<int> q; q.push(o);

	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < 3; i++) {
			int w;
			if (i == 0) w = (v + 1)%MAX;
			else if (i == 1) w = (v * 2) % MAX;
			else w = v / 3;

			if (dist[w] == INF) {
				dist[w] = dist[v] + 1;
				if (d == w) return dist[w];
				else q.push(w);
			}
		}
	}

}

bool resuelve() {
	int origen = 0, destino = 0;
	cin >> origen >> destino;

	if (!cin) return false;
	
	cout << bfs(origen, destino) << '\n';

	return true;
}

int main() {
	while (resuelve());
	return 0;
}