#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#include "adjacency_list.h"
#include "queue.h"
#include "priority_queue.h"


/**
 * @brief Creates a graph with a specified number of vertices.
 *
 * This function allocates memory for a graph structure and initializes
 * its adjacency list with the given number of vertices. Each vertex's
 * adjacency list is initially set to NULL.
 *
 * @param n The number of vertices in the graph.
 * @return A pointer to the newly created graph.
 */
Graph list_create_graph(int n) {
    int i;
    Graph g = malloc(sizeof(Graph));
    g->n = n;
    g->adj = malloc(n * sizeof(Graph_node));
    for (i = 0; i < n; i++)
        g->adj[i] = NULL;
    return g;
}

/**
 * @brief Frees the memory allocated for a graph.
 *
 * This function frees the memory allocated for a graph structure and its
 * adjacency lists. It iterates through each vertex in the graph and frees
 * the memory allocated for its adjacency list, then frees the memory allocated
 * for the array of adjacency lists, and finally frees the memory allocated for
 * the graph structure itself.
 *
 * @param g A pointer to the graph structure to be destroyed.
 */
void free_list(Graph_node list) {
    if (list != NULL) {
        free_list(list->next);
        free(list);
    }
}


/**
 * @brief Destroys a graph and frees all associated memory.
 *
 * This function deallocates the memory used by the graph's adjacency list and the graph structure itself.
 *
 * @param g A pointer to the graph to be destroyed.
 */
void list_destroy_graph(Graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free_list(g->adj[i]);
    free(g->adj);
    free(g);
}

/**
 * @brief Inserts an edge between two vertices in the graph.
 *
 * This function inserts an edge between two vertices in the graph with a specified weight.
 * It adds the edge to the adjacency lists of both vertices.
 *
 * @param g The graph in which the edge is to be inserted.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @param weight The weight of the edge.
 */
Graph_node insert_to_list(Graph_node list, int v, int weight) {
    Graph_node new_node = malloc(sizeof(Node));
    new_node->v = v;
    new_node->next = list;
    new_node->weight = weight;
    return new_node;
}

/**
 * @brief Inserts an edge into the adjacency list of the graph.
 *
 * This function adds an edge between two vertices `u` and `v` with a specified weight.
 * It updates the adjacency list of both vertices to reflect the new edge.
 *
 * @param g The graph in which the edge is to be inserted.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @param weight The weight of the edge.
 */
void list_insert_edge(Graph g, int u, int v, int weight) {
    g->adj[v] = insert_to_list(g->adj[v], u, weight);
    g->adj[u] = insert_to_list(g->adj[u], v, weight);
}

/**
 * @brief Removes a node with a specific value from a linked list of graph nodes.
 *
 * This function searches for a node with the value `v` in the linked list `list`.
 * If found, it removes the node from the list and frees its memory.
 *
 * @param list A pointer to the head of the linked list of graph nodes.
 * @param v The value of the node to be removed.
 * @return A pointer to the head of the modified linked list. If the head node
 *         is removed, the function returns the next node in the list.
 */
Graph_node remove_from_list(Graph_node list, int v) {
    if (list == NULL) return NULL;

    if (list->v == v) {
        Graph_node next = list->next;
        free(list);
        return next;
    }

    list->next = remove_from_list(list->next, v);
    return list;
}

/**
 * @brief Removes an edge between two vertices in the graph.
 *
 * This function removes an edge between two vertices `u` and `v` from the graph.
 * It updates the adjacency lists of both vertices to reflect the removal of the edge.
 *
 * @param g The graph from which the edge is to be removed.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 */
void list_remove_edge(Graph g, int u, int v) {
    if (u >= g->n || v >= g->n) return; // Verifica se os vértices são válidos
    g->adj[u] = remove_from_list(g->adj[u], v);
    g->adj[v] = remove_from_list(g->adj[v], u);
}

/**
 * @brief Checks if an edge exists between two vertices in the graph.
 *
 * This function checks if an edge exists between two vertices `u` and `v` in the graph.
 *
 * @param g The graph in which the edge is to be checked.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @return 1 if the edge exists, 0 otherwise.
 */
int list_have_edge(Graph g, int u, int v) {
    for (Graph_node t = g->adj[u]; t != NULL; t = t->next) {
        if (t->v == v)
            return 1;
    }
    return 0;
}

/**
 * @brief Prints the edges of the graph represented by an adjacency list.
 *
 * This function prints the edges of the graph by iterating through each vertex
 * and its adjacency list. For each vertex, it prints the edges to its neighbors.
 *
 * @param g The graph whose edges are to be printed.
 */
void list_print_edges(Graph g) {
    int u;
    Graph_node t;
    for (u=0; u < g->n; u++)
        for (t = g->adj[u]; t != NULL; t = t->next)
            printf("{%d,%d}\n", u, t->v);
}

