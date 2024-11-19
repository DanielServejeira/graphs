#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief Creates a queue with a specified capacity.
 *
 * This function allocates memory for a new Queue structure and initializes its
 * front and rear pointers to NULL, its size to 0, and its capacity to the specified value.
 * If memory allocation fails, the function prints an error message to stderr and exits the program.
 *
 * @param capacity The maximum number of elements that the queue can hold.
 * @return A pointer to the newly created Queue structure.
 */
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

/**
 * @brief Destroys a queue and frees all associated memory.
 *
 * This function dequeues all elements from the queue and frees the memory allocated for each QueueNode.
 * It then frees the memory allocated for the Queue structure itself.
 *
 * @param queue A pointer to the Queue structure to be destroyed.
 */
void destroy_queue(Queue *queue) {
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

/**
 * @brief Enqueues a new element into the queue.
 *
 * This function creates a new QueueNode with the specified data and enqueues it into the queue.
 * If the queue is full, the function prints an error message to stderr and returns without enqueuing the element.
 *
 * @param queue A pointer to the Queue structure.
 * @param data The data to be enqueued.
 */
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

/**
 * @brief Dequeues an element from the queue.
 *
 * This function removes the element at the front of the queue and returns its data.
 * If the queue is empty, the function prints an error message to stderr and returns -1 to indicate failure.
 *
 * @param queue A pointer to the Queue structure.
 * @return The data of the element dequeued from the queue, or -1 if the queue is empty.
 */
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

/**
 * @brief Peeks at the element at the front of the queue.
 *
 * This function returns the data of the element at the front of the queue without dequeuing it.
 * If the queue is empty, the function prints an error message to stderr and returns -1 to indicate an empty queue.
 *
 * @param queue A pointer to the Queue structure.
 * @return The data of the element at the front of the queue, or -1 if the queue is empty.
 */
int peek(Queue *queue) {
    if (is_queue_empty(queue)) {
        fprintf(stderr, "Queue is empty. Cannot peek.\n");
        return -1; // Retorna -1 para indicar fila vazia
    }
    return queue->front->data;
}

/**
 * @brief Checks if the queue is empty.
 *
 * This function checks if the queue is empty by verifying if the front pointer is NULL.
 *
 * @param queue A pointer to the Queue structure.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int is_queue_empty(Queue *queue) {
    return queue->size == 0;
}

/**
 * @brief Gets the size of the queue.
 *
 * This function returns the number of elements currently in the queue.
 *
 * @param queue A pointer to the Queue structure.
 * @return The number of elements in the queue.
 */
int get_size(Queue *queue) {
    return queue->size;
}
