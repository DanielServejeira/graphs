#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
    int capacity; // Campo para armazenar a capacidade máxima
} Queue;

Queue *create_queue(int capacity);
void destroy_queue(Queue *queue);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
int is_queue_empty(Queue *queue);
int get_size(Queue *queue);

#endif
