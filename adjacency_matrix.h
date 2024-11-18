#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

typedef struct {
    int **adj;
    int n;
}Adj_matrix;

typedef Adj_matrix *graph;

graph matrix_create_graph(int n);
void matrix_destroy_matrix_graph(graph g);
void matrix_insert_edge(graph g, int u, int v, int weight);
void matrix_remove_edge(graph g, int u, int v);
int matrix_have_edge(graph g, int u, int v);
void matrix_print_edges(graph g);
graph matrix_read_graph();
int matrix_degree(graph g, int u);
int matrix_most_popular(graph g);
void matrix_print_recommendations(graph g, int u);
int matrix_path_exists(graph g, int s, int t);
int matrix_rec_search(graph g, int *visited , int v, int t);

#endif
