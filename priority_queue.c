#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "priority_queue.h"

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

void insert(p_queue h, int vertex, int priority) {
    h->v[h->n].vertex = vertex;
    h->v[h->n].priority = priority;
    h->index[vertex] = h->n;
    h->n++;
}

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

int is_empty(p_queue h) {
    return h->n == 0;
}

int priority(p_queue h, int vertex) {
    int i = h->index[vertex];
    if (i == -1) {
        return INT_MAX;
    }
    return h->v[i].priority;
}