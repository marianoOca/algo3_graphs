#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

/* -- declaracion de variables -- */
int m, n;
vector<vector<int>> filas;
int cc = 0;

/* -- union-find -- */
struct UF {
    vector<int> p, s; // parents y size

    UF(int n): p(n, -1), s(n, 1) {}

    // hace la unión y devuelve el tamaño resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; // el árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }

    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]);
    }
};

/* -- declaracion de funciones auxiliares -- */
void contar_cc(UF& uf);
void actualizar(UF& viejo, UF& nuevo);

// lee la primer fila y une componentes conexas en ella
void primer_fila(UF& uf) {
    // leemos la fila de la consola
    int nodo;
    for (int i = 0; i < n; i++) {
        cin >> nodo;
        filas[0].push_back(nodo);
    }
    // unimos componentes en la fila
    for (int i = 0; i < n-1; i++) {
        if (filas[0][i] == 1 && filas[0][i+1] == 1) uf.unite(i, i+1);
    }
}

// lee una fila y une componentes conexas en ella
void leer_fila(UF& uf) {
    // limpiamos la fila anterior
    filas[1].clear();
    // leemos de consola la nueva fila
    int nodo;
    for (int i = 0; i < n; i++) {
        cin >> nodo;
        filas[1].push_back(nodo);
    }
    // unimos componentes en la fila
    for (int i = 0; i < n-1; i++) {
        if (filas[1][i] == 1 && filas[1][i+1] == 1) uf.unite(i+n, i+n+1);
    }
}

// une componentes conexas entre ambas filas
void unir_filas(UF& uf) {
    for (int i = 0; i < n; i++) {
        if (filas[0][i] == 1 && filas[1][i] == 1) uf.unite(i, i+n);
    }
}

// hace espacio para leer una nueva fila y guarda la info de la que perdemos
void nueva_fila(UF& viejo) {
    contar_cc(viejo);
    UF nuevo(2*n);
    actualizar(viejo, nuevo);
    viejo = nuevo;
    filas[0].clear();
    for (int i = 0; i < n; i++) {
        filas[0].push_back(filas[1][i]);
    }
}

int main(void) {
/* -- leemos el tamaño -- */
    cin >> m >> n;

    filas.assign(2, vector<int>()); // vector con las dos filas que tenemos en memoria
    UF uf(2*n);

/* -- leemos y procesamos la primer fila -- */
    auto start = chrono::steady_clock::now();
    primer_fila(uf);

/* -- leemos y procesamos el resto de a una -- */
    for (int i = 0; i < m-1; i++) {
        leer_fila(uf);
        unir_filas(uf);
        nueva_fila(uf);
    }

/* -- contamos cc de la ultima fila -- */
    vector<bool> etiquetas(2*n, false);
    for (int i = 0; i < n; i++) {
        if (filas[0][i]) etiquetas[uf.find(i)] = true;
    }
    for (int i = 0; i < 2*n; i++) {
        if (etiquetas[i]) cc++;
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

/* -- escribimos el resultado en consola -- */
    cout << cc << endl;

/* -- guardamos los tiempos -- */
    string filename = "./resultados/tiempos.txt";
    fstream fs;
    fs.open(filename, ios::app);
    fs << n << ", " << m << ", " << cc << ", " << total_time << "\n";
    fs.close();

    return 0;
}

/* -- funciones auxiliares -- */
// cuenta las componentes conexas de la fila que se va
// solo si no continuan en la fila siguiente
void contar_cc(UF& uf) {
    // etiquetas[i] es true si hay algun nodo en la fila 0 con la etiqueta i
    // y no hay ningun nodo en la fila 1 con la etiqueta i
    vector<bool> etiquetas(2*n, false);
    for (int i = 0; i < n; i++) {
        if (filas[0][i]) etiquetas[uf.find(i)] = true;
    }
    for (int i = n; i < 2*n; i++) etiquetas[uf.find(i)] = false;
    for (int i = 0; i < 2*n; i++) {
        if (etiquetas[i]) cc++;
    }
}

// actualiza las componentes conexas encontradas hasta el momento en el nuevo UF
void actualizar(UF& viejo, UF& nuevo) {
    // etiquetas[i] = todos los nodos que tienen etiqueta i en viejo
    vector<vector<int>> etiquetas(2*n, vector<int>());
    for (int i = 0; i < n; i++) etiquetas[viejo.find(i+n)].push_back(i);
    for (vector<int> etiqueta : etiquetas) {
        for (int i = 0; i < etiqueta.size(); i++) {
            nuevo.unite(etiqueta[0], etiqueta[i]);
        }
    }
}