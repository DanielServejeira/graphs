#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#include "adjacency_list.h"
#include "queue.h"
#include "priority_queue.h"

Graph list_create_graph(int n) {
    int i;
    Graph g = malloc(sizeof(Graph));
    g->n = n;
    g->adj = malloc(n * sizeof(Graph_node));
    for (i = 0; i < n; i++)
        g->adj[i] = NULL;
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
        free_list(g->adj[i]);
    free(g->adj);
    free(g);
}

Graph_node insert_to_list(Graph_node list, int v, int weight) {
    Graph_node new_node = malloc(sizeof(Node));
    new_node->v = v;
    new_node->next = list;
    new_node->weight = weight;
    return new_node;
}


void list_insert_edge(Graph g, int u, int v, int weight) {
    g->adj[v] = insert_to_list(g->adj[v], u, weight);
    g->adj[u] = insert_to_list(g->adj[u], v, weight);
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
    if (u >= g->n || v >= g->n) return; // Verifica se os vértices são válidos
    g->adj[u] = remove_from_list(g->adj[u], v);
    g->adj[v] = remove_from_list(g->adj[v], u);
}

int list_have_edge(Graph g, int u, int v) {
    for (Graph_node t = g->adj[u]; t != NULL; t = t->next) {
        if (t->v == v)
            return 1;
    }
    return 0;
}

void list_print_edges(Graph g) {
    int u;
    Graph_node t;
    for (u=0; u < g->n; u++)
        for (t = g->adj[u]; t != NULL; t = t->next)
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
            list_in_depth_search(g, parent, v, t->v);
}

int *list_find_paths(Graph g, int s) {
    int i, *parent = malloc(g->n * sizeof(int));

    for (i = 0; i < g->n; i++)
        parent[i] = -1;

    list_in_depth_search(g, parent, s, s);
    return parent;
}

void list_print_reverse_path(int v, int *parent) {
    printf("%d", v);
    if(parent[v] != v)
    list_print_reverse_path(parent[v], parent);
}

void list_print_path(int v, int *parent) {
    if(parent[v] != v)
        list_print_path(parent[v], parent);
    printf("%d", v);
}

int *dijkstra(Graph g, int s) {
    int v, *parent = malloc(g->n * sizeof(int));
    Graph_node t;
    p_queue h = create_p_queue(g->n);
    for (v = 0; v < g->n; v++) {
        parent[v] = -1;
        insert(h, v, INT_MAX);
    }
    parent[s] = s;
    decrease_priority(h, s, 0);
    while (!is_prior_queue_empty(h)) {
        v = extract_min(h);
        if (priority(h, v) != INT_MAX)
            for (t = g->adj[v]; t != NULL; t = t->next)
                if (priority(h, v) + t->weight < priority(h, t->v)) {
                    decrease_priority(h, t->v, priority(h, v) + t->weight);
                    parent[t->v] = v;
                }
    }
    return parent;
}

int *list_width_search(Graph g, int s) {
    // Verificar se o vértice inicial é válido
    

    int w, v;
    int *parent = malloc(g->n * sizeof(int)); // Vetor para armazenar os pais
    int *visited = malloc(g->n * sizeof(int)); // Vetor de vértices visitados
    Queue *f = create_queue(g->n); // Cria a fila com capacidade igual ao número de vértices

    // Inicializa os vetores de pais e visitados
    for(v = 0; v < g->n; v++) {
        parent[v] = -1;
        visited[v] = 0;
    }

    // Adiciona o vértice inicial na fila
    enqueue(f, s);
    parent[s] = s; // O vértice inicial é seu próprio pai
    visited[s] = 1; // Marca como visitado

    // Realiza a busca em largura
    while (!is_queue_empty(f)) {
        v = dequeue(f); // Desenfileira um vértice

        // Percorre a lista de adjacência do vértice v
        for (Graph_node aux = g->adj[v]; aux != NULL; aux = aux->next) {
            w = aux->v; // Obtém o índice do vértice adjacente
            if (!visited[w]) { // Verifica se o vértice já foi visitado
                visited[w] = 1; // Marca como visitado
                parent[w] = v; // Define o pai
                enqueue(f, w); // Enfileira o vértice adjacente
            }
        }
    }

    // Libera memória alocada para a fila e o vetor visited
    destroy_queue(f);
    free(visited);

    return parent; // Retorna o vetor de pais
}

int degree_ListAdj(Graph g, int u){
    Graph_node aux;
    int degree = 0;
    for(aux = g->adj[u]; aux != NULL; aux = aux->next){
        degree++;
    }
    return degree;
}

int most_popular_List(Graph g){
    int u, max, max_degree, current_degree;

    max = 0;
    max_degree = degree_ListAdj(g, max);
    for( u = 1; u < g->n; u++) {
        current_degree = degree_ListAdj(g, u);
        if(current_degree > max_degree){
            max = u;
            max_degree = current_degree;
        }
    }
    return max;
}

/*
 * Função que imprime vizinhos dos vizinhos do vértice
 * de forma não repetida
*/
void print_recommendations(Graph g, int u){
    Graph_node aux, rec_aux;
    int *recommended = malloc(g->n * sizeof(int));  
    int i;
    for (i = 0; i < g->n; i++) {
        recommended[i] = 0;
    }

    for (aux = g->adj[u]; aux != NULL; aux = aux->next) {
        int v = aux->v;

        for (rec_aux = g->adj[v]; rec_aux != NULL; rec_aux = rec_aux->next) {
            int w = rec_aux->v;

            if (w != u) {
                if (!recommended[w]) {  //verifica se já não foi recomendado
                    printf("Recommendation: %d\n", w);  
                    recommended[w] = 1;  
                }
            }
        }
    }

    free(recommended);  // Libera a memória alocada para o vetor de recomendados
}

int rec_search_list(Graph g,int* visited, int v, int t){
    int w;
    Graph_node aux;

    if(v == t){
        return 1;
    }
    visited[v] = 1;
    for(aux = g->adj[v]; aux != NULL ; aux = aux->next){
        w = aux->v;
        if(!visited[w]){
            if(rec_search_list(g, visited, w, t)){
                return 1;
            }
        }

    }
    return 0;
}

int has_path_List(Graph g, int start, int end){
    int founded_flag, i;
    int *visited = malloc(g->n * sizeof(int));

    for (i = 0 ; i < g->n ; i++){
        visited[i] = 0;
    }

    founded_flag = rec_search_list(g,visited,start,end);
    free(visited);

    return founded_flag;
}

