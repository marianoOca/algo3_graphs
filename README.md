# Graph Algorithms – Algorithms and Data Structures III

The project focuses on solving and analyzing several problems related to graphs and digraphs using techniques such as **BFS**, **Union-Find**, **Johnson's algorithm** and **Bertossi's algorithm**.

---

## 📌 Problem Summary

This assignment involves solving the following problems:

1. **Geodesic Graph Detection** – Determine if a given connected graph is geodesic (i.e., has a unique shortest path between each pair of vertices).
2. **Connected Components in Sparse Matrices** – Count connected components in a 0/1 matrix representing adjacency, using **O(n)** space.
3. **All-Pairs Shortest Path** – Use **Johnson’s algorithm** to compute shortest paths in a weighted, directed graph.
4. **Minimum Total Dominating Set in Intervals** – Solve using **Bertossi's algorithm** for interval graphs.

---

## ⚙️ Techniques Used

- Breadth-First Search (BFS)
- Union-Find (Disjoint Sets)
- Johnson’s Algorithm (Bellman-Ford + Dijkstra)
- Interval Graph Modeling
- Complexity analysis and empirical benchmarking

---

## 🧪 Results Summary

Each algorithm was tested on custom and randomized instances. All experiments were benchmarked and results aligned with the expected theoretical time complexities.

- **Geodesic Graphs**: Verified with cycle-based and complete graphs
- **Connected Components**: Space-efficient linear scans with sliding-window Union-Find
- **Shortest Paths**: Efficient detection of negative cycles and correct shortest-path reconstruction
- **Dominating Sets**: Graph reduction and pathfinding over transformed digraphs

> 📄 See `informe.pdf` for detailed complexity analysis, figures, tables, and graphs.

📅 Term: 2nd semester of 2022
🏫 Universidad de Buenos Aires, Facultad de Ciencias Exactas y Naturales

## 🧪 How to Run the Exercises

Inside each exercise directory, run the following commands from the console:

### 🔁 To run **all instances**:

```bash
make
for i in ./instancias/*.txt; do echo ${i} >> ./resultados/tiempos.txt; timeout 600 ./resolucion < ${i}; done
```

### ▶️ To run a **single instance**:

```bash
make
echo './instancias/nombre-instancia' >> ./resultados/tiempos.txt
./resolucion < ./instancias/nombre-instancia
```

### 🧹 To clean the executable:

```bash
make clean
```

### 🧬 To generate instances (inside the `instancias/` folder):

```bash
python generador.py
```

---

## 🐳 Running with Docker

You can also compile and execute the program inside a Docker container:

### 🧰 Build and run:

From the root directory of the project:

```bash
cd <EJ>
docker build -t <EJ> .
docker run --rm -v <P>:/tp/tiempos <EJ> <I>
```

Where:

- `<EJ>` is the name of the exercise folder  
- `<P>` is the **absolute path** to the directory where results should be saved  
- `<I>` *(optional)* is the name of the specific instance to run

### 📦 Example:

```bash
cd ejercicio_2
docker build -t ejercicio_2 .
docker run --rm -v C:\Users\Lucas\tp\ejercicio_2:/tp/tiempos ejercicio_2
```

### 🧽 Cleanup suggestion:

To free up space, remove old Docker images (~1.15 GB each) with:

```bash
docker rmi <EJ> && docker image prune
```
