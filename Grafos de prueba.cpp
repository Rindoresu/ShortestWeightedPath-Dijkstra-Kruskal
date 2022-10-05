#include <iostream>
#include "camino minimo todos a todos.h"

#ifndef GRAFOS
#define GRAFOS

using namespace std;

void printVecinos(nodo n){
	for(SemiArista sa : n.vecinos)
		cout << sa.llegada << ", " << sa.litros << endl;
}

string mostrar_resultados(string quien, Vertice orig, vector<Precio> costos){
	string res = string("Resultados de ") + quien + string(":\n");
	for(Vertice v = 0; v < costos.size(); ++v)
		res += to_string(orig) + "-" + to_string(v) + ": $" + to_string(costos[v]) + "\n";
	return res;
}

string mostrar_resultados_BF_FW_en_paralelo(Vertice orig, const vector<Precio>& costosBF, const vector<vector<Precio> >& costosFM){
    string res = string("Desde ") + to_string(orig) + string(":\n\t|BF\t\t|FW\n");
    for(Vertice v = 0; v < costosBF.size(); ++v)
        res += to_string(v) + ":\t$" + to_string(costosBF[v]) + ((to_string(costosBF[v]).size() < 3) ? "\t\t$" : "\t$") + to_string(costosFM[orig][v]) + "\n";
    return res;
}

string mostrar_resultados_DJ1_DJ2_BF_FW_en_paralelo(Vertice orig, const vector<Precio>& costosDJ1, const vector<Precio>& costosDJ2, const vector<Precio>& costosBF, const vector<vector<Precio> >& costosFM){
    string res = string("Desde ") + to_string(orig) + string(":\n\t|DJ1\t|DJ2\t|BF\t\t|FW\n");
    for(Vertice v = 0; v < costosBF.size(); ++v) {
        res += to_string(v) + ":\t$";
        res += to_string(costosDJ1[v]) + ((to_string(costosDJ1[v]).size() < 3) ? "\t\t$" : "\t$");
        res += to_string(costosDJ2[v]) + ((to_string(costosDJ2[v]).size() < 3) ? "\t\t$" : "\t$");
        res += to_string(costosBF[v])  + ((to_string( costosBF[v]).size() < 3) ? "\t\t$" : "\t$");
        res += to_string(costosFM[orig][v]) + "\n";
    }
    return res;
}

