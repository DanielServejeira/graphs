#include<stdio.h>
#include<stdlib.h>

#include "adjacency_matrix.h"
#include "queue.h"

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
            g->adj[i][j] = -1;
    return g;
}

void matrix_destroy_matrix_graph(graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

void matrix_insert_edge(graph g, int u, int v, int weight) {
    g->adj[u][v] = weight;
    g->adj[v][u] = weight;
}
void matrix_remove_edge(graph g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}
int matrix_have_edge(graph g, int u, int v) {
    return g->adj[u][v];
}

void matrix_print_edges(graph g) {
    int u, v;
    for (u = 0; u < g->n; u++)
        for (v = u+1; v < g->n; v++)
            if (g->adj[u][v])
                printf("{%d,%d}\n", u, v);
}

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

int matrix_degree(graph g, int u) {
    int v, degree = 0;
    for (v = 0; v < g->n; v++)
        if (g->adj[u][v])
            degree++;
    return degree;
}

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

int matrix_path_exists(graph g, int s, int t) {
    int found , i, *visited = malloc(g->n * sizeof(int));
    for (i=0; i < g->n; i++)
        visited[i] = 0;
    found = matrix_rec_search(g, visited , s, t);
    free(visited);
    return found;
}

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


