#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

typedef struct {
    int **adj;
    int n;
    int weight;
}Adj_matrix;

typedef Adj_matrix *AdjMatrixGraph;

AdjMatrixGraph matrix_create_graph(int n);
void matrix_destroy_graph(AdjMatrixGraph g);
void matrix_insert_edge(AdjMatrixGraph g, int u, int v, int weight);
void matrix_remove_edge(AdjMatrixGraph g, int u, int v);
int matrix_have_edge(AdjMatrixGraph g, int u, int v);
void matrix_print_edges(AdjMatrixGraph g);
int matrix_degree(AdjMatrixGraph g, int u);
int matrix_most_popular(AdjMatrixGraph g);
void matrix_print_recommendations(AdjMatrixGraph g, int u);
int matrix_path_exists(AdjMatrixGraph g, int s, int t);
int matrix_rec_search(AdjMatrixGraph g, int *visited , int v, int t);
int *matrix_width_search(AdjMatrixGraph g, int s);       //largura
int *matrix_find_paths(AdjMatrixGraph g, int s);         //profundidade
int *matrix_find_components(AdjMatrixGraph g);
void matrix_print_reverse_path(int v, int *parent);
void matrix_print_path(int v, int *parent);

#endif
