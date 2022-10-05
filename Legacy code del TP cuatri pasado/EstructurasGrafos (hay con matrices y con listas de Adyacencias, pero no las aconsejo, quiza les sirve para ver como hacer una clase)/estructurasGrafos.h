#ifndef ALGO_3_TP2_ESTRUCTURASGRAFOS_H
#define ALGO_3_TP2_ESTRUCTURASGRAFOS_H

#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <cmath>

using namespace std;

/* NOTA IMPORTANTE, CLUSTERES ES GRAFO NO DIRIGIDO, ARBITRAJE ES GRAFO DIRIGIDO,
 * para los grafos matriz no dirigidos tenemos que mantener una matriz simétrica (si asignamos en la fila i columna j, tambien debemos hacerlo para la fila j, columna i).
 * Para listas si es no dirigido tenemos que chequear si el par (i,j) o el par (j,i) esta en la lista en TODAS LAS COMPARACIONES.*/
//Permite construir Digrafos y pseudografos, usar con precaucion.
class GrafoMatriz {

public:
    /*
     * Constructor por defecto sin nodos.
     */
    GrafoMatriz() = default;
    /*
     * Constructor por copia por defecto.
     */
    GrafoMatriz(const GrafoMatriz&) = default;

    /*
     * Asignacion por defecto
     */
    GrafoMatriz& operator=(const GrafoMatriz&) = default;

    /*
     * Constructor dado una cantidad de nodos.
     */
    explicit GrafoMatriz(size_t cantNodos);

    explicit GrafoMatriz(const vector<vector<double> >& matriz_ady);

    /*
     * Si hay arista (si no vale infinito) es verdadero, si no, (si vale infinito) es falso.
     */
    bool hayArista(const pair<unsigned int, unsigned int>& p) const;

    /*
     * Si hay arista devuelve su peso, si no la hay, devuelve infinito.
     */
    double peso(const pair<unsigned int, unsigned int>& p) const;

    /*
     * Devuelve el peso (o infinito si no hay arista) de la arista, y permite modificar su valor.
     */
    double & operator[](const pair<unsigned int, unsigned int>& p);

    size_t cantNodos() const;


private:
    vector<vector<double> > M;
};


//Permite construir Digrafos y pseudografos, usar con precaucion. PARA GRAFOS NO DIRIGIDOS, SOLO SE INCLUYE UNA ARISTA (CHEQUEAR LA ARISTA INVERSA TAMBIEN).
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
    GrafoLista(size_t n, const list<pair<pair<unsigned int, unsigned int>, double> > &list);

    /*
     * Asignacion por defecto
     */
    GrafoLista& operator=(const GrafoLista&) = default;

    void agregar_arista(const pair< pair<unsigned int, unsigned int>, double>& p);

    size_t cantNodos() const;

    size_t cantEjes() const;

    list< pair< pair<unsigned int, unsigned int>, double> >::const_iterator begin() const;

    list< pair< pair<unsigned int, unsigned int>, double> >::const_iterator end() const;


    list< pair< pair<unsigned int, unsigned int>, double> > devolver_lista() const;

    vector< pair< pair<unsigned int, unsigned int>, double> > devolver_vector() const;

private:
    size_t tamano; //Cantidad de vertices en el grafo.
    /*
     * Única lista de adyacencias donde el par interno indica de donde y a donde va la arista, (dirigido).
     * Y el double indica el peso de la arista.
     */
    list< pair< pair<unsigned int, unsigned int>, double> > listAristas;
};


#endif //ALGO_3_TP2_ESTRUCTURASGRAFOS_H
