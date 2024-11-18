#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX

typedef struct {
    int **adj;
    int n;
}Adj_list;

typedef Adj_matrix *graph;

graph create_graph(int n);
void destroy_graph(graph g);
void insert_edge(graph g, int u, int v);
void remove_edge(graph g, int u, int v);
int have_edge(graph g, int u, int v);
void print_edges(graph g);
graph read_graph();
int degree(graph g, int u);
int most_popular(graph g);
void print_recommendations(graph g, int u);

#include "adjacency_matrix.c"

#endif
