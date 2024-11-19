#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Cria uma fila com capacidade definida
Queue *create_queue(int capacity) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    queue->capacity = capacity; // Define a capacidade
    return queue;
}

// Libera toda a memória associada à fila
void destroy_queue(Queue *queue) {
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

// Insere um elemento na fila
void enqueue(Queue *queue, int data) {
    if (queue->size == queue->capacity) {
        fprintf(stderr, "Queue is full. Cannot enqueue.\n");
        return;
    }

    QueueNode *new_QueueNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (!new_QueueNode) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    new_QueueNode->data = data;
    new_QueueNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = new_QueueNode;
    } else {
        queue->rear->next = new_QueueNode;
        queue->rear = new_QueueNode;
    }
    queue->size++;
}

// Remove e retorna o elemento da frente da fila
int dequeue(Queue *queue) {
    if (is_queue_empty(queue)) {
        fprintf(stderr, "Queue is empty. Cannot dequeue.\n");
        return -1; // Retorna -1 para indicar falha
    }

    QueueNode *temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

// Retorna o elemento da frente da fila sem removê-lo
int peek(Queue *queue) {
    if (is_queue_empty(queue)) {
        fprintf(stderr, "Queue is empty. Cannot peek.\n");
        return -1; // Retorna -1 para indicar fila vazia
    }
    return queue->front->data;
}

// Verifica se a fila está vazia
int is_queue_empty(Queue *queue) {
    return queue->size == 0;
}

// Retorna o tamanho atual da fila
int get_size(Queue *queue) {
    return queue->size;
}
