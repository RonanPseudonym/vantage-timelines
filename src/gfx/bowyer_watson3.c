#include "../utils/vector.h"
#include "../shp/types.h"

#include "bowyer_watson3.h"

Vector *bw3_triangulate(Vector *vertices) {
    Vector *_vertices;
    Vector *_triangles;

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

    const Point v1 = (Point){midx - 20 * delta_max, midy - delta_max};
    const Point v2 = (Point){midx, midy + 20 * delta_max};
    const Point v3 = (Point){midx + 20 * delta_max, midy - delta_max};

    vector_push(
}
