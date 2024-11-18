#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST

typedef struct node {
    int v;
    struct node *next;
} Node;

typedef Node *Graph_node;

typedef struct {
    graph_node *adjacency;
    int n;
} Adj_list;

typedef Adj_list *Graph;

Graph criar_grafo(int n);
void destroy_graph(Graph g);
void insert_edge(Graph g, int u, int v);
void remove_edge(Graph g, int u, int v);
int have_edge(Graph g, int u, int v);
void print_edges(Graph g);

#include "adjacency_list.c"

#endif
