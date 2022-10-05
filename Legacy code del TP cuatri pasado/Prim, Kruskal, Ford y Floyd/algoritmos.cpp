#include "algoritmos.h"

/* AGM */ /*SON GRAFOS NO DIRIGIDOS*/
/*
 * Algoritmo de Prim para crear AGM de un grafo no dirigido.
 */
GrafoLista prim(const GrafoMatriz & G) {
    size_t n = G.cantNodos();
    vector<bool> nodosAgregados(n,false);
    vector<double> distancia_a_nodo(n, numeric_limits<double>::infinity());
    vector<int> padre(n,-1);
    nodosAgregados[0] = true;
    distancia_a_nodo[0] = 0;
    int ultimo_nodo_agregado = 0;

    GrafoLista result(n); //Grafo de n nodos sin aristas.

    for(int i = 0; i < n-1; i++) { //Tengo que agregar los n nodos al arbol.
        int nodo_dist_min = -1; //Indice al nodo mínimo no agregado, empieza en -1 para indicar que no hallo un nodo no agregado todavía.
        for(int j = 0; j<n; j++) { //Actualizo las distancias y busco si es el nuevo mínimo despues de actualizarlo.
            if(G.peso(make_pair(ultimo_nodo_agregado,j)) < distancia_a_nodo[j]) {
                distancia_a_nodo[j] = G.peso(make_pair(ultimo_nodo_agregado,j));
                padre[j] = ultimo_nodo_agregado;
            }
            if(!nodosAgregados[j] and (nodo_dist_min == -1 or (nodo_dist_min != -1 and distancia_a_nodo[nodo_dist_min] > distancia_a_nodo[j]))) { //Estoy buscando al menos un nodo para agregar y encuentro uno, o encontre un nodo con mejor distancia al ya encontrado.
                nodo_dist_min = j;
            }
        }
        result.agregar_arista(make_pair(make_pair(padre[nodo_dist_min], nodo_dist_min), G.peso(make_pair(padre[nodo_dist_min],nodo_dist_min)))); //Agrego la arista que conecta al AGM al de menor distancia, y esa arista pesa lo que pesa en G.
        nodosAgregados[nodo_dist_min] = true;
        ultimo_nodo_agregado = nodo_dist_min;
    }

    return result;
}
/*
 * Funciones Auxiliares Kruskal
 */
bool comp_aristas(const pair<pair<unsigned int, unsigned int>, double>& a1, const pair<pair<unsigned int, unsigned int>, double>& a2) {
    return a1.second<a2.second;
}

