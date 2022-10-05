#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>		/* ofstream */
#include "camino minimo todos a todos.h"

using namespace std;


int main() {

	srand (time(0));
	int nMax = 301;	//va a correr hasta n = 300;

	//Grafo completo (con aristas de peso aleatorio)
	//variables para modificar: nMax(y/o donde empieza y de a cuanto sube n), litros(si es poco la complejidad aumenta)
	//acordarse de modificar el nombre de archivo para que sea descriptivo de los datos que tiene
	ofstream dataComp ("data_ej2_completo_aleatorio.txt");
	for(int n = 100; n < nMax; n+=20){
		int m = (n*(n-1)) / 2;

		dataComp << n << " " << m << endl; //va a tener un caso de n abajo del otro, seguidos, los valores separados por espacios
		//guardamos solo un archivo con todos uno abajo del otro? muchos archivos?
		//cout << "n: "<< n << ", m: " << m << endl;

		//creo el grafo K_n
		Grafo G;
		for(int nroNodo = 0; nroNodo < n; nroNodo++){
			nodo nodoActual;
			nodoActual.precio = rand() % 31 +10; 	//precios aleatorios desde 10 a 40

			dataComp << nodoActual.precio << endl;

			G.push_back(nodoActual);
		}

		for(int nroNodo = 0; nroNodo < n; nroNodo++){
			for(int nroVecino = nroNodo+1; nroVecino < n; nroVecino++){

				SemiArista nuevaArista;
				nuevaArista.llegada = nroVecino;
				nuevaArista.litros = rand() % 61 +1; //distancia en litros aleatoria de 1 a 60 (hacer mas casos: valen 1, valen 60)
				G[nroNodo].vecinos.push_back(nuevaArista);

				nuevaArista.llegada = nroNodo;	//y agrego la arista de direccion opuesta
				G[nroVecino].vecinos.push_back(nuevaArista);

				dataComp << nroNodo << " " << nroVecino << " " << nuevaArista.litros << endl;
			}
		}

		//evaluando tiempos (test)
	///*
		auto tiempoAntes = chrono::steady_clock::now();
		for(int i = 0; i<n; i++){
	   		BellmanFord(G, i);
		}
	   	auto tiempoDespues = chrono::steady_clock::now();

		auto res = chrono::duration <double, milli> (tiempoDespues - tiempoAntes).count();

		cout << "tiempo tardado(ms): " << res << endl;
	//*/
	}
	dataComp.close();


	//Grafo con un promedio de (aprox) k aristas por vertice(aleatorio, pero aseguro por lo menos un camino) (con aristas de peso aleatorio)
	//variables para modificar: k, nMax(y/o donde empieza y de a cuanto sube n), litros(si es poco la complejidad aumenta)
	//acordarse de modificar el nombre de archivo para que sea descriptivo de los datos que tiene
	int k = 1;
	ofstream dataGrafo ("data_ej2_camino_aleatorio.txt");
	for(int n = 100; n < nMax; n+=20){

		int m = 0;

		vector<vector<int> > listaAristas; //guardo las aristas hasta que tenga que imprimirlas

		for(int nroNodo = 0; nroNodo < n; nroNodo++){
			for(int nroVecino = nroNodo+1; nroVecino < n; nroVecino++){
				bool agregoArista = (nroVecino==nroNodo+1) || (k-1 < rand() % (n-1));
				if(agregoArista){
					vector<int> nuevaArista;
					int litros = rand() % 61 +1; //distancia en litros aleatoria de 1 a 60 (hacer mas casos: valen 1, valen 60)
					
					nuevaArista.push_back(nroNodo);
					nuevaArista.push_back(nroVecino);
					nuevaArista.push_back(litros);

					listaAristas.push_back(nuevaArista);

					m++;
				}
			}
		}


		dataGrafo << n << " " << m << endl; //igual que el anterior

		srand (time(0));

		//creo el grafo K_n
		Grafo G;
		for(int nroNodo = 0; nroNodo < n; nroNodo++){
			nodo nodoActual;
			nodoActual.precio = rand() % 31 +10; 	//precios aleatorios desde 10 a 40

			dataGrafo << nodoActual.precio << endl;

			G.push_back(nodoActual);
		}

		for(int i = 0; i<listaAristas.size(); i++){
			SemiArista nuevaArista;
			nuevaArista.llegada = listaAristas[i][1];
			nuevaArista.litros = listaAristas[i][2];
			G[listaAristas[i][0]].vecinos.push_back(nuevaArista);

			nuevaArista.llegada = listaAristas[i][0];	//agrego la arista de sentido opuesto
			G[listaAristas[i][1]].vecinos.push_back(nuevaArista);

			dataGrafo << listaAristas[i][0] << " " << listaAristas[i][1] << " " << listaAristas[i][2] << endl;
		}

		//evaluando tiempos (test)
	///*
		auto tiempoAntes = chrono::steady_clock::now();
		for(int i = 0; i<n; i++){
	   		BellmanFord(G, i);
		}
	   	auto tiempoDespues = chrono::steady_clock::now();

		auto res = chrono::duration <double, milli> (tiempoDespues - tiempoAntes).count();

		cout << "tiempo tardado(ms): " << res << endl;
	//*/
	}
	dataGrafo.close();



    return 0;
}