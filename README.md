# Graph Library in C

This project implements a comprehensive library for working with **graphs** in C, using **adjacency lists** and **adjacency matrices**. It includes basic graph operations, traversal algorithms, and graph-related utilities. Below is a detailed overview of the files, structures, and functionalities provided.

---

## Table of Contents
1. [Project Overview](#project-overview)  
2. [Features](#features)  
3. [Files and Structure](#files-and-structure)  
4. [Usage](#usage)  
5. [License](#license)  

---

## Project Overview

This library provides an efficient way to handle graphs with support for **adjacency lists** and **adjacency matrices**, making it versatile for different use cases. The implementation includes graph traversal (DFS, BFS), pathfinding algorithms (Dijkstra, Prim's MST), and utility functions for analyzing graph properties.

---

## Features

### General
- Create and manage graph structures.
- Support for weighted and unweighted edges.
- Graph traversal (BFS, DFS).
- Connected components detection.
- Pathfinding algorithms (Dijkstra, Prim's MST).
- Recommendations and popularity analysis.

### Adjacency List (`AdjListGraph`)
- Compact and memory-efficient representation.
- Efficient for sparse graphs.
- Functions for edge insertion, removal, and degree calculations.

### Adjacency Matrix (`AdjMatrixGraph`)
- Simple and fast access to edges.
- Better suited for dense graphs.
- Includes all standard graph operations.

---

## Files and Structure

### Core Graph Files
- **`adjacency_list.c` and `adjacency_list.h`**  
  Implementation of the adjacency list representation.
  
- **`adjacency_matrix.c` and `adjacency_matrix.h`**  
  Implementation of the adjacency matrix representation.

### Utilities
- **`priority_queue.c` and `priority_queue.h`**  
  Priority queue for algorithms like Dijkstra and Prim.
  
- **`queue.c` and `queue.h`**  
  Generic queue implementation used for BFS and other algorithms.

### Interfaces
- **`interfaces.c` and `interfaces.h`**  
  User-friendly interfaces for interacting with the library.  
  Supports English and Portuguese.

### Other
- **`main.c`**  
  **This is the main file to execute for running the program.**  
  It serves as the entry point for testing features and interacting with the graph library.
  
- **`makefile`**  
  Build automation script.

---

## Usage

### Build and run the project with an IDE
```c
./main.exe
```

## Interfaces
```c
run_english_interface();
run_portuguese_interface();
```

---

### License

This project is licensed under the MIT License. See the `LICENSE` file for details.

This README serves as a starting point for understanding and utilizing the graph library effectively. For more information, consult the source code and function comments.
