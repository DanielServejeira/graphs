#include<stdio.h>
#include<stdlib.h>

graph create_graph(int n) {
    int i, j;

    graph g = malloc(sizeof(Adj_list));
    g->n = n;
    g->adj = malloc(n*sizeof(int *));
    for(i=0; i<n; i++) {
        g->adj[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;
    return g;
}

void destroy_graph(graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

void insert_edge(graph g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}
void remove_edge(graph g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}
int have_edge(graph g, int u, int v) {
    return g->adj[u][v];
}

void print_edges(graph g) {
    int u, v;
    for (u = 0; u < g->n; u++)
        for (v = u+1; v < g->n; v++)
            if (g->adj[u][v])
                printf("{%d,%d}\n", u, v);
}

graph read_graph() {
    int n, m, i, u, v;
    graph g;
    scanf("%d %d", &n, &m);
    g = create_graph(n);
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insert_edge(g, u, v);
    }
    return g;
}

int degree(graph g, int u) {
    int v, degree = 0;
    for (v = 0; v < g->n; v++)
        if (g->adj[u][v])
            degree++;
    return degree;
}

int most_popular(graph g) {
    int u, max, max_degree , current_degree;
    max = 0;
    max_degree = degree(g, 0);
    for (u = 1; u < g->n; u++) {
        current_degree = degree(g, u);
        if (current_degree > max_degree) {
            max_degree = current_degree;
            max = u;
        }
    }
    return max;
}

void print_recommendations(graph g, int u) {
    int v, w;
    for (v=0; v < g->n; v++) {
        if (g->adj[u][v]) {
            for (w = 0; w < g->n; w++) {
                if (g->adj[v][w] && w != u && !g->adj[u][w])
                    printf("%d\n", w);
            }
        }
    }
}

int path_exists(graph g, int s, int t) {
    int found , i, *visited = malloc(g->n * sizeof(int));
    for (i=0; i < g->n; i++)
        visited[i] = 0;
    found = rec_search(g, visited , s, t);
    free(visited);
    return found;
}
int rec_search(graph g, int *visited , int v, int t) {
    int w;
    if (v == t)
        return 1;
    visited[v] = 1;
    for (w=0; w < g->n; w++)
        if (g->adj[v][w] && !visited[w])
            if (rec_search(g, visited , w, t))
                return 1;
    return 0;
}


