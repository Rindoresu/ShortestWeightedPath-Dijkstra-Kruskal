//
// Created by nahuel on 14/05/19.
//

#include "camino minimo todos a todos.h"

vector<Precio> BellmanFord(Grafo &G, Vertice orig){
    Matriz_litros costos = Matriz_litros(G.size());    //Diccionaro que toa como claves un vertice v y una cant. de litros lit
    // costos[v][lit] me dará el mínimo costo para llegar desde orig hasta v quedando lit litros en el tanque.
    for(Litro l = 0; l <= 60; ++l)              //
        for (Vertice v = 0; v < G.size(); ++v)  //Inicializo la matriz
            costos[v][l] = MAX_PRECIO;          //de costos por litro
    costos[orig][0] = 0;                        //

    list<Vertice> modificados = {orig};
    bool* esta_en_modificados = new bool[G.size()] {};    //Este array indica que vertices están en "modificados" para agregar en O(1). Con "{}" se inicializa en false para todas las posiciones.
    esta_en_modificados[orig] = true;
    for(uint longit = 1; longit <= 2*(G.size() - 1) && not modificados.empty(); ++longit){
        // En cada iteración "costos" da lo dicho anteriormente pero con caminos de longitud a lo sumo "longit"
        // (si no consideramos que los valores se pisan. Como sí se pisan, la semantica de "costos" es complicada).
        auto it = modificados.begin();
        auto end = modificados.end();
        while(it != end){ Vertice& partida = *it;                                   //Uso un nombre más cómodo que "*it" para el vértice.

            for(Litro l = 1; l <= 60; ++l)                                              //Actualizo los precios
                if (costos[partida][l] > costos[partida][l - 1] + G[partida].precio)    //en "partida" fijándome
                    costos[partida][l] = costos[partida][l - 1] + G[partida].precio;    //si me conviene cargar acá.

            for(SemiArista a : G[partida].vecinos) { Vertice& destino = a.llegada;  //Uso un nombre más cómodo que "a.llegada" para el vértice.
                bool cambio_para_algun_litro = false;
                Litro litros_partida = a.litros;	//necesitamos como minimo el consumo de la arista que vamos a usar.
                for (litros_partida; litros_partida <= 60; ++litros_partida) {
                    if (costos[destino][litros_partida - a.litros] > costos[partida][litros_partida]) {
                        costos[destino][litros_partida - a.litros] = costos[partida][litros_partida];
                        cambio_para_algun_litro = true;
                    }
                }

                if(cambio_para_algun_litro && not esta_en_modificados[destino]) {   //Actualizo "modificados"
                    esta_en_modificados[destino] = true;                            //y "esta_en_modificados"
                    modificados.push_front(destino);                            //Hago push_front para que no se cuelgue si hay ciclos negativos.
                }
            }
            it = modificados.erase(it); esta_en_modificados[partida] = false;  //Análogo a "cambio = false".
        }
    }
    delete[] esta_en_modificados;
    vector<Precio> res = vector<Precio>(G.size());
    for(Vertice v = 0; v < costos.size(); ++v) res[v] = costos[v][0];
    return res;
}

vector<vector<Precio> > FloyWarshall(Grafo &G){
    vector<vector<vector<vector<Precio> > > > C_v_w_E_T(G.size(), vector<vector<vector<Precio> > >(G.size(), vector<vector<Precio> >(61, vector<Precio>(61, MAX_PRECIO))));  //Matriz que en la entrada M[v][w][e][t] contiene en cada paso el mínimo COSTO de ir de v hasta w EMPEZANDO con e litros y TERMINANDO con t litros

    for(Vertice partida = 0; partida < G.size(); ++partida){
        for(Litro lts_empi = 0; lts_empi <= 60; ++lts_empi)
            for (Litro lts_term = lts_empi; lts_term <= 60; ++lts_term)
                C_v_w_E_T[partida][partida][lts_empi][lts_term] = (lts_term - lts_empi) * G[partida].precio;

        for(SemiArista a : G[partida].vecinos){ Vertice& destino = a.llegada;
            if(G[partida].precio < G[destino].precio)
                for(Litro lts_empi = 0; lts_empi <= 60; ++lts_empi){
                    for(Litro lts_term = max(lts_empi - a.litros, 0); lts_term <= 60; ++lts_term) {
                        Litro lts_rec_par = min(lts_term + a.litros - lts_empi, 60) - lts_empi; //Litros que se recargan en "partida". Como "partida" es más barato, se recarga allí todoo lo posible.
                        Litro lts_rec_des = max(0, lts_term - (60 - a.litros));                 //Litros que se recargan en "destino". Si cargando en el max en "partida" no se pude alcanzar ltr_term, se recarga en "destino".
                        C_v_w_E_T[partida][destino][lts_empi][lts_term] = (lts_rec_par * G[partida].precio) + (lts_rec_des * G[destino].precio);
                    }
                }
            else
                for(Litro lts_empi = 0; lts_empi <= 60; ++lts_empi){
                    Litro lts_rec_par = max(a.litros - lts_empi, 0);    //Litros que se recargan en "partida". Como "destino" es más barato, sólo se recarga lo necesario para llegar.
                    Litro lts_qdn_des = max(lts_empi - a.litros, 0);    //Litros que me quedan al llegar a "destino".
                    for(Litro lts_term = lts_qdn_des; lts_term <= 60; ++lts_term)
                        C_v_w_E_T[partida][destino][lts_empi][lts_term] = lts_rec_par * G[partida].precio + (lts_term - lts_qdn_des) * G[destino].precio;
                }
        }
    }

    for(Vertice interno = 0; interno < G.size(); ++interno)
        for(Vertice partida = 0; partida < G.size(); ++partida)
            for(Vertice destino = 0; destino < G.size(); ++destino)
                for(Litro lts_empi = 0; lts_empi <= 60; ++lts_empi)
                    for(Litro lts_inte = 0; lts_inte <= 60; ++lts_inte) //Litros con los que termino en "interno", y con los que empiezo en "interno".
                        for(Litro lts_term = 0; lts_term <= 60; ++lts_term)
                            if (C_v_w_E_T[partida][destino][lts_empi][lts_term] > C_v_w_E_T[partida][interno][lts_empi][lts_inte] + C_v_w_E_T[interno][destino][lts_inte][lts_term])
                                C_v_w_E_T[partida][destino][lts_empi][lts_term] = C_v_w_E_T[partida][interno][lts_empi][lts_inte] + C_v_w_E_T[interno][destino][lts_inte][lts_term];

    vector<vector<Precio> > res(G.size(), vector<Precio>(G.size()));
    for(Vertice v = 0; v < G.size(); ++v)
        for(Vertice w = 0; w < G.size(); ++w)
            res[v][w] = C_v_w_E_T[v][w][0][0];

    return res;
}