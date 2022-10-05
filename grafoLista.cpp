#include "grafoLista.h"


GrafoLista::GrafoLista() {
    size=0;
}

GrafoLista::GrafoLista(size_t n) : size(n) {}

GrafoLista::GrafoLista(size_t n, const vector<pair<pair<unsigned int, unsigned int>, double> > &vec) {
    size = n;
    listAristas = vec;
}

void GrafoLista::agregar_arista(const pair<pair<unsigned int, unsigned int>, double> &p) {
    listAristas.push_back(p);
}

size_t GrafoLista::cantNodos() const {
    return size;
}

size_t GrafoLista::cantEjes() const {
    return listAristas.size();
}

vector< pair< pair<unsigned int, unsigned int>, double> >::const_iterator GrafoLista::begin() const {
    return listAristas.begin();
}

vector< pair< pair<unsigned int, unsigned int>, double> >::const_iterator GrafoLista::end() const {
    return listAristas.end();
}

vector< pair< pair<unsigned int, unsigned int>, double> > GrafoLista::devolver_vector() const {
    return listAristas;
}
