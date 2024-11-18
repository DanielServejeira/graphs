#include<stdio.h>
#include<stdlib.h>

#include "adjacency_list.h"
#include "queue.h"

Graph list_create_graph(int n) {
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
void list_destroy_graph(Graph g) {
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

void list_insert_edge(Graph g, int u, int v) {
    g->adjacency[v] = insert_to_list(g->adjacency[v], u);
    g->adjacency[u] = insert_to_list(g->adjacency[u], v);
}

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

void list_remove_edge(Graph g, int u, int v) {
    g->adjacency[u] = remove_from_list(g->adjacency[u], v);
    g->adjacency[v] = remove_from_list(g->adjacency[v], u);
}

int list_have_edge(Graph g, int u, int v) {
    for (Graph_node t = g->adjacency[u]; t != NULL; t = t->next) {
        if (t->v == v)
            return 1;
    }
    return 0;
}

void list_print_edges(Graph g) {
    int u;
    Graph_node t;
    for (u=0; u < g->n; u++)
        for (t = g->adjacency[u]; t != NULL; t = t->next)
            printf("{%d,%d}\n", u, t->v);
}

void list_rec_search(Graph g, int *components , int comp, int v) {
    Graph_node t;
    components[v] = comp;

    for (t = g->adj[v]; t != NULL; t = t->next)
        if (components[t->v] == -1)
            list_rec_search(g, components , comp, t->v);
}

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

void list_in_depth_search(Graph g, int *parent, int p, int v) {
    Graph_node t;
    parent[v] = p;

    for(t = g->adj[v]; t != NULL; t = t->next)
        if (parent[t->v] == -1)
            in_depth_search(g, parent, v, t->v);
}

int *list_find_paths(Graph g, int s) {
    int i, *parent = malloc(g->n * sizeof(int));

    for (i = 0; i < g->n; i++)
        parent[i] = -1;

    in_depth_search(g, parent, s, s);
    return parent;
}

void list_print_reverse_path(int v, int *parent) {
    printf("%d", v);
    if(parent[v] != v)
    print_reverse_path(parent[v], parent);
}

void list_print_path(int v, int *parent) {
    if(parent[v] != v)
        list_print_path(parent[v], parent);
    printf("%d", v);
}

int *list_width_search(Graph g, int s) { //ARRUMAR
    int w, v;
    int *parent = malloc(g->n * sizeof(int));
    int *visited = malloc(g->n * sizeof(int));
    Queue f = create_queue();

    for (v = 0; v < g->n; v++) {
        parent[v] = -1;
        visited[v] = 0;
    }

    enqueue(f,s);
    parent[s] = s;
    visited[s] = 1;

    while(!empty_queue(f)) {
        v = dequeue(f);
        for (w = 0; w < g->n; w++)
            if (g->adj[v][w] && !visited[w]) {
                visited[w] = 1;
                parent[w] = v;
                enqueue(f, w);
            }
    }

    destroy_queue(f);
    free(visited);
    return parent;
}
