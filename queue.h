#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
    int size;
    int capacity; // Campo para armazenar a capacidade máxima
} Queue;

Queue *create_queue(int capacity);
void destroy_queue(Queue *queue);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
int is_empty(Queue *queue);
int get_size(Queue *queue);

#endif
