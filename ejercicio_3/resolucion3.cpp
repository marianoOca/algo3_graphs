#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

using peso = int;
using distancia = int;
using nodo = int;

const distancia INF = 1e9;

struct arista {
    nodo fuente;
    nodo destino;

    bool operator<(const arista &o) const {
        return fuente < o.fuente || fuente == o.fuente && destino < o.destino;
    }
};

struct grafo {
    vector<nodo> V;
    vector<arista> E;
    vector<vector<nodo>> Adj;
};

int n;                  // cantidad de nodos
int m;                  // cantidad de aristas

grafo computarGPrima(grafo, map<arista, peso>&);
bool bellmanFord(grafo&, map<arista, peso>&, nodo s, vector<distancia>& d, vector<nodo>& cicloNeg);
void dijkstra(grafo&, map<arista, peso>& w, nodo s, vector<distancia>& d);

bool johnson(grafo G, map<arista, peso> w, vector<vector<distancia>>& D, vector<nodo>& cicloNeg) {
    grafo Gprima = computarGPrima(G, w);
    nodo s = n;

    vector<distancia> distanciasHastaS(n+1);
    if (!bellmanFord(Gprima, w, s, distanciasHastaS, cicloNeg)) {
        return false;
    }

    map<arista, peso> wNueva;
    for (arista e : Gprima.E)
        wNueva[e] = w[e] + distanciasHastaS[e.fuente] - distanciasHastaS[e.destino];

    for (nodo u : G.V) {
        vector<distancia> distanciasHastaU(n+1);
        dijkstra(G, wNueva, u, distanciasHastaU);
        for (nodo v : G.V) {
            D[u][v] = distanciasHastaU[v] + distanciasHastaS[v] - distanciasHastaS[u];
        }
    }

    return true;
}

// Agrega nuevo nodo al grafo, junto con una arista apuntando a cada nodo con peso 0.
grafo computarGPrima(grafo G, map<arista, peso>& w) {
    G.Adj.emplace_back();
    for (nodo i : G.V) {
        G.Adj[n].push_back(i);
        arista nuevaArista = {n, i};
        G.E.push_back(nuevaArista);
        w[nuevaArista] = 0;
    }
    G.V.push_back(n);

    return G;
}

void inicializarSssp(grafo& G, nodo s, vector<distancia>& d, vector<nodo>& pred);
bool relajar(nodo u, nodo v, map<arista, peso> w, vector<distancia>& d, vector<nodo>& p);
bool bellmanFord(grafo& G, map<arista, peso>& w, nodo s, vector<distancia>& distancias, vector<nodo>& cicloNeg) {
    vector<nodo> pred(G.V.size());
    inicializarSssp(G, s, distancias, pred);
    for (int i = 0; i < n+1; i++)
        for (arista e : G.E)
            relajar(e.fuente, e.destino, w, distancias, pred);
    for (arista e : G.E) {
        if (distancias[e.destino] > distancias[e.fuente] + w[e]) {
            cicloNeg.push_back(e.destino);
            for (nodo p = pred[e.destino]; p != e.destino; p = pred[p])
                cicloNeg.push_back(p);
            cicloNeg.push_back(e.destino);
            return false;
        }
    }
    return true;
}

void dijkstra(grafo& G, map<arista, peso>& w, nodo s, vector<distancia>& distancias) {
    vector<nodo> pred(G.V.size());
    inicializarSssp(G, s, distancias, pred);
    priority_queue<pair<distancia, nodo>, vector<pair<distancia, nodo>>, greater<>> Q;
    for (nodo v : G.V)
        Q.push({distancias[v], v});

    vector<bool> visitado(G.V.size(), false);

    while (!Q.empty()) {
        nodo u = Q.top().second;
        Q.pop();
        visitado[u] = true;

        for (nodo v : G.Adj[u])
            if (!visitado[v] && relajar(u, v, w, distancias, pred))
                Q.push({distancias[v], v});
    }
}

void inicializarSssp(grafo& G, nodo s, vector<distancia>& d, vector<nodo>& pred) {
    pred[s] = -1;
    for (nodo v : G.V)
        d[v] = INF;
    d[s] = 0;
}

bool relajar(nodo u, nodo v, map<arista, peso> w, vector<distancia>& d, vector<nodo>& pred) {
    peso p = w[{u, v}];
    if (d[v] > d[u] + p) {
        d[v] = d[u] + p;
        pred[v] = u;
        return true;
    }
    return false;
}

int main(void) {

    cin >> n >> m;
    vector<nodo> V(n);
    vector<arista> E(m);
    vector<vector<nodo>> Adj(n, vector<nodo>());
    map<arista, peso> w;

    for (int i = 0; i < n; i++) V[i] = i;

   int t, h, wt;
   for (int i = 0; i < m; i++) {
       cin >> t >> h >> wt;
       arista e = {t, h};
       E[i] = e;
       w[e] = wt;
       Adj[t].push_back(h);
   }

    grafo G = {V, E, Adj};
    vector<nodo> cicloNeg;
    vector<vector<distancia>> distancias(n, vector<distancia>(n));

    auto start = chrono::steady_clock::now();

    bool j = johnson(G, w, distancias, cicloNeg);

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

    cout << j << endl;
    if (j) {
        for (nodo v : V) {
            for (distancia d : distancias[v]) {
                if (d == INF) cout << "INF ";
                else cout << d << " ";
            }
            cout << endl;
        }
    } else {
        // recorrer cicloNeg al reves
        for (auto it = cicloNeg.rbegin(); it != cicloNeg.rend(); it++)
            cout << *it << " ";
    }

/* -- guardamos los tiempos -- */
    string filename = "./resultados/tiempos.txt";
    fstream fs;
    fs.open(filename, ios::app);
    fs << n << ", " << m << ", " << j << ", " << total_time << "\n";
    fs.close();

    return 0;
}
