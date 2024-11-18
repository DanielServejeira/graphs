#include<stdio.h>

typedef enum {
    ADJACENCY_LIST = 1,
    ADJACENCY_MATRIX
} GraphType;

void run_english_interface() {
    GraphType menu;

    printf("Insert an option:\n"
           "\n[1] <- Adjacency List Graph"
           "\n[2] <- Adjacency Matrix Graph\n");

    while (scanf("%d", (int*)&menu) != 1 || menu < ADJACENCY_LIST || menu > ADJACENCY_MATRIX) {
        printf("Invalid option. Please select a valid graph type:\n"
               "\n[1] <- Adjacency List Graph"
               "\n[2] <- Adjacency Matrix Graph\n");
        while (getchar() != '\n'); // Clear the input buffer
    }

    switch(menu) {
        case ADJACENCY_LIST:
            
            break;

        case ADJACENCY_MATRIX:
            
            break;
    }
}