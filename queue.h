#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
    int size;
} Queue;

Queue *create_queue();
void destroy_queue(Queue *queue);
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void *peek(Queue *queue);
int is_empty(Queue *queue);
int get_size(Queue *queue);

#endif