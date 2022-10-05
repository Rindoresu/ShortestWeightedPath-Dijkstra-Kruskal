#include "segmentation.cpp"
#include <fstream>
#include <iostream>

//#define k 10000
#define algoritmoUsado 2 // 0 = Kruskal Arreglo, 1 = KruskalDST, 2 = KruskalPC
#define output_file "./Output/SinEasyK"
#define input_file "./EasySin"


int main() {
    unsigned int w,h;
    string esPGM;
    ifstream input(input_file);
    input >> esPGM; //Esto lo hago porque PGM tiene un "P5" que no me importa pero no quiero andar borrando manualmente de cada archivo.
    input >> esPGM;
    input >> esPGM;
    input >> esPGM;
    input >> esPGM;
    input >> esPGM;
    input >> esPGM;
    input >> esPGM;
    input >> w;
    input >> h;
    input >> esPGM;
    char a = 0;
    input.get(a);

    /*cin >> esPGM; //Esto lo hago porque PGM tiene un "P5" que no me importa pero no quiero andar borrando manualmente de cada archivo.
    cin >> esPGM;
    cin >> w;
    cin >> h;
    cin >> esPGM;*/ //Tambien tiene una linea con el valor maximo que siempre voy a dejar como 255.
    vector<vector<uint8_t> > image(h,vector<uint8_t>(w,0));
    for(unsigned int i = 0; i < h; i++) {
        for(unsigned int j = 0; j < w; j++) {
            char n = 0;
            //cin.get(n);
            input.get(n);
            image[i][j] = n;
        }
    }
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
    vector<int> valoresK = {0, 1, 50, 150, 300, 500, 800, 1500, 3000, 10000};
    valoresK.push_back(graphSize/16);
    valoresK.push_back(graphSize/8);
    valoresK.push_back(graphSize/4);
    valoresK.push_back(graphSize/2);
    valoresK.push_back(graphSize);
    for(int k : valoresK) {
        ofstream file(output_file + to_string(k) + ".csv", fstream::trunc);
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

                for(unsigned int i = 0; i < h; i++) {
                    for(unsigned int j = 0; j < w - 1; j++) {
                        file << componentes[i*w+j] << ","; //image[i][j];
                    }
                    file << componentes[i*w+w-1] << '\n';
                }
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

                for (unsigned int i = 0; i < h; i++) {
                    for (unsigned int j = 0; j < w - 1; j++) {
                        file << componentes[i * w + j] << ","; //image[i][j];
                    }
                    file << componentes[i * w + w - 1] << '\n';
                }
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

                for (unsigned int i = 0; i < h; i++) {
                    for (unsigned int j = 0; j < w - 1; j++) {
                        file << componentes[i * w + j] << ","; //image[i][j];
                    }
                    file << componentes[i * w + w - 1] << '\n';
                }
                break;
            }
        }
    }



    return 0;
}