#include "grafoLista.h"

using GrafoAdyacencias = vector<std::vector<int>>;



vector<int> BFS(GrafoAdyacencias G) {
    vector<int> componente(G.size(), 0); //Resultado de la funcion le da un valor de componente a cada vertice.
    int componenteActual = 1;
    vector<bool> V(G.size(),false); // nodos por los que pase.
    int n = G.size();
    list<int> S;

    for(int i = 0; i < n; i++) {
        if(!V[i]) { // Si no pase por este elemento
            S.push_back(i);
            while(!S.empty()) {
                int w = S.front();
                S.pop_front();
                if(!V[w]) {
                    V[w] = true;
                    componente[w] = componenteActual;

                    for(int u : G[w]) {
                        S.push_back(u);
                    }
                }
            }
            componenteActual++;
        }
    }

    return componente;
}

bool comp_aristas(const pair<pair<unsigned int, unsigned int>, double>& a1, const pair<pair<unsigned int, unsigned int>, double>& a2) {
    return a1.second<a2.second;
}

bool comp_mayor_aristas(const pair<pair<unsigned int, unsigned int>, double>& a1, const pair<pair<unsigned int, unsigned int>, double>& a2) {
    return a1.second>a2.second;
}

int find_vector(int i, const vector<int>& comp) {
    return comp[i];
}

int find(int i, const vector<int>& padre) {
    while (padre[i] != i) {
        i = padre[i];
    }
    return i;
}

int find_compresion(int i, vector<int>& padre) {
    if(i != padre[i]) {
        padre[i] = find_compresion(padre[i],padre);
    }
    return padre[i];
}

void union_vector(pair<pair<unsigned int, unsigned int>, double> e, vector<int>& comp, vector<double>& maxComp, vector<int>& sizeComp) {
    int i = e.first.first;
    int j = e.first.second;
    int anteriorComp = comp[i];
    double maximo = e.second;
    int size = sizeComp[i] + sizeComp[j];
    for(unsigned int k = 0; k<comp.size(); k++) {
        if(comp[k] == anteriorComp or comp[k] == comp[j]) {
            comp[k] = comp[j];
            maxComp[k] = maximo;
            sizeComp[k] = size;
        }
    }
}

void union_tree(pair<pair<unsigned int, unsigned int>, double> e, vector<int>& padre, vector<double>& maxComp, vector<int>& sizeComp, vector<int>& altura) {
    int padre_i = find(e.first.first, padre);
    int padre_j = find(e.first.second, padre);
    if(altura[padre_i] < altura[padre_j]) {
        padre[padre_i] = padre_j;
        maxComp[padre_j] = e.second;
        sizeComp[padre_j] = sizeComp[padre_i] + sizeComp[padre_j];
    } else {
        padre[padre_j] = padre_i;
        maxComp[padre_i] = e.second;
        sizeComp[padre_i] = sizeComp[padre_i] + sizeComp[padre_j];
        if(altura[padre_i] == altura[padre_j]){
            altura[padre_i]++;
        }
    }
}

void union_compression(pair<pair<unsigned int, unsigned int>, double> e, vector<int>& padre, vector<double>& maxComp, vector<int>& sizeComp, vector<int>& altura) {
    int i = find(e.first.first,padre);
    int j = find(e.first.second, padre);
    if(altura[i] < altura[j]) {
        padre[i] = j;
        maxComp[j] = e.second;
        sizeComp[j] = sizeComp[i] + sizeComp[j];
    } else {
        padre[j] = i;
        maxComp[i] = e.second;
        sizeComp[i] = sizeComp[i] + sizeComp[j];
    }
    if (altura[i] == altura[j]) {
        altura[i]++;
    }
}

/*
 * Algoritmo de Kruskal con vector, Crea el AGM con una lista de aristas y devuelve un grafo AGM de G.
 */
