#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

typedef struct node {
    int v;
    struct node *next;
} Node;

typedef Node *Graph_node;

typedef struct {
    Graph_node *adjacency;
    int n;
} Adj_list;

typedef Adj_list *Graph;

Graph list_create_graph(int n);
void list_destroy_graph(Graph g);
void list_insert_edge(Graph g, int u, int v);
void list_remove_edge(Graph g, int u, int v);
int list_have_edge(Graph g, int u, int v);
void list_print_edges(Graph g);

#endif
