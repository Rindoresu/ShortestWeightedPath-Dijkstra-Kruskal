#include "segmentation.cpp"
#include <iostream>
#include <chrono>

#define k 150
#define algoritmoUsado 1 // 0 = Kruskal Arreglo, 1 = KruskalDST, 2 = KruskalPC
#define totalRepes 50



int main() {
    unsigned int step = 10;
    unsigned int max_h = 150;
    unsigned int max_w = 300;
    vector<pair<int, double> > tiempos(max_w/step, pair<int, double> (0,-1));
    for(unsigned int test = 1; test <= max_w/step; test++) {
        unsigned int w,h;
        w = test*step;
        h = max_h;
        int n = h*w;
        tiempos[test-1].first = n;

        vector<vector<uint8_t> > image(h,vector<uint8_t>(w,0));
        /*for(unsigned int i = 0; i < h; i++) {
            for(unsigned int j = 0; j < w; j++) {
                cin >> image[i][j];
            }
        }*/


        for (int repe = 0; repe < totalRepes; ++repe) {
            chrono::steady_clock::time_point t0;
            chrono::steady_clock::time_point t1;
            t0 = chrono::steady_clock::now();


            size_t graphSize = h*w;
            vector<pair<pair<unsigned int, unsigned int>, double> > aristas;
            aristas.reserve(h*w*4);
            for(unsigned int i = 0; i < h; i++) {
                for(unsigned int j = 0; j < w; j++) {
                    if(j < w-1) {
                        aristas.emplace_back(make_pair(make_pair(i*w+j,i*w+j+1), abs(image[i][j] - image[i][j+1])));
                    }
                    if(j < w-1 and i < h-1) {
                        aristas.emplace_back(make_pair(make_pair(i*w+j,(i+1)*w+j+1), abs(image[i][j] - image[i+1][j+1])));
                    }
                    if(i < h-1) {
                        aristas.emplace_back(make_pair(make_pair(i*w+j,(i+1)*w+j), abs(image[i][j] - image[i+1][j])));
                    }
                    if(j > 0 and i < h-1) {
                        aristas.emplace_back(make_pair(make_pair(i*w+j,(i+1)*w+j-1), abs(image[i][j] - image[i+1][j-1])));
                    }
                }
            }
            switch(algoritmoUsado) {
                case 0 : {
                    GrafoLista G(graphSize, aristas);
                    GrafoLista tree_lista = kruskal_vector(G,k);
                    GrafoAdyacencias T(graphSize);
                    for(auto e : tree_lista) { //Amortizado O(n+n) (recordemos tenemos n aristas)
                        T[e.first.first].push_back(e.first.second);
                        T[e.first.second].push_back(e.first.first);
                    }

                    vector<int> componentes = BFS(T);
                    /*GrafoLista G(graphSize, aristas);
                    pair<GrafoLista, vector<int> > p = kruskal_vector(G, k);
                    vector<int> &componentes = p.second;*/
                    /*for (unsigned int i = 0; i < h; i++) {
                        for (unsigned int j = 0; j < w - 1; j++) {
                            cout << componentes[i * w + j] << ", "; //image[i][j];
                        }
                        cout << componentes[i * w + w - 1] << '\n';
                    }*/
                    break;
                }
                case 1 : {
                    GrafoLista G(graphSize, aristas);
                    GrafoLista tree_lista = kruskal_tree(G, k);
                    GrafoAdyacencias T(graphSize);
                    for (auto e : tree_lista) { //Amortizado O(n+n) (recordemos tenemos n aristas)
                        T[e.first.first].push_back(e.first.second);
                        T[e.first.second].push_back(e.first.first);
                    }

                    vector<int> componentes = BFS(T);

                    /*for (unsigned int i = 0; i < h; i++) {
                        for (unsigned int j = 0; j < w - 1; j++) {
                            cout << componentes[i * w + j] << ", "; //image[i][j];
                        }
                        cout << componentes[i * w + w - 1] << '\n';
                    }*/
                    break;
                }
                case 2 : {
                    GrafoLista G(graphSize, aristas);
                    GrafoLista tree_lista = kruskal_path_compression(G, k);
                    GrafoAdyacencias T(graphSize);
                    for (auto e : tree_lista) { //Amortizado O(n+n) (recordemos tenemos n aristas)
                        T[e.first.first].push_back(e.first.second);
                        T[e.first.second].push_back(e.first.first);
                    }

                    vector<int> componentes = BFS(T);

                    /*for (unsigned int i = 0; i < h; i++) {
                        for (unsigned int j = 0; j < w - 1; j++) {
                            cout << componentes[i * w + j] << ", "; //image[i][j];
                        }
                        cout << componentes[i * w + w - 1] << '\n';
                    }*/
                    break;
                }
            }

            t1 = chrono::steady_clock::now();

            double delta_t = chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();

            if(tiempos[test-1].second == -1 or tiempos[test-1].second > delta_t) {
                tiempos[test-1].second = delta_t;
            }
        }

    }
    cout << "n,Tiempo" << '\n';
    for (unsigned int test = 1; test <= max_w/step; test++) {
        cout << tiempos[test-1].first << ',' << tiempos[test-1].second << '\n';
    }


    return 0;
}