# Algorithms Project 3

This project contains implementations of three algorithms for finding the Minimum Spanning Trees (MST). These are:

- Prim's Algorithm
- Kruskal's Algorithm
- Reverse-Delete Algorithm

All three algorithms in this project are implemented using an adjacency list representation of graphs. The core data structures — Graph, Node, and Edge — are defined once and reused across all algorithm implementations, ensuring modularity and validity in benchmark testing. In addition, several utility functions are share provided between the algorithms for graph manipulation (e.g., adding edges, extracting edge lists, and initializing graphs). These functions enable a shared interface.

The core objectives of the project are:

- Benchmark testing framework for performance evaluation
- Algorithmic Analysis, Theory validation and conclusions

## 🧪 Compilation

To compile the entire project:

```bash
gcc ./data_structure/task.c task1/task1.c task2/task2.c task3/task3.c bench_testing.c -o bench_testing.exe
```
To run it:
```bash
./bench_testing.exe
```
