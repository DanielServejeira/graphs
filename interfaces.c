#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "adjacency_list.h"
#include "adjacency_matrix.h"

typedef enum {
    ADJACENCY_LIST = 1,
    ADJACENCY_MATRIX
} GraphType;


/**
 * @brief Runs the English interface for graph operations.
 *
 * This function presents a menu to the user to select the type of graph representation
 * (Adjacency List or Adjacency Matrix) and then provides various operations that can be
 * performed on the selected graph type. The user can create, destroy, insert edges, remove edges,
 * check if an edge exists, print edges, find connected components, find paths, and find the shortest path.
 *
 * The function uses a loop to continuously prompt the user for input until the user chooses to exit.
 *
 * Operations for Adjacency List Graph:
 * - Create graph
 * - Destroy graph
 * - Insert edge
 * - Remove edge
 * - Check if edge exists
 * - Print edges
 * - Find connected components
 * - Find paths
 * - Find shortest path
 */
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

    AdjListGraph adj_list_graph = NULL;
    AdjMatrixGraph adj_matrix_graph = NULL;
    int choice;
    switch(menu) {
        case ADJACENCY_LIST:
            do
            {
                printf("Adjacency LIST graph operations\n"
                       "\n[1] <- Create graph"
                       "\n[2] <- Destroy graph"
                       "\n[3] <- Insert edge"
                       "\n[4] <- Remove edge"
                       "\n[5] <- Check if edge exists"
                       "\n[6] <- Print edges"
                       "\n[7] <- Find connected components"
                       "\n[8] <- Find paths"
                       "\n[9] <- Find shortest path"
                       "\n[10] <- Dijkstra"
                       "\n[11] <- Minimum Spanning Tree"
                       "\n[0] <- Exit\n\n");

                scanf("%d", &choice);
                
                int n, u, v, weight, s;
                int *components, *p, *path;

                switch (choice)
                {
                case 0:
                    break;

                case 1:
                    if (adj_list_graph != NULL)
                    {
                        printf("Graph already exists. Please destroy it before creating a new one.\n\n");
                        break;
                    }
                    printf("Enter the number of vertices: ");
                    scanf("%d", &n);
                    adj_list_graph = list_create_graph(n);
                    printf("Graph created successfully.\n\n");
                    break;

                case 2:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before destroying it.\n\n");
                        break;
                    }
                    list_destroy_graph(adj_list_graph);
                    adj_list_graph = NULL;
                    printf("Graph destroyed successfully.\n\n");
                    break;

                case 3:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before inserting an edge.\n\n");
                        break;
                    }
                    printf("Enter the vertices to insert the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    printf("Enter the weight of the edge: ");
                    scanf("%d", &weight);
                    list_insert_edge(adj_list_graph, u, v, weight);
                    printf("Edge inserted successfully.\n\n");
                    break;

                case 4:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before removing an edge.\n\n");
                        break;
                    }
                    printf("Enter the vertices to remove the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    list_remove_edge(adj_list_graph, u, v);
                    printf("Edge removed successfully.\n\n");
                    break;

                case 5:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before checking if an edge exists.\n\n");
                        break;
                    }
                    printf("Enter the vertices to check if the edge exists (u v): ");
                    scanf("%d %d", &u, &v);
                    if (list_have_edge(adj_list_graph, u, v))
                        printf("The edge {%d,%d} exists.\n\n", u, v);
                    else
                        printf("The edge {%d,%d} does not exist.\n\n", u, v);
                    break;

                case 6:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before printing its edges.\n\n");
                        break;
                    }
                    list_print_edges(adj_list_graph);
                    break;

                case 7:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding its connected components.\n\n");
                        break;
                    }
                    components = list_find_components(adj_list_graph);
                    printf("Graph has %d connected components.\n\n", components[0]);
                    free(components);
                    break;

                case 8:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding paths.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);

                    p = (int *)malloc(adj_list_graph->n * sizeof(int));

                    list_in_depth_search(adj_list_graph, p, adj_list_graph->adj[0]->v, s);
                    for (int i = 0; i < adj_list_graph->n; i++)
                    {
                        printf("Path from %d to %d: ", s, i);
                        list_print_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                case 9:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the shortest path.\n\n");
                        break;
                    }
                    printf("Enter the destination vertex: ");
                    scanf("%d", &v);
                    path = list_width_search(adj_list_graph, v);
                    printf("Shortest path from %d to %d: ", s, v);
                    list_print_reverse_path(v, path);
                    printf("\n");
                    free(path);
                    break;

                case 10:
                    if (adj_list_graph == NULL) {
                        printf("Graph does not exist. Please create it before finding the shortest path.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = dijkstra(adj_list_graph, s);
                    for (int i = 0; i < adj_list_graph->n; i++) {
                        printf("Shortest path from %d to %d: ", s, i);
                        list_print_reverse_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;
                case 11:
                    if (adj_list_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the minimum spanning tree.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = dijkstra(adj_list_graph, s);
                    for (int i = 0; i < adj_list_graph->n; i++)
                    {
                        printf("Minimum spanning tree from %d to %d: ", s, i);
                        list_print_reverse_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                default:
                    printf("Invalid option. Please select a valid operation.\n\n");
                    break;
                }
            } while (choice != 0);
            
            break;

        case ADJACENCY_MATRIX:
            do
            {
                printf("Adjacency MATRIX graph operations\n"
                       "\n[1] <- Create graph"
                       "\n[2] <- Destroy graph"
                       "\n[3] <- Insert edge"
                       "\n[4] <- Remove edge"
                       "\n[5] <- Check if edge exists"
                       "\n[6] <- Print edges"
                       "\n[7] <- Get vertex degree"
                       "\n[8] <- Find most popular vertex"
                       "\n[9] <- Print recommendations"
                       "\n[10] <- Check if path exists"
                       "\n[11] <- Breadth First Search"
                       "\n[12] <- Depth First Search"
                       "\n[13] <- Find connected components"
                       "\n[14] <- Dijkstra"
                       "\n[15] <- Minimum Spanning Tree"
                       "\n[0] <- Exit\n\n");

                scanf("%d", &choice);
                
                int n, u, v, weight, s;
                int *components, *p;

                switch (choice)
                {
                case 0:
                    break;

                case 1:
                    if (adj_matrix_graph != NULL)
                    {
                        printf("Graph already exists. Please destroy it before creating a new one.\n\n");
                        break;
                    }
                    printf("Enter the number of vertices: ");
                    scanf("%d", &n);
                    adj_matrix_graph = matrix_create_graph(n);
                    printf("Graph created successfully.\n\n");
                    break;

                case 2:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before destroying it.\n\n");
                        break;
                    }
                    matrix_destroy_graph(adj_matrix_graph);
                    adj_matrix_graph = NULL;
                    printf("Graph destroyed successfully.\n\n");
                    break;

                case 3:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before inserting an edge.\n\n");
                        break;
                    }
                    printf("Enter the vertices to insert the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    printf("Enter the weight of the edge: ");
                    scanf("%d", &weight);
                    matrix_insert_edge(adj_matrix_graph, u, v, weight);
                    printf("Edge inserted successfully.\n\n");
                    break;

                case 4:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before removing an edge.\n\n");
                        break;
                    }
                    printf("Enter the vertices to remove the edge (u v): ");
                    scanf("%d %d", &u, &v);
                    matrix_remove_edge(adj_matrix_graph, u, v);
                    printf("Edge removed successfully.\n\n");
                    break;

                case 5:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before checking if an edge exists.\n\n");
                        break;
                    }
                    printf("Enter the vertices to check if the edge exists (u v): ");
                    scanf("%d %d", &u, &v);
                    if (matrix_have_edge(adj_matrix_graph, u, v))
                        printf("The edge {%d,%d} exists.\n\n", u, v);
                    else
                        printf("The edge {%d,%d} does not exist.\n\n", u, v);
                    break;

                case 6:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before printing its edges.\n\n");
                        break;
                    }
                    matrix_print_edges(adj_matrix_graph);
                    break;

                case 7:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the degree of a vertex.\n\n");
                        break;
                    }
                    printf("Enter the vertex to find its degree: ");
                    scanf("%d", &u);
                    printf("The degree of vertex %d is %d.\n\n", u, matrix_degree(adj_matrix_graph, u));
                    break;

                case 8:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the most popular vertex.\n\n");
                        break;
                    }
                    printf("The most popular vertex is %d.\n\n", matrix_most_popular(adj_matrix_graph));
                    break;

                case 9:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before printing recommendations.\n\n");
                        break;
                    }
                    printf("Enter the vertex to print recommendations: ");
                    scanf("%d", &u);
                    matrix_print_recommendations(adj_matrix_graph, u);
                    break;

                case 10:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before checking if a path exists.\n\n");
                        break;
                    }
                    printf("Enter the source and target vertices to check if a path exists (s t): ");
                    scanf("%d %d", &s, &v);
                    if (matrix_path_exists(adj_matrix_graph, s, v))
                        printf("A path exists between %d and %d.\n\n", s, v);
                    else
                        printf("No path exists between %d and %d.\n\n", s, v);
                    break;

                case 11:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before performing a breadth-first search.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = matrix_width_search(adj_matrix_graph, s);
                    printf("Shortest path from %d to %d: ", s, v);
                    matrix_print_reverse_path(v, p);
                    printf("\n");
                    free(p);
                    break;

                case 12:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before performing a depth-first search.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = (int *)malloc(adj_matrix_graph->n * sizeof(int));
                    p = matrix_find_paths(adj_matrix_graph, s);
                    for (int i = 0; i < adj_matrix_graph->n; i++)
                    {
                        printf("Path from %d to %d: ", s, i);
                        matrix_print_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                case 13:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding its connected components.\n\n");
                        break;
                    }
                    components = matrix_find_components(adj_matrix_graph);
                    printf("Graph has %d connected components.\n\n", components[0]);
                    free(components);
                    break;

                case 14:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the shortest path.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = dijkstra(adj_matrix_graph, s);
                    for (int i = 0; i < adj_matrix_graph->n; i++)
                    {
                        printf("Shortest path from %d to %d: ", s, i);
                        matrix_print_reverse_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                case 15:
                    if (adj_matrix_graph == NULL)
                    {
                        printf("Graph does not exist. Please create it before finding the minimum spanning tree.\n\n");
                        break;
                    }
                    printf("Enter the source vertex: ");
                    scanf("%d", &s);
                    p = dijkstra(adj_matrix_graph, s);
                    for (int i = 0; i < adj_matrix_graph->n; i++)
                    {
                        printf("Minimum spanning tree from %d to %d: ", s, i);
                        matrix_print_reverse_path(i, p);
                        printf("\n");
                    }
                    free(p);
                    break;

                default:
                    printf("Invalid option. Please select a valid operation.\n\n");
                    break;
                }
            } while (choice != 0);
            
            break;
    }
}


/**
 * @brief Runs the Portuguese interface for selecting the graph type.
 *
 * This function sets the locale to Portuguese and prompts the user to select a type of graph.
 * The user can choose between an adjacency list graph or an adjacency matrix graph.
 * The function ensures that the user input is valid and handles invalid inputs by prompting the user again.
 *
 * @param None
 * @return None
 */
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
