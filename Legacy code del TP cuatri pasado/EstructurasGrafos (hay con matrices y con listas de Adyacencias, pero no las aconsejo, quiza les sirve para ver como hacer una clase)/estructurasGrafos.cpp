#include "estructurasGrafos.h"

GrafoMatriz::GrafoMatriz(size_t cantNodos) : M(vector<vector<double> >(cantNodos, vector<double>(cantNodos, 0))) {
    for(int i = 0; i<cantNodos; i++) {
        for(int j = 0; j<cantNodos; j++) {
            M[i][j] = numeric_limits<double>::infinity();
        }
    }
}
/*
GrafoMatriz GrafoMatriz::distancias(unsigned int cantNodos) {
    for(int i = 0; i<cantNodos; i++) {
        for(int j = 0; j<cantNodos; j++) {
            M[i][j] = i==j ? 0 : numeric_limits<double>::infinity();
        }
    }
}*/

GrafoMatriz::GrafoMatriz(const vector<vector<double> > & matriz_ady) : M(matriz_ady) {}

size_t GrafoMatriz::cantNodos() const {
    return M.size();
}

bool GrafoMatriz::hayArista(const pair<unsigned int, unsigned int> &p) const {
    bool result;
    result = M[p.first][p.second] == numeric_limits<double>::infinity();
    return result;
}

double GrafoMatriz::peso(const pair<unsigned int, unsigned int> &p) const {
    return M[p.first][p.second];
}

double& GrafoMatriz::operator[](const pair<unsigned int, unsigned int> &p) {
    return  M[p.first][p.second];
}

GrafoLista::GrafoLista() : tamano(0), listAristas(list< pair< pair<unsigned int, unsigned int>, double> >()) {}


GrafoLista::GrafoLista(size_t n) : tamano(n), listAristas() {}


GrafoLista::GrafoLista(size_t n, const list<pair<pair<unsigned int, unsigned int>, double> > &list) : tamano(n),
                                                                                                      listAristas(list){}

void GrafoLista::agregar_arista(const pair<pair<unsigned int, unsigned int>, double> &p) {
    listAristas.push_back(p);
}

size_t GrafoLista::cantNodos() const {
    return tamano;
}

size_t GrafoLista::cantEjes() const {
    return listAristas.size();
}

list< pair< pair<unsigned int, unsigned int>, double> >::const_iterator GrafoLista::begin() const {
    return listAristas.cbegin();
}

list< pair< pair<unsigned int, unsigned int>, double> >::const_iterator GrafoLista::end() const {
    return listAristas.cend();
}

list< pair< pair<unsigned int, unsigned int>, double> > GrafoLista::devolver_lista() const {
    return list<pair<pair<unsigned int, unsigned int>, double> >(listAristas);
}

vector< pair< pair<unsigned int, unsigned int>, double> > GrafoLista::devolver_vector() const {
    vector<pair<pair<unsigned int, unsigned int>, double> > result(listAristas.size());
    auto iterator = listAristas.begin();
    int i = 0;
    while(iterator != listAristas.end()) {
        result[i].first.first = iterator->first.first;
        result[i].first.second = iterator->first.second;
        result[i].second = iterator->second;
        iterator++;
        i++;
    }

    return result;
}
