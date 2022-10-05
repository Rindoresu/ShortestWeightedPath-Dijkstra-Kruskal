#include <iostream>
#include "dijkstra_basico.h"
#include "dijkstra_prioridad.h"
#include "camino minimo todos a todos.h"
#include "Grafos de prueba.cpp"
#include <tuple>

int main() {
    //std::cout << "Hello, World!" << std::endl;

    vector<Grafo> grafos;
    vector<string> tex;
    vector<Precio> res_DJ1;
    vector<Precio> res_DJ2;
    vector<Precio> res_BF;
    vector<vector<Precio> > res_FW;
    tie(grafos, tex) = grafosDePreuba();
    char nro_grafo_a_testear = 0;
    Grafo& G = grafos[nro_grafo_a_testear];
    res_FW = FloyWarshall(G);
    bool iguales = true;

    for(Vertice orig = 0; orig < G.size(); ++orig){
        res_DJ1 = dijkstra_basico(G, orig);
        res_DJ2 = dijkstra_prioridad(G, orig);
        res_BF = BellmanFord(G, orig);
        cout << mostrar_resultados_DJ1_DJ2_BF_FW_en_paralelo(orig, res_DJ1, res_DJ2, res_BF, res_FW) << endl;
        for(Vertice v = 0; v < G.size(); ++v)
            if(not (res_DJ1[v] == res_DJ2[v] && res_DJ2[v] == res_BF[v] && res_BF[v] == res_FW[orig][v]) ) {
                iguales = false;
                cout << "FALLA EN " << orig << "-" << v << "--------------------------" << endl << endl;
            }
    }

    cout << "¿Iguales?: " << (iguales ? "sí" : "no") << endl;

    return 0;
}