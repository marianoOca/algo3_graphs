#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

const int INF = 1e9;

// tiene sentido en una lista de adyacencia, el origen es el vector al que pertenece la arista
struct arista {
    int destino;
    int peso;
};

struct intervalo {
    int inicio;
    int fin;
    int indice;
};

using nodo = pair<int, int>; // {costo desde v, nodo}

int n;
vector<intervalo> I;
vector<intervalo> I_copia;
vector<vector<arista>> D; // lista de adyacencias

void dijkstra(int v, vector<int>& dist, vector<int>& pred) {
    dist.assign(D.size(), INF);
    pred.assign(D.size(), -1);

    vector<bool> visitado(D.size(), false);

    priority_queue<nodo, vector<nodo>, greater<nodo>> Q;

    visitado[v] = true;
    dist[v] = 0;
    pred[v] = v;
    Q.push({0, v});

    for (int i = 0; i < D.size(); i++) {
        if(i != v) {
            dist[i] = INF;
            Q.push({INF, i});
        }
    }

    while (!Q.empty()) {
        int w = Q.top().second;
        Q.pop();
        visitado[w] = true;

        for (arista e : D[w]) {
            // e = w -> u
            // u = e.destino
            if (!visitado[e.destino]) {
                if (dist[e.destino] > dist[w] + e.peso) {
                    dist[e.destino] = dist[w] + e.peso;
                    pred[e.destino] = w;
                    Q.push({dist[e.destino], e.destino});
                }
            }
        }
    }
}

// ordena I segun inicio
void bucketSort() {
    vector<intervalo> vacio;
    vector<vector<intervalo>> buckets(2*n, vacio);
    for (intervalo i: I) buckets[i.inicio].push_back(i);
    I.clear();
    for (vector<intervalo> bucket: buckets) {
        for (intervalo i: bucket) I.push_back(i);
    }
}

// devuelve true si i esta contenido en j
bool contenido(intervalo i, intervalo j) {
    return j.inicio < i.inicio && i.fin < j.fin;
}

// devuelve true si hay una arista de tipo B de i a j
bool arista_B(intervalo i, intervalo j) {
    return j.inicio < i.fin && i.fin < j.fin;
}

// devuelve true si hay una arista de tipo C de i a j
bool arista_C(intervalo i, intervalo j) {
    if (i.fin < j.inicio) {
        bool res = true;
        int k = 0;
        while (res && k < I_copia.size()) {
            res = !contenido(I_copia[k], {i.fin, j.inicio, -1});
            k++;
        }
        return res;
    }
    return false;
}

int main(void) {

/* -- leemos la instancia -- */
    cin >> n;

    I.assign(n, {0, 0, 0});

    int s;
    int t;
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        I[i] = {s, t, i};
    }

/* -- guardamos una copia del conjunto de intervalos -- */
    I_copia = I;

/* -- ordenamos I segun inicio -- */
    auto start = chrono::steady_clock::now();
    bucketSort();

/* -- chequeamos si hay un intervalo que contiene a todos -- */
    int max_t = 0;
    for (int i = 0; i < I.size(); i++) {
        if (I[i].fin > I[max_t].fin) max_t = i;
    }

    if (max_t == 0) {
        auto end = chrono::steady_clock::now();
        double total_time = chrono::duration<double>(end - start).count();

    /* -- escribimos el resultado en consola -- */
        cout << "2" << endl;
        cout << I[max_t].indice << " " << I[1].indice << endl;

    /* -- guardamos los tiempos -- */
        string filename = "./resultados/tiempos.txt";
        fstream fs;
        fs.open(filename, ios::app);
        fs << n << ", " << total_time << "\n";
        fs.close();

        return 0;
    }

/* -- agregamos I_0 e I_n+1 -- */
    intervalo i = {I[max_t].fin + 1, I[max_t].fin + 2, -1};
    I.push_back(i);
    i = {I[0].inicio - 2, I[0].inicio - 1, -1};
    I.insert(I.begin(), i);

/* -- sacamos intervalos que esten contenidos en algun otro -- */
    for (auto i = I.begin(); i != I.end();) {
        auto j = I.begin();
        bool esta_contenido = false;
        while (!esta_contenido && j != I.end()) {
            esta_contenido = contenido(*i, *j);
            j++;
        }
        if (esta_contenido) I.erase(i);
        else i++;
    }

    n = I.size() - 2;

/* -- armamos el grafo -- */
    D.assign(2*n + 2, vector<arista>());
    arista e;

    // nodo impar representa i_in  -- i_in = 2i - 1
    // nodo par representa i_out   -- i_out = 2i

    // aristas que salen de i_0 y aristas que llegan a i_n+1
    for (int i = 1; i < I.size()-1; i++) {
        if (arista_C(I[0], I[i])) {
            e = {2*i, 0};
            D[0].push_back(e);
        }
        if (arista_C(I[i], I[n+1])) {
            e = {2*n+1, 1};
            D[2*i-1].push_back(e);
        }
    }

    // aristas entre intervalos de 1 a n
    for (int i = 1; i < I.size()-1; i++) {
        e = {2*i, 0};
        D[2*i-1].push_back(e);
        for (int j = i + 1; j < I.size()-1; j++) {
            if (arista_B(I[i], I[j])) {
                e = {2*j-1, 1};
                D[2*i].push_back(e);
            } else if (arista_C(I[i], I[j])) {
                e = {2*j, 1};
                D[2*i-1].push_back(e);
            }
        }
    }

/* -- buscamos el camino minimo de i_0 a i_n+1 -- */
    vector<int> dist, pred;
    dijkstra(0, dist, pred);

/* -- escribimos el resultado en consola -- */
    vector<int> camino; // de i_0 a i_n+1
    int v = pred[2*n + 1];
    while (v != 0) {
        camino.push_back(v);
        v = pred[v];
    }

    set<int> res;
    for (int x : camino) {
        if (x % 2 == 0) res.insert(x/2);
        else res.insert((x+1)/2);
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

    cout << res.size() << endl;
    for (int x : res) cout << I[x].indice << " ";
    cout << endl;

/* -- guardamos los tiempos -- */
    string filename = "./resultados/tiempos.txt";
    fstream fs;
    fs.open(filename, ios::app);
    fs << n << ", " << res.size() << ", " << total_time << "\n";
    fs.close();

    return 0;
}


/* -- couts para debuggear -- */

    // cout << "I_copia:" << endl;
    // for (intervalo i : I_copia) cout << i.inicio << " " << i.fin << endl;
    // cout << endl;

    // cout << "I:" << endl;
    // for (intervalo i : I) cout << i.inicio << " " << i.fin << endl;
    // cout << endl;

    // cout << "D:" << endl;
    // for (int v = 0; v < D.size(); v++) {
    //     cout << "[" << v << "] = ";
    //     for (arista e : D[v]) cout << e.destino << " ";
    //     cout << endl;
    // }
    // cout << endl;