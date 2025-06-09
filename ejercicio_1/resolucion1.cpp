#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

struct arista {
    int tail;
    int head;
};

using grafo = vector<vector<int>>;

int n;                  // cantidad de nodos
int m;                  // cantidad de aristas
grafo G;                // lista de adyacencias
vector<arista> aristas; // lista de aristas

// si G es geodesico, guarda el camino minimo entre todo par de vertices
// si no, guarda dos caminos minimos distintos entre algun par de vertices
vector<vector<int>> caminos;

void BFS(int s, vector<int>& dist, vector<int>& pred) {
    queue<int> Q;
    vector<bool> visitado(n, false);

    Q.push(s);
    visitado[s] = true;
    pred[s] = s;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (int w : G[v]) {
            if (!visitado[w]) {
                dist[w] = dist[v] + 1;
                pred[w] = v;
                Q.push(w);
                visitado[w] = true;
            }
        }
    }
}

bool geodesico() {
    vector<vector<int>> distancias(n);    // distancias[v][w] = distancia de v a w
    vector<vector<int>> predecesores(n);  // predecesores[v] = arbol BFS de v

    // BFS para cada v
    for (int v = 0; v < n; v++) {
        distancias[v].assign(n, 0);
        predecesores[v].assign(n, -1);
        BFS(v, distancias[v], predecesores[v]);
    }

    // para cada v, chequeamos si hay dos caminos minimos desde el
    bool es_geodesico = true;
    int origen;
    arista arista_alternativa;
    for (int v = 0; v < n; v++) {
        for (arista e : aristas) {
            if (predecesores[v][e.head] != e.tail &&
                distancias[v][e.head] == distancias[v][e.tail] + 1) {
                    es_geodesico = false;
                    origen = v;
                    arista_alternativa = e;
            }
        }
    }

    if (!es_geodesico) {
        vector<int> camino;
        
        // camino del arbol
        int nodo = arista_alternativa.head;
        while (nodo != origen) {
            camino.push_back(nodo);
            nodo = predecesores[origen][nodo];
        }
        camino.push_back(origen);
        caminos.push_back(camino);
        camino.clear();

        // camino alternativo
        camino.push_back(arista_alternativa.head);
        nodo = arista_alternativa.tail;
        while (nodo != origen) {
            camino.push_back(nodo);
            nodo = predecesores[origen][nodo];
        }
        camino.push_back(origen);
        caminos.push_back(camino);
    } else {
        caminos = predecesores;
    }

    return es_geodesico;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

/* -- leemos la instancia -- */
    cin >> n >> m;
    
    G.assign(n, vector<int>());
    aristas.assign(m, {0, 0});

    int t;
    int h;
    for (int i = 0; i < m; i++) {
        cin >> t >> h;
        G[t].push_back(h);
        G[h].push_back(t);
        aristas[i] = {t, h};
    }

/* -- llamamos a la funcion -- */
    auto start = chrono::steady_clock::now();

    bool res = geodesico();

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

/* -- escribimos el resultado en consola -- */
    cout << res << endl;

    for (auto camino : caminos) {
        for (int v : camino) {
            cout << v << " ";
        }
        cout << endl;
    }

/* -- guardamos los tiempos -- */
    string filename = "./resultados/tiempos.txt";
    fstream fs;
    fs.open(filename, ios::app);
    fs << n << ", " << m << ", " << res << ", " << total_time << "\n";
    fs.close();

    return 0;
}
