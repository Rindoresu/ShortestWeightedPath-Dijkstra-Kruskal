#include "segmentation.cpp"
#include <iostream>

#define k 150


int main() {
    unsigned int w,h;
    cin >> w;
    cin >> h;
    vector<vector<int> > image(h,vector<int>(w,0));
    for(unsigned int i = 0; i < h; i++) {
        for(unsigned int j = 0; j < w; j++) {
            cin >> image[i][j];
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

    GrafoLista G(graphSize, aristas);
    GrafoLista tree_lista = kruskal_tree(G,k);
    GrafoAdyacencias T(graphSize);
    for(auto e : tree_lista) { //Amortizado O(n+n) (recordemos tenemos n aristas)
        T[e.first.first].push_back(e.first.second);
        T[e.first.second].push_back(e.first.first);
    }

    vector<int> componentes = BFS(T);

    for(unsigned int i = 0; i < h; i++) {
        for(unsigned int j = 0; j < w - 1; j++) {
            cout << componentes[i*w+j] << ", "; //image[i][j];
        }
        cout << componentes[i*w+w-1] << '\n';
    }

    return 0;
}