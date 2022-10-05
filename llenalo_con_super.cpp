using namespace std;
#include <iostream>
#include <vector>
#include <chrono>
#include "camino minimo todos a todos.h"
#include "dijkstra_prioridad.h"
#include "dijkstra_basico.h"
 

void medir_tiempo2(Grafo &region ,vector<vector<Precio> >  (*funcion)(Grafo &G)) {
    vector<double> arrayT;
    
    auto tiempoAntes = chrono::steady_clock::now();
    
    funcion(region);
    
    
    auto tiempoDespues = chrono::steady_clock::now();

    auto tiempoTardado = tiempoDespues - tiempoAntes;
    auto res = chrono::duration <double, milli> (tiempoTardado).count();
   
   
    cout<<  res;

}

void medir_tiempo(Grafo &region ,vector<Precio> (*funcion)(Grafo &G, Vertice orig)) {
	vector<double> arrayT;
	
	auto tiempoAntes = chrono::steady_clock::now();
    
        for(int h=0; h<region.size(); h++)
    	   funcion(region,h);
    
    
    auto tiempoDespues = chrono::steady_clock::now();

    auto tiempoTardado = tiempoDespues - tiempoAntes;
    auto res = chrono::duration <double, milli> (tiempoTardado).count();
   
   
    cout<<  res;

    if(*funcion != dijkstra_prioridad)
    	cout << " ,";
}

void quiero_soluciones(int nodos){
    int ejes;
    cin >> ejes;

   Grafo  region(nodos);
  
  //leemos ciudades
  for(int i = 0; i < nodos; ++i){
        int precio; cin >> precio;
        region[i].precio = precio;
  }
  //armamos ejes
  for(int i = 0; i < ejes; ++i) {

        int v, w, lt; cin >> v >> w >> lt;
        SemiArista nueva1,nueva2;
        nueva1.llegada = w;
        nueva1.litros = lt;
        nueva2.llegada = v;
        nueva2.litros = lt;
        region[v].vecinos.push_back(nueva1);
        region[w].vecinos.push_back(nueva2);
  }
    cout<<"dijkstra_basico: "<<endl;
    for(int j=0; j< nodos; j++){
        vector<Precio> res = dijkstra_basico(region,j);
        for(int i = 0; i < region.size(); i++){
            cout <<j<<" "<<i<<" "<<res[i]<<endl;
        }
    }
    
    
    
    cout<<"dijkstra_prioridad: "<<endl;
    for(int j=0; j< nodos; j++){
        vector<Precio> res = dijkstra_prioridad(region,j);
        for(int i = 0; i < region.size(); i++){
            cout <<j<<" "<<i<<" "<<res[i]<<endl;
        }
    }
    cout<<"bellman_ford: "<<endl;
    for(int j=0; j< nodos; j++){
        vector<Precio> res = dijkstra_prioridad(region,j);
        for(int i = 0; i < region.size(); i++){
            cout <<j<<" "<<i<<" "<<res[i]<<endl;
        }
    }
    cout<<"floyd_warshall: "<<endl;
    vector<vector<Precio> > res = FloyWarshall(region);
    int j  = 0;
    for(auto it = res.begin(); it != res.end(); it++){
        int vecino = 0;
         cout<<endl;
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            cout<<j<<" "<<vecino<<" "<<*it2<<endl;
            vecino++;
        }
        j++;
    }
}

void quiero_tiempos(){
    Grafo G; 
    int nodos, ejes;
    cin >> nodos >> ejes;
  Grafo  region(nodos);
  
  //leemos ciudades
  for(int i = 0; i < nodos; ++i){
        int precio; cin >> precio;
        region[i].precio = precio;
  }
  //armamos ejes
  for(int i = 0; i < ejes; ++i) {

        int v, w, lt; cin >> v >> w >> lt;
        SemiArista nueva1,nueva2;
        nueva1.llegada = w;
        nueva1.litros = lt;
        nueva2.llegada = v;
        nueva2.litros = lt;
        region[v].vecinos.push_back(nueva1);
        region[w].vecinos.push_back(nueva2);
  }

    cout << nodos << ", " << ejes <<",";
     
    medir_tiempo2(region, FloyWarshall);
    medir_tiempo(region, BellmanFord);
    medir_tiempo(region, dijkstra_basico);
    medir_tiempo(region, dijkstra_prioridad);

    cout << endl;
}


int main() {
    int n;
    cin >> n; 

    bool tiempos = n < 0;  
    //pide dato de entrada(int), si es menor a cero calcula los tiempos, si no, las soluciones para cada algoritmo

    if(tiempos){
        quiero_tiempos();
    } else {
        quiero_soluciones(n);
    }

    return 0;
}
