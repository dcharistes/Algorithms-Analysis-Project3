# Algorithms Project 3

This project contains implementations of three algorithms for finding the Minimum Spanning Trees (MST). These are:

- Prim's Algorithm
- Kruskal's Algorithm
- Reverse-Delete Algorithm

All three algorithms in this project are implemented using an adjacency list representation of graphs. The core data structures — Graph, Node, and Edge — are defined once and reused across all algorithm implementations, ensuring clarity and modularity. In addition, several utility functions are provided for graph manipulation (e.g., adding/removing edges, extracting edge lists, and initializing graphs). These functions enable a shared interface and simplify benchmarking.

- Benchmark testing framework for performance evaluation

## 🧪 Compilation

To compile the entire project:

```bash
gcc ./data_structure/task.c task1/task1.c task2/task2.c task3/task3.c bench_testing.c -o bench_testing.exe
```
To run it:
```bash
./bench_testing.exe
```
