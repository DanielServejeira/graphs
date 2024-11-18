#include<stdio.h>
#include<stdlib.h>

Graph create_graph(int n) {
    int i;
    Graph g = malloc(sizeof(Graph));
    g->n = n;
    g->adjacency = malloc(n * sizeof(Graph_node));
    for (i = 0; i < n; i++)
        g->adjacency[i] = NULL;
    return g;
}
void free_list(Graph_node list) {
    if (list != NULL) {
        free_list(list->next);
        free(list);
    }
}
void destroy_graph(Graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free_list(g->adjacency[i]);
    free(g->adjacency);
    free(g);
}

Graph_node insert_to_list(Graph_node list, int v) {
    Graph_node new_node = malloc(sizeof(Node));
    new_node->v = v;
    new_node->next = list;
    return new_node;
}

void insert_edge(Graph g, int u, int v) {
    g->adjacency[v] = insert_to_list(g->adjacency[v], u);
    g->adjacency[u] = insert_to_list(g->adjacency[u], v);
}

Graph_node remove_from_list(Graph_node list, int v) {
    Graph_node next;
    if (list == NULL)
        return NULL;
    else if (list->v == v) {
        next = list->adjacency;
        free(list);
        return next;
    } else {
        list->adjacency = remove_from_list(list->adjacency, v);
        return list;
    }
}

void remove_edge(Graph g, int u, int v) {
    g->adjacency[u] = remove_from_list(g->adjacency[u], v);
    g->adjacency[v] = remove_from_list(g->adjacency[v], u);
}

int have_edge(Graph g, int u, int v) {
    Graph_node t;
    for (t = g->adjacency[u]; t != NULL; t = t->adjacency)
        if (t->v == v)
    return 1;
    return 0;
}

void print_edges(Graph g) {
    int u;
    Graph_node t;
    for (u=0; u < g->n; u++)
        for (t = g->adjacency[u]; t != NULL; t = t->next)
            printf("{%d,%d}\n", u, t->v);
}
