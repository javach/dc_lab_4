#include <stdlib.h>
#include <stddef.h>

struct Element {
    long value;
    struct Element* next;
};

struct Queue {
    int size;
    struct Element *head;
    struct Element *tail;
};

struct Queue init_queue() {
    struct Queue queue;
    queue.size = 0;
    return queue;
}

void queue_push(struct Queue *queue, long value) {
    struct Element *new_element = (struct Element*) malloc(sizeof(struct Element));
    new_element->value = value;
    if (queue->size == 0) {
        queue->head = new_element;
        queue->tail = new_element;
    } else {
        queue->tail->next = new_element;
        queue->tail = new_element;
    }
    queue->size++;
}

long queue_pop(struct Queue *queue) {
    if (queue->size == 0)
        return -1;
    queue->size--;
    long value = queue->head->value;
    struct Element *old = queue->head;
    queue->head = queue->head->next;
    free(old);
    return value;
}

long queue_get_head(struct Queue queue) {
    if (queue.size == 0)
        return -1;
    return queue.head->value;
}

typedef struct Queue Queue;