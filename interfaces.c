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