#include<stdio.h>
#include<locale.h>

typedef enum {
    ADJACENCY_LIST = 1,
    ADJACENCY_MATRIX
} GraphType;

void run_portuguese_interface() {
    setlocale(LC_ALL, "Portuguese");

    GraphType menu;

    printf("Insira uma opção:\n"
           "\n[1] <- Lista de Adjacência"
           "\n[2] <- Matriz de Adjacência\n");

    while (scanf("%d", (int*)&menu) != 1 || menu < ADJACENCY_LIST || menu > ADJACENCY_MATRIX) {
        printf("Opção inválida. Por favor, selecione um tipo de grafo válido:\n"
               "\n[1] <- Lista de Adjacência"
               "\n[2] <- Matriz de Adjacência\n");
        while (getchar() != '\n'); // Clear the input buffer
    }

    switch(menu) {
        case ADJACENCY_LIST:
            
            break;

        case ADJACENCY_MATRIX:
            
            break;
    }
}