/**
 * @brief Searches for connected components in the graph.
 *
 * This function searches for connected components in the graph using a recursive depth-first search.
 * It assigns a component number to each vertex in the graph.
 *
 * @param g The graph in which connected components are to be found.
 * @param components An array to store the component number of each vertex.
 * @param comp The current component number.
 * @param v The current vertex being visited.
 */
void list_rec_search(Graph g, int *components , int comp, int v) {
    Graph_node t;
    components[v] = comp;           

    for (t = g->adj[v]; t != NULL; t = t->next)
        if (components[t->v] == -1)
            list_rec_search(g, components , comp, t->v);
}   

/**
 * @brief Finds connected components in the graph.
 *
 * This function finds the connected components in the graph by performing a depth-first search
 * starting from each vertex. It assigns a component number to each vertex in the graph.
 *
 * @param g The graph in which connected components are to be found.
 * @return An array containing the component number of each vertex.
 */
int *list_find_components(Graph g) {
    int s, c = 0, *components = malloc(g->n * sizeof(int));

    for (s = 0; s < g->n; s++)
        components[s] = -1;

    for (s = 0; s < g->n; s++)
        if (components[s] == -1) {
            list_rec_search(g, components , c, s);
            c++;
    }

    return components;
}

/**
 * @brief Performs a depth-first search on the graph.
 *
 * This function performs a depth-first search on the graph starting from a specified vertex.
 * It assigns a parent to each vertex in the graph.
 *
 * @param g The graph to be searched.
 * @param parent An array to store the parent of each vertex.
 * @param p The parent of the current vertex.
 * @param v The current vertex being visited.
 */
