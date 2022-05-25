#include <stdlib.h>
#include <string.h>

#include "../utils/vector.h"
#include "../shp/types.h"
#include "triangle.h"

#include "bowyer_watson3.h"

#define VAL_TO_POINTER(val) memcpy(malloc(sizeof(val)), &val, sizeof(val))

/* typedef struct {
    Point a,
    Point b
} Edge; */

Vector *bw3_triangulate(Vector *vertices) {
    Vector *_vertices  = VECTOR_NEW();
    Vector *_triangles = VECTOR_NEW();

    for (int i = 0; i < vertices->size; i ++) vector_push(_vertices, vector_index(vertices, i));

    double min_x = ((Point *)vector_index(vertices, 0))->x;
    double min_y = ((Point *)vector_index(vertices, 0))->y;
    double max_x = min_x;
    double max_y = min_y;

    for (size_t i = 0; i < vertices->size; ++ i) {
        Point *vertex = vector_index(vertices, i);

        if (vertex->x < min_x) min_x = vertex->x;
        if (vertex->y < min_y) min_y = vertex->y;
        if (vertex->x > max_x) max_x = vertex->x;
        if (vertex->y > max_y) max_y = vertex->y;
    }

    const double dx        = max_x - min_x;
    const double dy        = max_y - min_y;
    const double delta_max = dx > dy ? dx : dy;
    const double midx      = (min_x + max_x) / 2;
    const double midy      = (min_y + max_y) / 2;

    const Point p1 = (Point){midx - 20 * delta_max, midy - delta_max};
    const Point p2 = (Point){midx, midy + 20 * delta_max};
    const Point p3 = (Point){midx + 20 * delta_max, midy - delta_max};

    Triangle _t = (Triangle){p1, p2, p3};
    vector_push(_triangles, &_t);

    for (int i = 0; i < vertices->size; i ++) {
        Point  *p = vector_index(vertices, i);

        Vector *polygon = VECTOR_NEW();
        Vector *bads    = VECTOR_NEW();

        for (int j = 0; j < _triangles->size; j ++) {
            Triangle *t = vector_index(_triangles, j);

            if (circumcircle_contains(t, p)) {
                vector_push(bads, t);

                vector_push(polygon, VAL_TO_POINTER(((Edge){t->a, t->b})));
                vector_push(polygon, VAL_TO_POINTER(((Edge){t->b, t->c})));
                vector_push(polygon, VAL_TO_POINTER(((Edge){t->c, t->a})));
            }
        }
    }
}
