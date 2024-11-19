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

typedef Adj_list *Graph;

Graph list_create_graph(int n);
void list_destroy_graph(Graph g);
void list_insert_edge(Graph g, int u, int v, int weight);
void list_remove_edge(Graph g, int u, int v);
int list_have_edge(Graph g, int u, int v);
void list_print_edges(Graph g);
void list_rec_search(Graph g, int *components, int comp, int v);
int *list_find_components(Graph g);
void list_in_depth_search(Graph g, int *parent, int p, int v);
void list_print_reverse_path(int v, int *parent);
void list_print_path(int v, int *parent);
int *list_width_search(Graph g, int s);
int *dijkstra(Graph g, int s);
int degree_ListAdj(Graph g, int u);
int most_popular_List(Graph g);
void print_recommendations(Graph g, int u);
int has_path_List(Graph g, int start, int end);
Path prim_minimum_spanning_tree_la(Graph g, int start);

#endif
