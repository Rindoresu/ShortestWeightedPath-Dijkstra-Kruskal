
#include <vector>
#include <list>
#include <utility>
#include <limits.h>
#include <math.h>
#include <stdio.h> 
#include <iostream>
#include <set>
#include <tuple>

#include "camino minimo todos a todos.h"

using namespace std;

#define ciudad second
#define costo first

typedef vector<Precio[61]> Matriz_litros;

vector<Precio>  dijkstra_prioridad(Grafo &region,Vertice src);

 