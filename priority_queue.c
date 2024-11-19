#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "priority_queue.h"

/**
 * @brief Creates a priority queue with a specified size.
 *
 * This function allocates memory for a priority queue structure and its internal arrays.
 * It initializes the priority queue with the given size, setting all index values to -1.
 *
 * @param size The maximum number of elements the priority queue can hold.
 * @return A pointer to the newly created priority queue.
 */
p_queue create_p_queue(int size) {
    p_queue h = malloc(sizeof(Priority_queue));
    h->v = malloc(size * sizeof(Item));
    h->index = malloc(size * sizeof(int));
    h->n = 0;
    h->size = size;
    for (int i = 0; i < size; i++) {
        h->index[i] = -1;
    }
    return h;
}

/**
 * @brief Inserts a new element into the priority queue.
 *
 * This function inserts a new element with a specified vertex and priority into the priority queue.
 * It updates the index array to store the position of the element in the priority queue.
 *
 * @param h The priority queue in which the element is to be inserted.
 * @param vertex The vertex of the element to be inserted.
 * @param priority The priority of the element to be inserted.
 */
void insert(p_queue h, int vertex, int priority) {
    h->v[h->n].vertex = vertex;
    h->v[h->n].priority = priority;
    h->index[vertex] = h->n;
    h->n++;
}

/**
 * @brief Decreases the priority of an element in the priority queue.
 *
 * This function decreases the priority of an element in the priority queue to a new value.
 * It updates the priority of the element and adjusts the position of the element in the priority queue.
 *
 * @param h The priority queue in which the element is stored.
 * @param vertex The vertex of the element whose priority is to be decreased.
 * @param new_priority The new priority of the element.
 */
void decrease_priority(p_queue h, int vertex, int new_priority) {
    int i = h->index[vertex];
    h->v[i].priority = new_priority;
    while (i > 0 && h->v[i].priority < h->v[(i - 1) / 2].priority) {
        Item temp = h->v[i];
        h->v[i] = h->v[(i - 1) / 2];
        h->v[(i - 1) / 2] = temp;
        h->index[h->v[i].vertex] = i;
        h->index[h->v[(i - 1) / 2].vertex] = (i - 1) / 2;
        i = (i - 1) / 2;
    }
}

/**
 * @brief Extracts the element with the minimum priority from the priority queue.
 *
 * This function extracts the element with the minimum priority from the priority queue.
 * It removes the element from the priority queue and adjusts the position of the remaining elements.
 *
 * @param h The priority queue from which the element is to be extracted.
 * @return The vertex of the element with the minimum priority.
 */
int extract_min(p_queue h) {
    int min_vertex = h->v[0].vertex;
    h->v[0] = h->v[h->n - 1];
    h->index[h->v[0].vertex] = 0;
    h->n--;
    int i = 0;
    while (2 * i + 1 < h->n) {
        int j = 2 * i + 1;
        if (j + 1 < h->n && h->v[j + 1].priority < h->v[j].priority) {
            j++;
        }
        if (h->v[i].priority <= h->v[j].priority) {
            break;
        }
        Item temp = h->v[i];
        h->v[i] = h->v[j];
        h->v[j] = temp;
        h->index[h->v[i].vertex] = i;
        h->index[h->v[j].vertex] = j;
        i = j;
    }
    return min_vertex;
}

/**
 * @brief Checks if the priority queue is empty.
 *
 * This function checks if the priority queue is empty.
 *
 * @param h The priority queue to be checked.
 * @return 1 if the priority queue is empty, 0 otherwise.
 */
int is_prior_queue_empty(p_queue h) {
    return h->n == 0;
}

/**
 * @brief Returns the priority of an element in the priority queue.
 *
 * This function returns the priority of an element in the priority queue.
 *
 * @param h The priority queue in which the element is stored.
 * @param vertex The vertex of the element whose priority is to be returned.
 * @return The priority of the element.
 */
int priority(p_queue h, int vertex) {
    int i = h->index[vertex];
    if (i == -1) {
        return INT_MAX;
    }
    return h->v[i].priority;
}