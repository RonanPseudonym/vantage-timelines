#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "../utils/vector.h"
#include "../shp/types.h"

#include "triangle.h"
#include "bowyer_watson.h"
#include "convex_hull.h"

#define GEN_EDGE(TRIANGLE, INDEX, EDGE) switch (INDEX) {\
    case 0:\
        EDGE[0] = TRIANGLE->a;\
        EDGE[1] = TRIANGLE->b;\
        break;\
    case 1:\
        EDGE[0] = TRIANGLE->b;\
        EDGE[1] = TRIANGLE->c;\
        break;\
    case 2:\
        EDGE[0] = TRIANGLE->c;\
        EDGE[1] = TRIANGLE->a;\
        break;\
}\

double vector_distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double triangle_circumcircle_radius(Triangle t) {
    double a = vector_distance(t.a, t.b);
    double b = vector_distance(t.b, t.c);
    double c = vector_distance(t.c, t.a);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

bool point_inside_circumcircle(Point p, Triangle t) {
    double x = p.x - t.a.x;
    double y = p.y - t.a.y;
    double r = sqrt(x * x + y * y);
    return r <= triangle_circumcircle_radius(t);
}

/* void get_edge(Triangle t, int index, Point e[2]) {
    switch (index) {
        case 0:
            e[0] = t.a;
            e[1] = t.b;
            break;
        case 1:
            e[0] = t.b;
            e[1] = t.c;
            break;
        case 2:
            e[0] = t.c;
            e[1] = t.a;
            break;
    }
} */

bool edge_not_shared(Point e[2], Vector *bad_triangles) {
    for (int i = 0; i < bad_triangles->size; i++) {
        Triangle *t = (Triangle*)vector_index(bad_triangles, i);

        for (int j = 0; j < 3; j ++) {
            Point be[2];

            GEN_EDGE(t, j, be);

            // check if e and be overlap
            if (e[0].x == be[0].x && e[0].y == be[0].y && e[1].x == be[1].x && e[1].y == be[1].y) { // This might be too demanding? Like if they're different sizes but still overlap, it might still count. idk i just want this to work
                return false;
            }
        }
    }
    return true;
}

Vector *bowyer_watson(int num_points, Point points[num_points]) {
    Vector *triangulation = VECTOR_NEW();

    Triangle striangle = super_triangle(quick_hull(num_points, points));
    vector_push(triangulation, &striangle);

    for (int i = 0; i < num_points; i ++) {
        Point   point = points[i];
        Vector *bad_triangles = VECTOR_NEW();

        for (int j = 0; j < triangulation->size; j ++) {
            Triangle *triangle = (Triangle *)vector_index(triangulation, j);
            if (point_inside_circumcircle(point, *triangle)) {
                vector_push(bad_triangles, triangle);
            }
        }

        printf("%d bad triangles\n", bad_triangles->size);

        Vector *polygon = VECTOR_NEW();
        for (int j = 0; j < bad_triangles->size; j ++) {
            Triangle *triangle = (Triangle *)vector_index(bad_triangles, j);
            for (int k = 0; k < 3; k ++) {
                Point edge[2];
                GEN_EDGE(triangle, k, edge);

                if (edge_not_shared(edge, bad_triangles)) {
                    vector_push(polygon, memcpy(malloc(sizeof(Point)), &edge[0], sizeof(Point))); // Might need to add only one here? But probably not

                    vector_push(polygon, memcpy(malloc(sizeof(Point)), &edge[1], sizeof(Point))); // Might need to add only one here? But probably not
                }
            }
        }

        for (int j = 0; j < bad_triangles->size; j ++) {
            vector_delete(triangulation, j);
        }

        for (int j = 0; j < polygon->size; j += 2) {
            // dereference Point[2] from polygon[j]
            Triangle *new_tri = malloc(sizeof(Triangle));

            new_tri->a = *(Point *)vector_index(polygon, j);
            new_tri->b = *(Point *)vector_index(polygon, j + 1);
            new_tri->c = point;

            vector_push(triangulation, new_tri);
        }
    }

    for (int i = 0; i < triangulation->size; i ++) { // Should be i = 1 maybe??
        Triangle *t = (Triangle *)vector_index(triangulation, i);

        for (int j = 0; j < 3; j ++) {
            Point edge;

            switch (j) {
                case 0:
                    edge = t->a;
                    break;
                case 1:
                    edge = t->b;
                    break;
                case 2:
                    edge = t->c;
                    break;
            }

            if (edge.x == striangle.a.x && edge.y == striangle.a.y) {
                vector_delete(triangulation, i);
                break;
            }
        }
    }

    return triangulation;
}
