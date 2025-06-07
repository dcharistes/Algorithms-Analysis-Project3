# Algorithms-Analysis-Project3

## 📚 Overview

This repository presents a computational analysis of three prominent algorithms for finding the Minimum Spanning Tree (MST) in a graph:

* **Prim's Algorithm**
* **Kruskal's Algorithm**
* **Reverse-Delete Algorithm**

Each algorithm is implemented using an adjacency list representation of graphs. The core data structures—`Graph`, `Node`, and `Edge`—are defined once and reused across all algorithm implementations, ensuring modularity and consistency in benchmarking.

## 📁 Project Structure

```
.
├── .vscode/                 # VSCode configuration files
├── crossection_analysis/    # Scripts for analyzing algorithm performance
├── data_structure/          # Definitions of core data structures (Graph, Node, Edge)
├── logs/                    # Output logs from benchmarking tests
├── task1/                   # Implementation of Prim's Algorithm
├── task2/                   # Implementation of Kruskal's Algorithm
├── task3/                   # Implementation of Reverse-Delete Algorithm
├── benchmark_test.c         # C program to benchmark the algorithms
├── run_benchmark.sh         # Shell script to execute benchmarks
└── README.md                # Project documentation
```

## ⚙️ Setup & Usage

### Prerequisites

* A C compiler (e.g., `gcc`)
* Unix-like environment for running shell scripts

### Compilation

Navigate to the root directory of the project and compile the benchmarking program:

```bash
gcc /data_structure/data_struct.c task1/task1.c task2/task2.c task3/task3.c benchmark_test.c -o benchmark_test.exe
```

### Running Benchmarks

Execute the provided shell script to run the benchmark:

```bash
./run_benchmark.sh
```

This script will:

1. Compile the benchmarking program (if not already compiled).
2. Run the benchmarking tests for all three algorithms.
3. Store the output logs in the `logs/` directory for further analysis.

## 📊 Performance Analysis

The `crossection_analysis/` directory contains scripts and tools to analyze the performance of the implemented algorithms. These analyses help in understanding the time and space complexities, as well as the practical efficiency of each algorithm under different scenarios.

## 🧱 Core Data Structures

Located in the `data_structure/` directory, the core components include:

* `Graph`: Represents the entire graph using an adjacency list.
* `Node`: Represents a vertex in the graph.
* `Edge`: Represents an edge connecting two nodes with an associated weight.

These structures are designed for reusability and are utilized across all algorithm implementations.

## 📌 Tasks Breakdown

* **Task 1 (`task1/`)**: Implementation of Prim's Algorithm.
* **Task 2 (`task2/`)**: Implementation of Kruskal's Algorithm.
* **Task 3 (`task3/`)**: Implementation of the Reverse-Delete Algorithm.

Each task directory contains the source code specific to the respective algorithm.

## Acknowledgments

This project was developed as part of the coursework for the Algorithms Design and Analysis class.
