//
// Created by nahuel on 14/05/19.
//
//updated by ricardo

#include "dijkstra_prioridad.h"

 
vector<Precio> dijkstra_prioridad(Grafo &G, Vertice orig){
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
  
    //cola de prioridad para almacenar los vertices que estan siendo preprocesados
    set< pair<int, int> > candidatos; 

    //agregamos tupla de costo y nodo, empezando por el origen
    candidatos.insert(make_pair(0, orig)); 
    Vertice min;
     int index = 0;
     int iter = 1;
    while( iter <= 3*n-1){
        // En cada iteración "costos" da lo dicho anteriormente pero con caminos de longitud a lo sumo "longit"
        // (si no consideramos que los valores se pisan. Como sí se pisan, la semantica de "costos" es complicada).
        
        //agarrar el vertice de minima distancia desde el conjunto de vertices no aun
        //procesados. 
        pair<int, int> tmp    ;  
        if(candidatos.empty() ){
            if (iter < n+1){
                iter++;
                continue;
            }
        }

        
        if(n < iter && iter <= 2*n){
            candidatos.insert(make_pair(costos[index][0], index));
              
            elegidos[index] = false;
            index++;
            iter++;
            continue;
        }
        tmp = *(candidatos.begin()); 
            //borramos de cola para no volver a usarlo
        candidatos.erase(candidatos.begin());

        //borramos de cola para no volver a usarlo
         //vertice elegido
        min = tmp.ciudad; 
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
                        if(destino != orig &&  litros_min == a.litros && elegidos[destino] == false){                           
                            if (costos[destino][0] != MAX_PRECIO)
                                candidatos.erase(candidatos.find(make_pair(costos[destino][0], destino)));
                                
                            candidatos.insert(make_pair(costos[min][litros_min], destino));  
                             
                        }
                        if(destino != orig || litros_min != a.litros)
                            costos[destino][litros_min - a.litros] = costos[min][litros_min];
                            
                    }
                }

        }
        iter++;
    }
    vector<Precio> res = vector<Precio>(G.size());
    for(Vertice v = 0; v < costos.size(); ++v) res[v] = costos[v][0];
    return res;
}



 
/*
//se invoca algoritmo de dijkstra modificado para cada nodo del grafo
void dijkstra_priorid(Grafo &region){
    for(int src = 0; src < region.size(); src++){
        int vecino = 0;
        vector<Precio> res = dijkstra_prioridad(region, src);
        
        for(auto it = res.begin(); it != res.end(); it++){
            cout<<src<<" "<<vecino<<" "<<*it<<endl;
            vecino++;
        }
    }
}
*/
 
