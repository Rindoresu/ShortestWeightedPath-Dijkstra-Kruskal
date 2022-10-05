#ifndef ALGORITMOS3_TP2_GRAFOLISTA_H
#define ALGORITMOS3_TP2_GRAFOLISTA_H

#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

class GrafoLista {

public:
    /*
     * Constructor por defecto de grafo sin nodos.
     */
    GrafoLista();
    /*
     * Constructor por defecto copia de otro grafo.
     */
    GrafoLista(const GrafoLista&) = default;

    /*
     * Constructor por defecto dado una cantidad de nodos construye un grafo sin aristas.
     */
    explicit GrafoLista(size_t n);

    /*
     * Constructor por defecto dado una cantidad de nodos y algunas adyacencias en el grafo.
     */
    GrafoLista(size_t n, const vector<pair<pair<unsigned int, unsigned int>, double> > &vec);

    /*
     * Asignacion por defecto
     */
    GrafoLista& operator=(const GrafoLista&) = default;

    void agregar_arista(const pair< pair<unsigned int, unsigned int>, double>& p);

    size_t cantNodos() const;

    size_t cantEjes() const;

    vector< pair< pair<unsigned int, unsigned int>, double> >::const_iterator begin() const;

    vector< pair< pair<unsigned int, unsigned int>, double> >::const_iterator end() const;

    vector< pair< pair<unsigned int, unsigned int>, double> > devolver_vector() const;

    template< class Compare >
    void sortGrafo(Compare comp);


private:
    size_t size; //Cantidad de vertices en el grafo.
    /*
     * Única lista de adyacencias donde el par interno indica de donde y a donde va la arista, (dirigido).
     * Y el double indica el peso de la arista.
     */
    vector< pair< pair<unsigned int, unsigned int>, double> > listAristas;
};

template < class Compare >
void GrafoLista::sortGrafo(Compare comp) {
    std::sort(listAristas.begin(),listAristas.end(),comp);
}

#endif //ALGORITMOS3_TP2_GRAFOLISTA_H
