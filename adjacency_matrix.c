#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#include "adjacency_matrix.h"
#include "queue.h"
#include "priority_queue.h"

/**
 * @brief Creates a graph represented by an adjacency matrix.
 *
 * This function allocates memory for a graph structure and initializes
 * its adjacency matrix. The matrix is initialized with -1 to indicate
 * that there are no edges between any vertices initially.
 *
 * @param n The number of vertices in the graph.
 * @return A pointer to the created graph structure.
 */
graph matrix_create_graph(int n) {
    int i, j;

    graph g = malloc(sizeof(Adj_matrix));
    g->n = n;
    g->adj = malloc(n*sizeof(int *));
    for(i=0; i<n; i++) {
        g->adj[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;
    return g;
}

/**
 * @brief Destroys a graph represented by an adjacency matrix.
 *
 * This function deallocates the memory used by the adjacency matrix of the graph
 * and the graph structure itself. It iterates through each row of the adjacency
 * matrix, freeing the memory allocated for each row, then frees the memory allocated
 * for the adjacency matrix array, and finally frees the memory allocated for the graph structure.
 *
 * @param g A pointer to the graph structure to be destroyed.
 */
void matrix_destroy_matrix_graph(graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

/**
 * @brief Inserts an edge into the adjacency matrix of the graph.
 *
 * This function adds an edge between two vertices in the graph with a specified weight.
 * It updates the adjacency matrix to reflect the new edge.
 *
 * @param g The graph in which the edge is to be inserted.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @param weight The weight of the edge.
 */
void matrix_insert_edge(graph g, int u, int v, int weight) {
    g->adj[u][v] = weight;
    g->adj[v][u] = weight;
}

/**
 * @brief Removes an edge from the adjacency matrix of the graph.
 *
 * This function removes an edge between two vertices in the graph. It updates the adjacency
 * matrix to reflect the removal of the edge.
 *
 * @param g The graph from which the edge is to be removed.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 */
void matrix_remove_edge(graph g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

/**
 * @brief Checks if an edge exists between two vertices in the graph.
 *
 * This function checks if an edge exists between two vertices in the graph.
 *
 * @param g The graph in which the edge is to be checked.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @return 1 if the edge exists, 0 otherwise.
 */
int matrix_have_edge(graph g, int u, int v) {
    return g->adj[u][v];
}

/**
 * @brief Prints the edges of the graph represented by an adjacency matrix.
 *
 * This function prints the edges of the graph represented by an adjacency matrix.
 * It iterates through the adjacency matrix and prints the edges that have a non-zero weight.
 *
 * @param g The graph whose edges are to be printed.
 */
void matrix_print_edges(graph g) {
    int u, v;
    for (u = 0; u < g->n; u++)
        for (v = u+1; v < g->n; v++)
            if (g->adj[u][v])
                printf("{%d,%d}\n", u, v);
}

/**
 * @brief Reads a graph from standard input.
 *
 * This function reads a graph from standard input. It first reads the number of vertices
 * and edges in the graph, then reads the edges and their weights. It creates a graph
 * represented by an adjacency matrix and inserts the edges into the graph.
 *
 * @return The graph read from standard input.
 */
graph matrix_read_graph() {
    int n, m, i, u, v, w;
    graph g;
    scanf("%d %d", &n, &m);
    g = matrix_create_graph(n);
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        matrix_insert_edge(g, u, v, w);
    }
    return g;
}

/**
 * @brief Calculates the degree of a vertex in the graph.
 *
 * This function calculates the degree of a vertex in the graph, i.e., the number of edges
 * incident on the vertex. It iterates through the row of the adjacency matrix corresponding
 * to the vertex and counts the number of non-zero entries.
 *
 * @param g The graph in which the degree is to be calculated.
 * @param u The vertex whose degree is to be calculated.
 * @return The degree of the vertex.
 */
int matrix_degree(graph g, int u) {
    int v, degree = 0;
    for (v = 0; v < g->n; v++)
        if (g->adj[u][v])
            degree++;
    return degree;
}

/**
 * @brief Finds the most popular vertex in the graph.
 *
 * This function finds the most popular vertex in the graph, i.e., the vertex with the highest degree.
 * It iterates through all vertices in the graph, calculates the degree of each vertex, and keeps track
 * of the vertex with the highest degree.
 *
 * @param g The graph in which the most popular vertex is to be found.
 * @return The most popular vertex in the graph.
 */
int matrix_most_popular(graph g) {
    int u, max, max_degree , current_degree;
    max = 0;
    max_degree = matrix_degree(g, 0);
    for (u = 1; u < g->n; u++) {
        current_degree = matrix_degree(g, u);
        if (current_degree > max_degree) {
            max_degree = current_degree;
            max = u;
        }
    }
    return max;
}

/**
 * @brief Prints recommendations for a vertex in the graph.
 *
 * This function prints recommendations for a vertex in the graph. It iterates through the
 * neighbors of the vertex, then iterates through the neighbors of each neighbor, and prints
 * the neighbors of the neighbors that are not neighbors of the original vertex.
 *
 * @param g The graph for which recommendations are to be printed.
 * @param u The vertex for which recommendations are to be printed.
 */
void matrix_print_recommendations(graph g, int u) {
    int v, w;
    for (v=0; v < g->n; v++) {
        if (g->adj[u][v]) {
            for (w = 0; w < g->n; w++) {
                if (g->adj[v][w] && w != u && !g->adj[u][w])
                    printf("%d\n", w);
            }
        }
    }
}

/**
 * @brief Checks if a path exists between two vertices in the graph.
 *
 * This function checks if a path exists between two vertices in the graph. It uses a recursive
 * depth-first search to explore the graph starting from the source vertex and marks visited
 * vertices. If the target vertex is reached during the search, the function returns 1, indicating
 * that a path exists between the source and target vertices.
 *
 * @param g The graph in which the path is to be checked.
 * @param s The source vertex.
 * @param t The target vertex.
 * @return 1 if a path exists between the source and target vertices, 0 otherwise.
 */
int matrix_path_exists(graph g, int s, int t) {
    int found , i, *visited = malloc(g->n * sizeof(int));
    for (i=0; i < g->n; i++)
        visited[i] = 0;
    found = matrix_rec_search(g, visited , s, t);
    free(visited);
    return found;
}

/**
 * @brief Recursive depth-first search to check if a path exists between two vertices.
 *
 * This function performs a recursive depth-first search to check if a path exists between two
 * vertices in the graph. It marks visited vertices to avoid revisiting them and explores the
 * graph starting from the source vertex. If the target vertex is reached during the search, the
 * function returns 1, indicating that a path exists between the source and target vertices.
 *
 * @param g The graph in which the path is to be checked.
 * @param visited An array to keep track of visited vertices.
 * @param v The current vertex being visited.
 * @param t The target vertex.
 * @return 1 if a path exists between the source and target vertices, 0 otherwise.
 */
int matrix_rec_search(graph g, int *visited , int v, int t) {
    int w;
    if (v == t)
        return 1;
    visited[v] = 1;
    for (w=0; w < g->n; w++)
        if (g->adj[v][w] && !visited[w])
            if (matrix_rec_search(g, visited , w, t))
                return 1;
    return 0;
}

/**
 * @brief Finds the shortest path from a source vertex to all other vertices in the graph.
 *
 * This function finds the shortest path from a source vertex to all other vertices in the graph
 * using Dijkstra's algorithm. It assigns a parent to each vertex in the graph.
 *
 * @param g The graph in which the shortest path is to be found.
 * @param s The source vertex.
 * @return An array containing the parent of each vertex.
 */
int *dijkstra(graph g, int s) {
    int *dist = malloc(g->n * sizeof(int));
    int *visited = malloc(g->n * sizeof(int));
    int i, u, v, min_dist, next_node;

    if (!dist || !visited) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < g->n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[s] = 0;

    for (i = 0; i < g->n - 1; i++) {
        min_dist = INT_MAX;
        next_node = -1;
        for (v = 0; v < g->n; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                next_node = v;
            }
        }

        if (next_node == -1) {
            break;
        }

        visited[next_node] = 1;

        for (v = 0; v < g->n; v++) {
            if (!visited[v] && g->adj[next_node][v] &&
                dist[next_node] != INT_MAX &&
                dist[next_node] + g->adj[next_node][v] < dist[v]) {
                dist[v] = dist[next_node] + g->adj[next_node][v];
            }
        }
    }

    free(visited);
    return dist;  // Retorna as distâncias calculadas
}

/**
 * @brief Performs a breadth-first search on the graph starting from a source vertex.
 *
 * This function performs a breadth-first search on the graph starting from a source vertex.
 * It assigns a parent to each vertex in the graph and returns an array containing the parent
 * of each vertex.
 *
 * @param g The graph in which the breadth-first search is to be performed.
 * @param s The source vertex.
 * @return An array containing the parent of each vertex.
 */
int *matrix_width_search(graph g, int s){ // trocar para matrix_BFS
    int *parent = malloc(g->n * sizeof(int));
    int *visited = malloc(g->n * sizeof(int));
    int w,v;
    Queue *f = create_queue(g->n);

    for(v = 0; v < g->n ; v++){
        parent[v] = -1;
        visited[v] = 0;
    }

    enqueue(f,s);
    parent[s] = s;
    visited[s] = 1;

    while(!empty_queue(f)){
        v = dequeue(f);

        for(w = 0; w < g->n; w++){
            if(g->adj[v][w] != -1 && !visited[w]){
                visited[w] = 1; 
                parent[w] = v; 
                enqueue(f, w); 
            }
        }
    }
    destroy_queue(f);
    free(visited);

    return parent; 
}

/**
 * @brief Prints the path from a vertex to the source vertex.
 *
 * This function prints the path from a vertex to the source vertex using the parent array.
 *
 * @param v The vertex for which the path is to be printed.
 * @param parent An array containing the parent of each vertex.
 */
void matrix_in_depth_search(graph g, int* parent, int p, int v){
    parent[v] = p;
    int w;
    for(w = 0; w < g->n; w++){
        if(g->adj[v][w] != 0 && parent[w] == -1){
            matrix_in_depth_search(g, parent, v, w);
        }
    }
}

/**
 * @brief Finds paths from a source vertex to all other vertices in the graph.
 *
 * This function finds paths from a source vertex to all other vertices in the graph using a depth-first search.
 * It assigns a parent to each vertex in the graph.
 *
 * @param g The graph in which paths are to be found.
 * @param s The source vertex.
 * @return An array containing the parent of each vertex.
 */
int *matrix_find_paths(graph g, int s){
    int* parent = malloc (g->n * sizeof(int));
    int i;

    for(i = 0; i < g->n; i++){
        parent[i] = -1;
    }
    matrix_in_depth_search(g,parent,s,s);
    return parent;
}

/**
 * @brief Finds the connected components of the graph.
 *
 * This function finds the connected components of the graph using a recursive depth-first search.
 * It assigns a component number to each vertex in the graph.
 *
 * @param g The graph in which the connected components are to be found.
 * @return An array containing the component number of each vertex.
 */
void matrix_recursive_visit(graph g, int *components, int count_comp, int v){
    components[v] = count_comp;

    for(int w = 0; w < g->n; w++){
        if(g->adj[v][w] == 1 && components[w] == -1){
            matrix_recursive_visit(g,components,count_comp,w);
        }
    }
}

/**
 * @brief Finds the connected components of the graph.
 *
 * This function finds the connected components of the graph using a recursive depth-first search.
 * It assigns a component number to each vertex in the graph.
 *
 * @param g The graph in which the connected components are to be found.
 * @return An array containing the component number of each vertex.
 */
int *matrix_find_components(graph g){
    int s, count_components = 0;
    int * components = malloc (g->n * sizeof(int));
    for(s = 0; s < g->n; s++){
        components[s] = -1;
    }

    for(s = 0; s < g->n; s++){
        if(components[s] == -1){
            matrix_recursive_visit(g,components,count_components,s);
            count_components++;
        }
    }
    return components;
}
