#ifndef STD_VECTOR
#define STD_VECTOR

#include <stddef.h>

#define VECTOR_INIT_CAPACITY 8
#define VECTOR_MULTIPLY      1.5

typedef struct _Vector Vector;

struct _Vector {
    void   **data;
    size_t capacity;
    size_t size;
};

Vector *vector_init   (Vector *v);
void    vector_push   (Vector *v, void *item);
void    vector_delete (Vector *v, size_t index);
void    vector_clear  (Vector *v);
void    vector_free   (Vector *v);
void   *vector_index  (Vector *v, size_t index);
void    vector_resize (Vector *v, size_t new_capacity);
void    vector_set    (Vector *v, size_t index, void *item);
void    vector_insert (Vector *v, size_t index, void *item);

#define VECTOR_NEW() vector_init((Vector*)(malloc(sizeof(void*) * VECTOR_INIT_CAPACITY + sizeof(size_t) * 2)))

#endif
