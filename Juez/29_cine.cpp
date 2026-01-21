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


/* DEMOSTRACIÓN DE OPTIMALIDAD POR REDUCCIÓN DE DIFERENCIA

--> REPRESENTACIÓN DE LA SOLUCIÓN: Vector de booleanos de longitud N. Cada posición i del vector indica si la película i se va a ver o no (True o False).
Tenemos el vector ordenado de menor a mayor por hora de finalización de las películas.

--> DEMOSTRACIÓN DE OPTIMALIDAD: Supongamos que existe una solución óptima que no coincide con la solución voraz que hemos obtenido:

	Solución voraz : x1...xj...xN	-Ambas soluciones tienen el mismo número de películas N.
	Solución óptima: y1...yk...yN	-j es la primera posición en la que difieren las dos soluciones. Tenemos que x1...xj-1 = y1...yj-1.

	1. Si xj = True, entonces yj = False:
		Debe haber un True en la solución óptima más adelante del vector de la solución óptima (sino no sería óptima al tener una solución que difiere en 1 con la voraz):
		Solución voraz : x1...xj...xk...xN	-En la posición yk hay un True (que es el primer True que aparece después de yj).
		Solución óptima: y1...yk...yk...yN	-Sabemos que, como xj=False e yk es el primer True de la solución óptima después de yj, el tramo xj...xk=False (para que no difieran en el número de películas que se ven).


		Nos planteamos si es posible hacer un intercambio entre yj e yk: 
		-Desde el punto de vista de la optimalidad no cambiaría el número de películas que se ven.
		-Sobre la factibilidad, tenemos que dada la construcción de la solución voraz y que el tramo previo a j es todo igual en ambas soluciones, sabemos
		que al haber sido seleccionada en la voraz la película j puede ser seleccionada en la óptima (ya que no hay ninguna película previa que lo impida).

	2. Si xj = False, entonces yj = True:
		Este caso no puede darse. Por la construcción de la solución voraz sabemos que si xj=False, esa película no puede ser seleccionada al entrar en conflicto
		con las anteriores, que resultan estar seleccionadas o no de la misma manera en ambas soluciones.
		Por tanto, si yj fuese True la solución óptima no sería si quiera solución al no ser factible.

*/

/* COSTE DE LA SOLUCIÓN
	El coste de la solución es O(NlogN) ya que el coste de ordenar el vector de películas es O(NlogN) y el coste de recorrer el vector de películas es O(N)
	por la manera en la que se avanza el indice i en el bucle.
	El coste total es O(NlogN). (Siendo N el número de películas que hay para ver)
*/


using namespace std;


struct p {
	int inicio;
	int fin;
};

bool operator <(p const& a, p const& b) {
	return a.fin < b.fin;
}



bool resuelve() {

	int N;
	cin >> N;
	if (N == 0) return false;

	vector<p> pelis;

	int hora;
	int min;
	char puntos;
	int duracion;

	for (int i = 0; i < N; i++) {
		cin >> hora >> puntos >> min >> duracion;

		p peli;
		peli.inicio = hora * 60 + min;
		peli.fin = peli.inicio + duracion + 10; //mas los diez minutos extra que necesita
		pelis.push_back(peli);
	}

	sort(pelis.begin(), pelis.end()); //se ordenan las peliculas por hora de finalización de menor a mayor

	int peliculas = 1;

	int j = 0;
	for (int i = 0; i < N; i++) {

		while (j < N && pelis[j].inicio < pelis[i].fin) {//por la ordenación sabemos que j termina después que i
			j++;
		}
		if (j < N) {
			peliculas++;	
		}
		i = j - 1;
		j++;
	}

	cout << peliculas << '\n';

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelve());
	return 0;
}