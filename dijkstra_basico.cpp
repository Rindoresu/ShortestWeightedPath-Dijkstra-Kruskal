//
// Created by nahuel on 14/05/19.
//
//updated by ricardo

#include "dijkstra_basico.h"


//funcion que devuelve el vertice de minima distancia del conjunto de vertices no
//incluidos aun en el camino minimo
Vertice minDistance(Matriz_litros &costos, vector< bool> &elegidos,  int n, int longit, int orig) 
{ 
  int min = MAX_PRECIO;
  Vertice min_index; 

  for (int v = 0; v < n; v++) {

    if (elegidos[v] == false && costos[v][0] <= min)
      min = costos[v][0], min_index = v; 
     if ( longit == n)
        elegidos[v] = false;
  }
  if (longit == n)
    return orig;
  return min_index; 
} 

vector<Precio> dijkstra_basico(Grafo &G, Vertice orig){
    Matriz_litros costos = Matriz_litros(G.size());    //Diccionario que toma como claves un vertice v y una cant. de litros lit
    // costos[v][lit] me dará el mínimo costo para llegar desde orig hasta v quedando lit litros en el tanque.
    for(Litro l = 0; l <= 60; ++l)              //
        for (Vertice v = 0; v < G.size(); ++v)  //Inicializo la matriz
            costos[v][l] = MAX_PRECIO;          //de costos por litro
    costos[orig][0] = 0;                        //

    int n = G.size();

    //este arreglo tendra true en posicion i si el vertice i esta incluido
    //en camino minimo desde src hacia i 
    vector<bool> elegidos(n,false);

    //list<Vertice> modificados; 
    Vertice min = orig;

    for(uint longit = 1; longit <= 2*G.size()-1  ; ++longit){
          
        //agarrar el vertice de minima distancia desde el conjunto de vertices no aun
        //procesados.  marcarlo como elegido       
        min =  minDistance(costos, elegidos,n,longit,orig); 
        //marcamos al elegido para no volver a actualizar su costo
        elegidos[min] = true;
        
            for(Litro l = 1; l <= 60; ++l)                                              //Actualizo los precios
                if (costos[min][l] > costos[min][l - 1] + G[min].precio)    //en "min" fijándome
                    costos[min][l] = costos[min][l - 1] + G[min].precio;    //si me conviene cargar acá.
            
            


        for(SemiArista a : G[min].vecinos) { Vertice& destino = a.llegada;  //Uso un nombre más cómodo que "a.llegada" para el vértice.
                 
                Litro litros_min = a.litros;  //necesitamos como minimo el consumo de la arista que vamos a usar.
                for (litros_min; litros_min <= 60; ++litros_min) {
                    if ( costos[destino][litros_min - a.litros] > costos[min][litros_min]) {
                         
                        //para cada vecino w del minimo, si fue elegido entonces no actualizamos
                        //su distancia final: costos[w][0], pues esta es la minima posible desde src segun dijkstra
                        //pero actualizamos los otros costos
                        if(destino != orig || litros_min != a.litros)
                            costos[destino][litros_min - a.litros] = costos[min][litros_min];
                            
                    }
                }

        }

    }

          vector<Precio> res = vector<Precio>(G.size());
    for(Vertice v = 0; v < costos.size(); ++v) res[v] = costos[v][0];
    return res;
}

/*
//se invoca algoritmo de dijkstra modificado para cada nodo del grafo
void camino_min_dijkstra_basic(Grafo &region){
    for(int src = 0; src < region.size(); src++){
        int vecino = 0;
        vector<Precio> res = dijkstra_basico(region, src);
        
        for(auto it = res.begin(); it != res.end(); it++){
            cout<<src<<" "<<vecino<<" "<<*it<<endl;
            vecino++;
        }
    }
}

*/

 
