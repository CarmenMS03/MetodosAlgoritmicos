#include "TreeSet_AVL.h"
#include <iostream>

using namespace std;

void leer();

int main() {
    leer();
    return 0;
}
void leer() {
    int N;

    while (cin >> N && N != 0) {
        Set<int> conjunto;
        for (int i = 0; i < N; ++i) {
            int valor;
            cin >> valor;
            conjunto.insert(valor);
        }

        int M;
        cin >> M;


        for (int i = 0; i < M; ++i) {
            int k;
            cin >> k;

            if (k < 1 || k > conjunto.size()) {
                cout << "??" << endl;
            }
            else {
                try {

                    int elemento = conjunto.kesimo(k);
                    cout << elemento << endl;
                }
                catch (out_of_range& e) {
                    cout << "??" << endl;
                }
            }
        }
        cout << "---" << endl;
    }
}