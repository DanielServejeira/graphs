#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
    int vertex;
    int priority;
} Item;

typedef struct {
    Item *v;
    int *index;
    int n;
    int size;
} Priority_queue, *p_queue;

p_queue create_p_queue(int size);
void insert(p_queue h, int vertex, int priority);
void decrease_priority(p_queue h, int vertex, int new_priority);
int extract_min(p_queue h);
int is_prior_queue_empty(p_queue h);
int priority(p_queue h, int vertex);

#endif
