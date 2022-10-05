#ifndef ALGO_3_TP2_ALGORITMOS_H
#define ALGO_3_TP2_ALGORITMOS_H

#include "estructurasGrafos.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <queue>


/*
 * Algoritmo de Prim, recibe como matriz porque asi es O(n^2) pero ademas devuelve como Lista porque la parte de
 * eliminar aristas por ser inconsistente tendria complejidad O(m*(m+m)) si es con lista de aristas (por cada
 * arista, mirar las aristas adyacentes y calcular su promedio o el desvio estandar y eliminarla segun corresponda),
 * pero un AGM cumple que O(m)=O(n) entonces O(m*(m+m))=O(n^2). En cambio con matriz de adyacencia seria y O(n^2*(n)),
 * por cada arista (n^2) debemos calcular el promedio de las aristas adyacentes (n) entonces queda O(n^3)>O(n^2) para
 * lista.
 */
GrafoLista prim(const GrafoMatriz & G);

/*
 * Algoritmo de kruskal. Recibe lista porque es mas comodo para ordenar las aristas de menor a mayor, y devuelve lista
 * por la misma razon que Prim.
 */
GrafoLista kruskal(const GrafoLista & G);

/*
 * Algoritmo de kruskal. Recibe lista porque es mas comodo para ordenar las aristas de menor a mayor, y devuelve lista
 * por la misma razon que Prim.
 */
GrafoLista kruskal_path_compression(const GrafoLista & G);

/*
 * Método número 1 de descarte de aristas inconsistentes. Si supera el desvío entonces las descarta.
 */
vector<list< pair< unsigned int, double> > > descartar_aristas_BFS(const GrafoLista &G, double factorDeInconsistencia, bool ambas_vecindades, int longitud_vecindad,
                                 bool esConPromedio);

/*
 * Algoritmo de Bellman-Ford con lista de adyacencias, itera n veces sobre las aristas para "relajarlas", cada vez que
 * relaja además recuerda la arista padre que la relajo, con el fin de que nos quede un arbol de distancias mínimas.
 * (Pero en particular porque ese "árbol" tendra un ciclo si habia un ciclo negativo en el grafo alcanzable desde start).
 * Para encontrar dicho ciclo paso por todos los vertices y los guardo hasta que pase por un vertice que ya pase, el
 * primer vertice por el que pase 2 veces será el inicio y fin del ciclo. Cómo antes de encontrarlo pude pasar por otros
 * elimino los iniciales hasta que el primer vertice sea el repetido.
 */
pair<bool,list<int> > ford_bellman(const GrafoLista & G, unsigned int start);

/*
 * Floyd-Warshall, en cada iteracion actualiza el construir_circuito desde i hasta j, si pasando por k es más rápido.
 */
pair<bool, list<int> > floyd_warshall(const GrafoMatriz & G);

#endif //ALGO_3_TP2_ALGORITMOS_H