bool comp_mayor_aristas(const pair<pair<unsigned int, unsigned int>, double>& a1, const pair<pair<unsigned int, unsigned int>, double>& a2) {
    return a1.second>a2.second;
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

void union_tree(int i, int j, vector<int>& padre) {
    padre[find(i, padre)] = find(j, padre);
}

void union_compression(int i, int j, vector<int>& padre, vector<int>& altura) {
    i = find(i,padre);
    j = find(j, padre);
    if(altura[i] < altura[j]) {
        padre[i] = j;
    } else {
        padre[j] = i;
    }
    if (altura[i] == altura[j]) {
        altura[i]++;
    }
}

/*
 * Algoritmo de Kruskal, Crea el AGM con una lista de aristas y devuelve un grafo AGM de G.
 */
GrafoLista kruskal(const GrafoLista & G) {
    size_t n = G.cantNodos();
    vector<pair<pair<unsigned int, unsigned int>, double> > aristas = G.devolver_vector();
    int m = aristas.size();
    sort(aristas.begin(), aristas.end(), comp_aristas); //Sorting vector O(n log(n)).

    vector<int> padre(n,-1); //Vector que me indica quien es el padre (para comprender las componentes conexas).
    for(int i = 0; i<n; i++) { padre[i] = i; }
    list<pair<pair<unsigned int, unsigned int>, double> > aristas_res;

    for(int i = 0; i<m; i++) {
        if (find(aristas[i].first.first, padre) != find(aristas[i].first.second, padre)) {
            aristas_res.push_back(aristas[i]); //Agrego la arista porque no genera ciclo
            union_tree(aristas[i].first.first, aristas[i].first.second, padre); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }
    }
    return GrafoLista(n, aristas_res);
}

/*
 * Algoritmo de Kruskal, con path Compression, Crea el AGM con una lista de aristas y devuelve un grafo AGM de G.
 */
GrafoLista kruskal_path_compression(const GrafoLista & G) {
    size_t n = G.cantNodos();
    vector<pair<pair<unsigned int, unsigned int>, double> > aristas = G.devolver_vector();
    int m = aristas.size();
    sort(aristas.begin(), aristas.end(), comp_aristas); //Sorting vector O(n log(n)).

    vector<int> padre(n,-1); //Vector que me indica quien es el padre (para comprender las componentes conexas).
    vector<int> altura(n,1); //Vector de altura de los arboles de path compression.
    for(int i = 0; i<n; i++) { padre[i] = i; }
    list<pair<pair<unsigned int, unsigned int>, double> > aristas_res;

    for(int i = 0; i<m; i++) {
        if (find_compresion(aristas[i].first.first, padre) != find_compresion(aristas[i].first.second, padre)) {
            aristas_res.push_back(aristas[i]); //Agrego la arista porque no genera ciclo
            union_compression(aristas[i].first.first, aristas[i].first.second, padre, altura); //Ahora ambos vertices pertenecen a la
            // misma componente conexa.
        }
    }
    return GrafoLista(n,aristas_res);
}


list<int> buscarCircuito(int ultimo_nodo_cambiado, vector<pair<int, double> > padres_res) {
    size_t n = padres_res.size();
    list<int> circuito;
    int nodo_actual = ultimo_nodo_cambiado;
    vector<bool> yaPase(n, false);
    yaPase[nodo_actual] = true;
    circuito.push_back(nodo_actual);
    nodo_actual = padres_res[nodo_actual].first;
    while (!yaPase[nodo_actual]) { //el distinto de -1 es por si elijo una arista que
        // todavia le convenia venir desde el origen (porque necesitamos mas de 2n pasos para reducir todas
        // las distancias por el ciclo negativo.
        circuito.push_back(nodo_actual);
        yaPase[nodo_actual] = true;
        nodo_actual = padres_res[nodo_actual].first;
    }
    circuito.push_back(nodo_actual);
    // el circuito va de j a j, entonces elimino todos los anteriores al primer j.
    while (circuito.front() != nodo_actual) {
        circuito.pop_front();
    }
    return circuito;
}

/*Caminos mínimos*/ /*Claramente son grafos dirigidos para el problema de Arbitraje*/
/*
 * Algoritmo Bellman-Ford para Digrafos con una lista de adyacencias.
 */
pair<bool,list<int> > ford_bellman(const GrafoLista & G, unsigned int start){
    vector<pair<int, double> > padres_res; //normalmente esta es la solución de Ford, pero solo queremos el circuito negativo.
    padres_res.reserve(G.cantNodos());

    for(int i = 0; i<G.cantNodos(); i++) {
        padres_res.emplace_back(make_pair(-1,numeric_limits<double>::infinity()));
    }
    padres_res[start].first = -1;
    padres_res[start].second = 0;

    size_t n = G.cantNodos();
    int k = 0;
    bool huboCambios = true;
    int ultimo_nodo_cambiado = -1; //Guarda el último nodo al que actualicé distancias. Como en la iteración n-ésima
    // su distancia solo puede mejorar por ciclos negativos, entonces el predecesor va a depender de algun ciclo negativo.

    while(k<n and huboCambios) {
        auto it = G.begin();
        huboCambios = false;

        while(it != G.end()) {
            int a = it->first.first;
            int b = it->first.second;
            double w = it->second;
            if(padres_res[b].second > padres_res[a].second + w) {
                padres_res[b].first = a;
                padres_res[b].second = padres_res[a].second + w;
                huboCambios = true;
                ultimo_nodo_cambiado = b;
            }
            it++;
        }
        k++;
    }

    list<int> circuito;
    bool hayCircuitoNeg = k == n and huboCambios;

    if(hayCircuitoNeg) { // Como hay circuito negativo, hicimos una n-ésima iteración y por tanto debemos haber
        //actualizado la distancia de algun nodo por tener un predecesor en dirección a algun ciclo negativo que le
        //mejora la distancia
        circuito = buscarCircuito(ultimo_nodo_cambiado,padres_res);

        /*int nodo_actual = ultimo_nodo_cambiado;
        vector<bool> yaPase(n, false);
        yaPase[nodo_actual] = true;
        circuito.push_back(nodo_actual);
        nodo_actual = padres_res[nodo_actual].first;
        while (!yaPase[nodo_actual]) { //el distinto de -1 es por si elijo una arista que
            // todavia le convenia venir desde el origen (porque necesitamos mas de 2n pasos para reducir todas
            // las distancias por el ciclo negativo.
            circuito.push_back(nodo_actual);
            yaPase[nodo_actual] = true;
            nodo_actual = padres_res[nodo_actual].first;
        }
        circuito.push_back(nodo_actual);
        // el circuito va de j a j, entonces elimino todos los anteriores al primer j.
        while (circuito.front() != nodo_actual) {
            circuito.pop_front();
        }*/
        /*
        bool buscandoCiclo = true;
        vector<bool> yaPase(n, false);
        int i = 0;
        while (i < n and buscandoCiclo) {
            if (!yaPase[i] and padres_res[i].first != -1) {
                yaPase[i] = true;
                circuito.push_back(i);
                int j = padres_res[i].first;
                while (!yaPase[j] and padres_res[j].first != -1) { //el distinto de -1 es por si elijo una arista que
                    // todavia le convenia venir desde el origen (porque necesitamos mas de 2n pasos para reducir todas
                    // las distancias por el ciclo negativo.
                    circuito.push_back(j);
                    yaPase[j] = true;
                    j = padres_res[j].first;
                }
                if (yaPase[j] and padres_res[j].first != -1) {
                    buscandoCiclo = false;
                    circuito.push_back(j);
                    // el circuito va de j a j, entonces elimino todos los anteriores al primer j.
                    while (circuito.front() != j) {
                        circuito.pop_front();
                    }
                } else {
                    //yaPase = vector<bool>(n,false);
                    circuito = list<int>();
                }
            }
            i++;
        }
        if (i == n and buscandoCiclo) {
            try {
                throw logic_error(
                        "Ford encontró un ciclo negativo pero no se encontró un ciclo para devolver. El programa terminará.");
            }
            catch (const logic_error &e) {
                cout << e.what() << '\n';
                throw;
            }
        }*/
    }
    pair<bool,list<int> > res;
    return make_pair(hayCircuitoNeg,circuito);
}

/*
 * Algoritmo para Floyd para calcular el construir_circuito de un vertice a otro
 */
list<int> construir_circuito(int i, vector<vector<int> > proximo) {
    if (proximo[i][i] == -1) {
        return list<int>();
    }
    int nodo_prox = i;
    list<int> camino_res;
    camino_res.push_back(nodo_prox);
    do {
        nodo_prox = proximo[nodo_prox][i];
        camino_res.push_back(nodo_prox);
    } while (nodo_prox != i);

    return camino_res;
}

/*
 * Algoritmo Floyd Warshall para Digrafos con matriz de adyacencias. Falta ver como hacer para ver los ciclos negativos.
 */
pair<bool,list<int> > floyd_warshall(const GrafoMatriz & G) {
    int n = G.cantNodos();

    GrafoMatriz *G1 = new GrafoMatriz(G);
    GrafoMatriz *G2 = new GrafoMatriz(n);
    vector<vector<int> > proximo(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            proximo[i][j] =
                    G.peso(make_pair(i, j)) == numeric_limits<double>::infinity() ? -1 : j; //El proximo de ir de i a j
            // es j si hay arista en el grafo (si no hay, ponemos -1 indicandolo).
        }
    }

    for (int i = 0; i < n; i++) { //la distancia de un nodo a si mismo es 0 (si uno decide no moverse).
        (*G2)[make_pair(i, i)] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((*G1)[make_pair(i, k)] + (*G1)[make_pair(k, j)] < (*G1)[make_pair(i, j)]) {
                    (*G2)[make_pair(i, j)] = (*G1)[make_pair(i, k)] + (*G1)[make_pair(k, j)];
                    proximo[i][j] = proximo[i][k];
                }
            }
        }
        GrafoMatriz *aux = G1;
        G1 = G2;
        G2 = aux;
    }
    delete G2;
    GrafoMatriz result = *G1;
    delete G1;
    bool hayCicloNeg = false;
    list<int> list_cam;
    for (int l = 0; l < n and !hayCicloNeg; ++l) { //Chequeo la diagonal para ver si hay ciclos negativos
        if (result[make_pair(l, l)] < 0) { //Si los hay, busco el construir_circuito
            hayCicloNeg = true;
            list_cam = construir_circuito(l, proximo); // OJO QUE ACA NO SE SI TERMINA PORQUE PODRIA ENTRAR EN UN CICLO SIN FIN
        }
    }
    return make_pair(hayCicloNeg, list_cam);
}