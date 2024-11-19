#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

typedef struct node {
    int v;
    int weight;
    struct node *next;
} Node;

typedef Node *Graph_node;

typedef struct {
    Graph_node *adj;
    int n;
} Adj_list;

typedef struct {
    int *parent;
    int *distance;
} Path;

typedef Adj_list *AdjListGraph;

AdjListGraph list_create_graph(int n);
void list_destroy_graph(AdjListGraph g);
void list_insert_edge(AdjListGraph g, int u, int v, int weight);
void list_remove_edge(AdjListGraph g, int u, int v);
int list_have_edge(AdjListGraph g, int u, int v);
void list_print_edges(AdjListGraph g);
void list_rec_search(AdjListGraph g, int *components, int comp, int v);
int *list_find_components(AdjListGraph g);
void list_in_depth_search(AdjListGraph g, int *parent, int p, int v);
void list_print_reverse_path(int v, int *parent);
void list_print_path(int v, int *parent);
int *list_width_search(AdjListGraph g, int s);
int *dijkstra(AdjListGraph g, int s);
int degree_ListAdj(AdjListGraph g, int u);
int most_popular_List(AdjListGraph g);
void print_recommendations(AdjListGraph g, int u);
int has_path_List(AdjListGraph g, int start, int end);
Path prim_minimum_spanning_tree_la(AdjListGraph g, int start);

#endif