pair<vector<Grafo>, vector<string> > grafosDePreuba() {
	vector<Grafo> grafos;
	vector<string> resultados_esperados_desde_0;
/*	CASO 1 idea:

	1--3--4
	|\ |
	| \|
	0--2

	precios:
	0: $3
	1: $5
	2: $1
	3: $2
	4: $4

	caminos:
	0-1: 20L
	0-2: 40L
	1-2: 5L
	1-3: 20L
	2-3: 30L
	3-4: 40L
*/
	Grafo g1;
	string resultado_esperado;

	//creo nodos
	g1.push_back({{{1, 20}, {2, 40}}, 3}); 

	g1.push_back({{{0, 20}, {2, 5}, {3, 20}}, 5});

	g1.push_back({{{0, 40}, {1, 5}, {3, 30}}, 1});

	g1.push_back({{{1, 20}, {2,30}, {4, 40}}, 2});

	g1.push_back({{{3, 40}}, 4});

	grafos.push_back(g1);
/*chequeo que este bien armado
	cout << "los precios de los nodos son:" << endl;
	for(int i = 0; i<5; i++){
		cout<< i <<": $" << g[i].precio << endl;
	}

	cout << "los vecinos de los nodos son:" << endl;
	for(int i = 0; i<5; i++){
		cout << "para el nodo " << i << ":" << endl;
		printVecinos(g[i]);
	}
*/

	resultado_esperado = 	"CASO 1:\n"
					 	 	"De nodo 0 al resto, resultados esperados:\n"
							"0-0: $0\n"
	   						"0-1: $60  (recorrido: 0-1)\n"
		  					"0-2: $75  (recorrido: 0-1-2)\n"
		 					"0-3: $100  (recorrido: 0-1-2-1-3)\n"
							"0-4: $145  (recorrido: 0-1-2-1-3-4)\n";

	resultados_esperados_desde_0.emplace_back(resultado_esperado);

/*	CASO 2 idea:
	
	0---1
	|   |
	5   2
	|   |
	4---3

	precios:
	0: $5
	1: $4
	2: $11
	3: $1
	4: $7
	5: $9

	caminos:
	0-1: 40L
	1-2: 50L
	2-3: 60L
	3-4: 15L
	4-5: 20L
	5-0: 30L
*/

	Grafo g2;

	//creo nodos
	g2.push_back({{{1, 40}, {5, 30}}, 5});

	g2.push_back({{{0, 40}, {2, 50}}, 4});

	g2.push_back({{{1, 50}, {3, 60}}, 11});

	g2.push_back({{{2, 60}, {4, 15}}, 1});

	g2.push_back({{{3, 15}, {5, 20}}, 7});

	g2.push_back({{{4, 20}, {0, 30}}, 9});

	grafos.push_back(g2);

	resultado_esperado = "De nodo 0 al resto, resultados esperados:\n"
                        "0-0: $0\n"
                        "0-1: $200  (recorrido: 0-1)\n"
                        "0-2: $395  (recorrido: 0-5-4-3-2)\n"
                        "0-3: $335  (recorrido: 0-5-4-3)\n"
                        "0-4: $250  (recorrido: 0-5-4)\n"
                        "0-5: $150  (recorrido: 0-5)\n";

    resultados_esperados_desde_0.push_back(resultado_esperado);

/*	CASO 3 idea:
	
	0   3
	|\ /|
	| 4 |
	|/ \|
	1---2

	precios:
	0: $1
	1: $8
	2: $5
	3: $3
	4: $7

	caminos:
	todos de 45L
*/

	Grafo g3;

	//creo nodos
	g3.push_back({{{1, 45}, {4, 45}}, 1});

	g3.push_back({{{0, 45}, {2, 45}, {4, 45}}, 8});

	g3.push_back({{{1, 45}, {3, 45}, {4, 45}}, 5});

	g3.push_back({{{2, 45}, {4, 45}}, 3});

	g3.push_back({{{0, 45}, {1, 45}, {2, 45}, {3, 45}}, 7});

    grafos.push_back(g3);

    resultado_esperado = "De nodo 0 al resto, resultados esperados:"
                         "0-0: $0"
                         "0-1: $45  (recorrido: 0-1)"
                         "0-2: $270  (recorrido: 0-4-2)"
                         "0-3: $270  (recorrido: 0-4-3)"
                         "0-4: $45  (recorrido: 0-4)";

    resultados_esperados_desde_0.push_back(resultado_esperado);

/*	CASO 4 idea:
	  4
	 / \
	3---5
	|  /|
	| / 0
	|/  |
	2---1

	precios:
	para todos $2

	caminos:
	0-1: 55L
	0-5: 5L
	1-2: 1L
	2-3: 10L
	2-5: 20L
	3-4: 40L
	3-5: 45L
	4-5: 60L
*/

	Grafo g4;

	//creo nodos
	g4.push_back({{{1, 55}, {5, 5}}, 2});

	g4.push_back({{{0, 55}, {2, 1}}, 2});

	g4.push_back({{{1, 1}, {3, 10}, {5, 20}}, 2});

	g4.push_back({{{2, 10}, {4, 40}, {5, 45}}, 2});

	g4.push_back({{{3, 40}, {5, 60}}, 2});

	g4.push_back({{{0, 5}, {2, 20}, {3, 45}, {4, 60}}, 2});

	grafos.push_back(g4);

	resultado_esperado = "De nodo 0 al resto, resultados esperados:"
                      "0-0: $0"
                      "0-1: $52  (recorrido: 0-5-2-1)"
                      "0-2: $50  (recorrido: 0-5-2)"
                      "0-3: $70  (recorrido: 0-5-2-3)"
                      "0-4: $130  (recorrido: 0-5-4)"
                      "0-5: $10  (recorrido: 0-5)";

	resultados_esperados_desde_0.push_back(resultado_esperado);

    return make_pair(grafos, resultados_esperados_desde_0);
}
#endif