void list_in_depth_search(Graph g, int *parent, int p, int v) {
    Graph_node t;
    parent[v] = p;

    for(t = g->adj[v]; t != NULL; t = t->next)
        if (parent[t->v] == -1)
            list_in_depth_search(g, parent, v, t->v);
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
int *list_find_paths(Graph g, int s) {
    int i, *parent = malloc(g->n * sizeof(int));

    for (i = 0; i < g->n; i++)
        parent[i] = -1;

    list_in_depth_search(g, parent, s, s);
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
void list_print_reverse_path(int v, int *parent) {
    printf("%d", v);
    if(parent[v] != v)
    list_print_reverse_path(parent[v], parent);
}

/**
 * @brief Prints the path from the source vertex to a vertex.
 *
 * This function prints the path from the source vertex to a vertex using the parent array.
 *
 * @param v The vertex for which the path is to be printed.
 * @param parent An array containing the parent of each vertex.
 */
void list_print_path(int v, int *parent) {
    if(parent[v] != v)
        list_print_path(parent[v], parent);
    printf("%d", v);
}

/**
 * @brief Finds the shortest path from a source vertex to all other vertices in the graph.
 *
 * This function finds the shortest path from a source vertex to all other vertices in the graph using Dijkstra's algorithm.
 * It assigns a parent to each vertex in the graph.
 *
 * @param g The graph in which the shortest path is to be found.
 * @param s The source vertex.
 * @return An array containing the parent of each vertex.
 */
int *dijkstra(Graph g, int s) {
    int v, *parent = malloc(g->n * sizeof(int));
    Graph_node t;
    p_queue h = create_p_queue(g->n);
    for (v = 0; v < g->n; v++) {
        parent[v] = -1;
        insert(h, v, INT_MAX);
    }
    parent[s] = s;
    decrease_priority(h, s, 0);
    while (!is_prior_queue_empty(h)) {
        v = extract_min(h);
        if (priority(h, v) != INT_MAX)
            for (t = g->adj[v]; t != NULL; t = t->next)
                if (priority(h, v) + t->weight < priority(h, t->v)) {
                    decrease_priority(h, t->v, priority(h, v) + t->weight);
                    parent[t->v] = v;
                }
    }
    return parent;
}

/**
 * @brief Finds the shortest path from a source vertex to all other vertices in the graph.
 *
 * This function finds the shortest path from a source vertex to all other vertices in the graph using breadth-first search.
 * It assigns a parent to each vertex in the graph.
 *
 * @param g The graph in which the shortest path is to be found.
 * @param s The source vertex.
 * @return An array containing the parent of each vertex.
 */
int *list_width_search(Graph g, int s) {
    // Verificar se o vértice inicial é válido
    

    int w, v;
    int *parent = malloc(g->n * sizeof(int)); // Vetor para armazenar os pais
    int *visited = malloc(g->n * sizeof(int)); // Vetor de vértices visitados
    Queue *f = create_queue(g->n); // Cria a fila com capacidade igual ao número de vértices

    // Inicializa os vetores de pais e visitados
    for(v = 0; v < g->n; v++) {
        parent[v] = -1;
        visited[v] = 0;
    }

    // Adiciona o vértice inicial na fila
    enqueue(f, s);
    parent[s] = s; // O vértice inicial é seu próprio pai
    visited[s] = 1; // Marca como visitado

    // Realiza a busca em largura
    while (!is_queue_empty(f)) {
        v = dequeue(f); // Desenfileira um vértice

        // Percorre a lista de adjacência do vértice v
        for (Graph_node aux = g->adj[v]; aux != NULL; aux = aux->next) {
            w = aux->v; // Obtém o índice do vértice adjacente
            if (!visited[w]) { // Verifica se o vértice já foi visitado
                visited[w] = 1; // Marca como visitado
                parent[w] = v; // Define o pai
                enqueue(f, w); // Enfileira o vértice adjacente
            }
        }
    }

    // Libera memória alocada para a fila e o vetor visited
    destroy_queue(f);
    free(visited);

    return parent; // Retorna o vetor de pais
}

/**
 * @brief Calculates the degree of a vertex in the graph.
 *
 * This function calculates the degree of a vertex in the graph, i.e., the number of edges incident to the vertex.
 *
 * @param g The graph in which the degree is to be calculated.
 * @param u The vertex for which the degree is to be calculated.
 * @return The degree of the vertex.
 */
int degree_ListAdj(Graph g, int u){
    Graph_node aux;
    int degree = 0;
    for(aux = g->adj[u]; aux != NULL; aux = aux->next){
        degree++;
    }
    return degree;
}

/**
 * @brief Finds the most popular vertex in the graph.
 *
 * This function finds the most popular vertex in the graph, i.e., the vertex with the highest degree.
 *
 * @param g The graph in which the most popular vertex is to be found.
 * @return The most popular vertex in the graph.
 */
int most_popular_List(Graph g){
    int u, max, max_degree, current_degree;

    max = 0;
    max_degree = degree_ListAdj(g, max);
    for( u = 1; u < g->n; u++) {
        current_degree = degree_ListAdj(g, u);
        if(current_degree > max_degree){
            max = u;
            max_degree = current_degree;
        }
    }
    return max;
}

/**
 * @brief Prints recommendations for a vertex in the graph.
 *
 * This function prints recommendations for a vertex in the graph. It iterates through the
 * adjacency list of each neighbor of the vertex and prints the vertices that are not already
 * recommended.
 *
 * @param g The graph for which recommendations are to be printed.
 * @param u The vertex for which recommendations are to be printed.
 */
void print_recommendations(Graph g, int u){
    Graph_node aux, rec_aux;
    int *recommended = malloc(g->n * sizeof(int));  
    int i;
    for (i = 0; i < g->n; i++) {
        recommended[i] = 0;
    }

    for (aux = g->adj[u]; aux != NULL; aux = aux->next) {
        int v = aux->v;

        for (rec_aux = g->adj[v]; rec_aux != NULL; rec_aux = rec_aux->next) {
            int w = rec_aux->v;

            if (w != u) {
                if (!recommended[w]) {  //verifica se já não foi recomendado
                    printf("Recommendation: %d\n", w);  
                    recommended[w] = 1;  
                }
            }
        }
    }

    free(recommended);  // Libera a memória alocada para o vetor de recomendados
}

/**
 * @brief Searches for a path between two vertices in the graph.
 *
 * This function searches for a path between two vertices in the graph using a recursive depth-first search.
 *
 * @param g The graph in which the path is to be found.
 * @param visited An array to store the visited vertices.
 * @param v The current vertex being visited.
 * @param t The target vertex.
 * @return 1 if a path exists, 0 otherwise.
 */
int rec_search_list(Graph g,int* visited, int v, int t){
    int w;
    Graph_node aux;

    if(v == t){
        return 1;
    }
    visited[v] = 1;
    for(aux = g->adj[v]; aux != NULL ; aux = aux->next){
        w = aux->v;
        if(!visited[w]){
            if(rec_search_list(g, visited, w, t)){
                return 1;
            }
        }

    }
    return 0;
}

/**
 * @brief Checks if a path exists between two vertices in the graph.
 *
 * This function checks if a path exists between two vertices in the graph using a recursive depth-first search.
 *
 * @param g The graph in which the path is to be checked.
 * @param start The source vertex.
 * @param end The target vertex.
 * @return 1 if a path exists, 0 otherwise.
 */
int has_path_List(Graph g, int start, int end){
    int founded_flag, i;
    int *visited = malloc(g->n * sizeof(int));

    for (i = 0 ; i < g->n ; i++){
        visited[i] = 0;
    }

    founded_flag = rec_search_list(g,visited,start,end);
    free(visited);

    return founded_flag;
}

