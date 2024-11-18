#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue *create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void destroy_queue(Queue *queue) {
    while (queue->size > 0) {
        Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        queue->size--;
    }
    free(queue);
}

void enqueue(Queue *queue, void *data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

void *dequeue(Queue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    Node* temp = queue->front;
    void* data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

void *peek(Queue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "Queue is empty. Cannot peek.\n");
        return NULL;
    }
    return queue->front->data;
}

int is_empty(Queue *queue) {
    return queue->size == 0;
}

int get_size(Queue *queue) {
    return queue->size;
}