GrafoLista kruskal_vector(GrafoLista &G, double k) {
    size_t n = G.cantNodos();
    G.sortGrafo(comp_aristas);
    /*vector<pair<pair<unsigned int, unsigned int>, double> > aristas = G.devolver_vector();
    int m = aristas.size();
    sort(aristas.begin(), aristas.end(), comp_aristas); *///Sorting vector O(m log(m)).

    vector<int> comp(n,-1); //Vector que me indica quien es el comp (para comprender las componentes conexas).
    for(unsigned int i = 0; i<n; i++) { comp[i] = i; }
    vector<double> maxComp(n,0);
    vector<int> sizeComp(n,1);
    vector<pair<pair<unsigned int, unsigned int>, double> > aristas_res;
    aristas_res.reserve(n);

    for(auto e : G) {
        int padre_i = find_vector(e.first.first, comp);
        int padre_j = find_vector(e.first.second, comp);
        if (padre_i != padre_j and
            e.second <= min(maxComp[padre_i] + k/sizeComp[padre_i], maxComp[padre_j] + k/sizeComp[padre_j])) {
            aristas_res.push_back(e); //Agrego la arista porque no genera ciclo
            union_vector(e, comp, maxComp, sizeComp); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }
        /*if (find(aristas[i].first.first, comp) != find(aristas[i].first.second, comp)) {
            aristas_res.push_back(aristas[i]); //Agrego la arista porque no genera ciclo
            union_tree(aristas[i].first.first, aristas[i].first.second, comp); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }*/
    }
    return GrafoLista(n, aristas_res);
}

/*
 * Algoritmo de Kruskal, Crea el AGM con una lista de aristas y devuelve un grafo AGM de G.
 */
GrafoLista kruskal_tree(GrafoLista &G, double k) {
    size_t n = G.cantNodos();
    G.sortGrafo(comp_aristas);
    /*vector<pair<pair<unsigned int, unsigned int>, double> > aristas = G.devolver_vector();
    int m = aristas.size();
    sort(aristas.begin(), aristas.end(), comp_aristas); *///Sorting vector O(m log(m)).

    vector<int> padre(n,-1); //Vector que me indica quien es el padre (para comprender las componentes conexas).
    for(unsigned int i = 0; i<n; i++) { padre[i] = i; }
    vector<double> maxComp(n,0);
    vector<int> sizeComp(n,1);
    vector<int> altura(n,1); //Vector de altura de los arboles.
    vector<pair<pair<unsigned int, unsigned int>, double> > aristas_res;
    aristas_res.reserve(n);

    for(auto e : G) {
        int padre_i = find(e.first.first, padre);
        int padre_j = find(e.first.second, padre);
        if (padre_i != padre_j and
            e.second <= min(maxComp[padre_i] + k/sizeComp[padre_i], maxComp[padre_j] + k/sizeComp[padre_j])) {
            aristas_res.push_back(e); //Agrego la arista porque no genera ciclo
            union_tree(e, padre, maxComp, sizeComp, altura); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }
        /*if (find(aristas[i].first.first, padre) != find(aristas[i].first.second, padre)) {
            aristas_res.push_back(aristas[i]); //Agrego la arista porque no genera ciclo
            union_tree(aristas[i].first.first, aristas[i].first.second, padre); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }*/
    }
    return GrafoLista(n, aristas_res);
}

/*
 * Algoritmo de Kruskal, con path Compression, Crea el AGM con una lista de aristas y devuelve un grafo AGM de G.
 */
GrafoLista kruskal_path_compression(GrafoLista & G, double k) {
    size_t n = G.cantNodos();
    G.sortGrafo(comp_aristas); //Sorting del vector de aristas en O(n log (n)).
    /*vector<pair<pair<unsigned int, unsigned int>, double> > aristas = G.devolver_vector();
    int m = aristas.size();
    sort(aristas.begin(), aristas.end(), comp_aristas); */ //Sorting vector O(n log(n)).

    vector<int> padre(n,-1); //Vector que me indica quien es el padre (para comprender las componentes conexas).
    vector<double> maxComp(n,0);
    vector<int> sizeComp(n,1);
    vector<int> altura(n,1); //Vector de altura de los arboles de path compression.
    for(unsigned int i = 0; i<n; i++) { padre[i] = i; }
    vector<pair<pair<unsigned int, unsigned int>, double> > aristas_res;
    aristas_res.reserve(n);

    for(auto e : G) {  //(int i = 0; i<m; i++) {
        int padre_i = find_compresion(e.first.first, padre);
        int padre_j = find_compresion(e.first.second, padre);
        if (padre_i != padre_j and
        e.second <= min(maxComp[padre_i] + k/sizeComp[padre_i], maxComp[padre_j] + k/sizeComp[padre_j])) {
            aristas_res.push_back(e); //Agrego la arista porque no genera ciclo
            union_compression(e, padre, maxComp, sizeComp, altura); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }
        /*if (find_compresion(aristas[i].first.first, padre) != find_compresion(aristas[i].first.second, padre)) {
            aristas_res.push_back(aristas[i]); //Agrego la arista porque no genera ciclo
            union_compression(aristas[i].first.first, aristas[i].first.second, padre, altura); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }*/
    }
    return GrafoLista(n,aristas_res);
}