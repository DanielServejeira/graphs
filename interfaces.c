#include <stdio.h>
#include <locale.h>

#include "adjacency_list.h"
#include "adjacency_matrix.h"

typedef enum {
    ADJACENCY_LIST = 1,
    ADJACENCY_MATRIX
} GraphType;

void run_english_interface() {
    GraphType menu;

    printf("Insert an option:\n"
           "\n[1] <- Adjacency List Graph"
           "\n[2] <- Adjacency Matrix Graph\n\n");

    while (scanf("%d", (int*)&menu) != 1 || menu < ADJACENCY_LIST || menu > ADJACENCY_MATRIX) {
        printf("Invalid option. Please select a valid graph type:\n"
               "\n[1] <- Adjacency List Graph"
               "\n[2] <- Adjacency Matrix Graph\n\n");
        while (getchar() != '\n'); // Clear the input buffer
    }

    switch(menu) {
        case ADJACENCY_LIST:
            Adj_list *graph = NULL;
            int choice;
            do
            {
                printf("Adjacency list graph operations\n"
                       "\n[1] <- Create graph"
                       "\n[2] <- Destroy graph"
                       "\n[3] <- Insert edge"
                       "\n[4] <- Remove edge"
                       "\n[5] <- Check if edge exists"
                       "\n[6] <- Print edges"
                       "\n[7] <- Find connected components"
                       "\n[8] <- Find paths"
                       "\n[9] <- Find shortest path"
                       "\n[0] <- Exit\n\n");

                scanf("%d", &choice);
                
                switch (choice)
                {
                case 0:
                    break;

                case 1:
                    if (graph != NULL)
                    {
                        printf("Graph already exists. Please destroy it before creating a new one.\n\n");
                        break;
                    }
                    int n;
                    printf("Enter the number of vertices: ");
                    scanf("%d", &n);
                    graph = list_create_graph(n);
                    printf("Graph created successfully.\n\n");
                    break;

                case 2:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before destroying it.\n\n");
                        break;
                    }
                    list_destroy_graph(graph);
                    graph = NULL;
                    printf("Graph destroyed successfully.\n\n");
                    break;

                case 3:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before inserting an edge.\n\n");
                        break;
                    }
                    int u, v;
                    printf("Enter the vertices to insert the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    list_insert_edge(graph, u, v);
                    printf("Edge inserted successfully.\n\n");
                    break;

                case 4:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before removing an edge.\n\n");
                        break;
                    }
                    printf("Enter the vertices to remove the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    list_remove_edge(graph, u, v);
                    printf("Edge removed successfully.\n\n");
                    break;

                case 5:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before checking if an edge exists.\n\n");
                        break;
                    }
                    printf("Enter the vertices to check if the edge exists (u v): ");
                    scanf("%d %d", &u, &v);
                    if (list_have_edge(graph, u, v))
                        printf("The edge {%d,%d} exists.\n\n", u, v);
                    else
                        printf("The edge {%d,%d} does not exist.\n\n", u, v);
                    break;

                case 6:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before printing its edges.\n\n");
                        break;
                    }
                    list_print_edges(graph);
                    break;

                case 7:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding its connected components.\n\n");
                        break;
                    }
                    int *components = list_find_components(graph);
                    printf("Graph has %d connected components.\n\n", components[0]);
                    free(components);
                    break;

                case 8:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding paths.\n\n");
                        break;
                    }
                    int s;
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);

                    int *p = (int *)malloc(graph->n * sizeof(int));

                    list_in_depth_search(graph, p, graph->adj[0], s);
                    for (int i = 0; i < graph->n; i++)
                    {
                        printf("Path from %d to %d: ", s, i);
                        list_print_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                case 9:
                    if (graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the shortest path.\n\n");
                        break;
                    }
                    printf("Enter the destination vertex: ");
                    scanf("%d", &v);
                    int *path = list_width_search(graph, v);
                    printf("Shortest path from %d to %d: ", s, v);
                    list_print_reverse_path(v, path);
                    printf("\n");
                    free(path);
                    break;

                default:
                    printf("Invalid option. Please select a valid operation.\n\n");
                    break;
                }
            } while (choice != 0);
            
            break;

        case ADJACENCY_MATRIX:

            break;
    }
}

void run_portuguese_interface() {
    setlocale(LC_ALL, "Portuguese");

    GraphType menu;

    printf("Insira uma opção:\n"
           "\n[1] <- Grafo de Lista de Adjacência"
           "\n[2] <- Grafo de Matriz de Adjacência\n\n");

    while (scanf("%d", (int*)&menu) != 1 || menu < ADJACENCY_LIST || menu > ADJACENCY_MATRIX) {
        printf("Opção inválida. Por favor, selecione um tipo de grafo válido:\n"
               "\n[1] <- Grafo de Lista de Adjacência"
               "\n[2] <- Grafo de Matriz de Adjacência\n\n");
        while (getchar() != '\n'); // Clear the input buffer
    }

    switch(menu) {
        case ADJACENCY_LIST:

            break;

        case ADJACENCY_MATRIX:

            break;
    }
}
