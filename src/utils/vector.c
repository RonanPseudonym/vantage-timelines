#include <stddef.h>
#include <stdlib.h>

#include "vector.h"

Vector* vector_init(Vector *v) {
    v->size = 0;
    v->capacity = VECTOR_INIT_CAPACITY;
    v->data = malloc(sizeof(void *) * v->capacity);
    return v;
}

void vector_resize(Vector *v, size_t new_capacity) {
    v->capacity = new_capacity;
    v->data = realloc(v->data, sizeof(void *) * v->capacity);
}

void vector_push(Vector *v, void *item) {
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity * VECTOR_MULTIPLY);
    }
    v->data[v->size++] = item;
}

void vector_set(Vector *v, size_t index, void *item) {
    v->data[index] = item;
}

void vector_insert(Vector *v, size_t index, void *item) {
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity * VECTOR_MULTIPLY);
    }
    for (size_t i = v->size; i > index; i--) {
        v->data[i] = v->data[i - 1];
    }
    v->data[index] = item;
    v->size++;
}

void *vector_index(Vector *v, size_t index) {
    return v->data[index];
}

void vector_delete(Vector *v, size_t index) { // Might have to account for resizing?
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

void vector_free(Vector *v) {
    free(v->data);
}
