//
// Created by nahuel on 14/05/19.
//

#ifndef ESCRITORIO_CAMINO_MINIMO_TODOS_A_TODOS_H
#define ESCRITORIO_CAMINO_MINIMO_TODOS_A_TODOS_H
#include <vector>
#include <list>
#include <utility>
#include <limits.h>
#include <math.h>
using namespace std;

typedef unsigned int uint;
typedef uint Vertice;
typedef uint Precio;
typedef int Litro;
struct SemiArista{      //Solo contiene un extremo.
    Vertice llegada;
    Litro litros;
};
struct nodo{
    list<SemiArista> vecinos;
    Precio precio;
};
typedef vector<nodo> Grafo;
typedef vector<Precio[61]> Matriz_litros;
#define MAX_PRECIO UINT_MAX/2
#define min(a, b) (a < b) ? a : b
#define max(a, b) (a > b) ? a : b

vector<Precio> BellmanFord(Grafo &G, Vertice orig);

vector<vector<Precio> > FloyWarshall(Grafo &G);

#endif //ESCRITORIO_CAMINO_MINIMO_TODOS_A_TODOS_H
