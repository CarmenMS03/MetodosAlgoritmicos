#include "bintree_eda.h";

using namespace std;

void leer();
bool resuelveCaso(bintree<int> const& arbol);

int main() {
	leer();
	return 0;
}

bool resuelveCasoAux(bintree<int> const& arbol, int& altura, int& minVal, int& maxVal) {
	if (arbol.empty()) {
		altura = 0;
		return true;
	}

	bool AVL = true;
	int alturaIzq = 0, alturaDer = 0;
	int minIzq, maxIzq, minDer, maxDer;
	if (!arbol.left().empty()) {
		AVL = resuelveCasoAux(arbol.left(), alturaIzq, minIzq, maxIzq);
		if (!AVL || maxIzq >= arbol.root()) return false;
	}
	else {
		minIzq = arbol.root(); // hemos llegado al final
	}

	if (!arbol.right().empty()) {
		AVL = AVL && resuelveCasoAux(arbol.right(), alturaDer, minDer, maxDer);
		if (!AVL || minDer <= arbol.root()) return false;
	}
	else {
		maxDer = arbol.root();
	}

	altura = max(alturaIzq, alturaDer) + 1;


	if (abs(alturaIzq - alturaDer) > 1) return false;


	minVal = min(minIzq, arbol.root());
	maxVal = max(maxDer, arbol.root());

	return AVL;



}

bool resuelveCaso(bintree<int> const& arbol) {
	int altura = 0;
	int minVal, maxVal;
	return resuelveCasoAux(arbol, altura, minVal, maxVal);
}

void leer() {
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++) {
		bintree<int> arbol = leerArbol(-1);
		if (resuelveCaso(arbol)) cout << "SI" << endl;
		else cout << "NO" << endl;
	}



}