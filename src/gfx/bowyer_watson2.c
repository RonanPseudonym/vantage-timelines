#include "../utils/vector.h"
#include "bowyer_watson2.h"
#include "triangle.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

Vector *triangles;
Vector *points;
Vector *initpoints;

#define VAL_TO_POINTER(val, size) memcpy(malloc(size), &val, size)

Point tri_get_center(Triangle t) {
    double a=t.b.x-t.a.x;
    double b=t.b.y-t.a.y;
    double c=t.c.x-t.a.x;
    double d=t.c.y-t.a.y;
    double e=a*(t.a.x+t.b.x)+b*(t.a.y+t.b.y);
    double f=c*(t.a.x+t.c.x)+d*(t.a.y+t.c.y);
    double g=2.0*(a*(t.c.y-t.b.y)-b*(t.c.x-t.b.x));
    // if (g==0) return NULL;
    double px=(d*e-b*f)/g;
    double py=(a*f-c*e)/g;
    return (Point){px, py};
}

double tri_get_radius(Triangle t) {
    Point center = tri_get_center(t);
    double x = t.a.x - center.x;
    double y = t.a.y - center.y;
    return sqrt(x*x + y*y);
}

bool tri_in_circum(Triangle t, Point p) {
    Point center = tri_get_center(t);
    double x = p.x - center.x;
    double y = p.y - center.y;
    double r = tri_get_radius(t);

    return sqrt(x*x+y*y)<r;
}

bool compare_edges(void *e1, void *e2) {
    Edge *e = (Edge *)e1;
    Edge *f = (Edge *)e2;
    return compare_points(&e->a, &f->a) && compare_points(&e->b, &f->b);
}

void bw2_init() {
    triangles  = VECTOR_NEW();
    points     = VECTOR_NEW();
    initpoints = VECTOR_NEW();
}

void bw2_initial(double w, double h) { // this was made for a square, so it's not super useful rn
    Point a = {0.0, 0.0};
    Point b = {w, 0.0};
    Point c = {w, h};
    Point d = {0.0, h};

    Triangle t1 = {a, b, c};
    Triangle t2 = {a, c, d};

    vector_push(triangles, VAL_TO_POINTER(t1, sizeof(Triangle)));
    vector_push(triangles, VAL_TO_POINTER(t2, sizeof(Triangle)));

    vector_push(initpoints, VAL_TO_POINTER(a, sizeof(Point)));
    vector_push(initpoints, VAL_TO_POINTER(b, sizeof(Point)));
    vector_push(initpoints, VAL_TO_POINTER(c, sizeof(Point)));
    vector_push(initpoints, VAL_TO_POINTER(d, sizeof(Point)));
}

void bw2_run(Point p) {
    Vector *bads      = VECTOR_NEW();
    Vector *edges     = VECTOR_NEW(); // This is a set
    Vector *to_remove = VECTOR_NEW(); // This is a set

    #define SET_ADD(set, pointer, func) if (vector_find(set, pointer, func) == -1) vector_push(set, pointer)

    for (int i = triangles->size-1; i>=0; i--) {
        Triangle *t = vector_index(triangles, i);
        // printf("%lf %lf %lf %lf %lf %lf :: %lf %lf\n", t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y, p.x, p.y);
        if (tri_in_circum(*t, p)) {
            // printf(" -> TRUE\n");
            vector_push(bads, t);
            vector_delete(triangles, i);
        }
    }

    for (int i = 0; i < bads->size; i ++) {
        Triangle *t = vector_index(bads, i);

        Edge e1 = {t->a, t->b};
        Edge e2 = {t->b, t->c};
        Edge e3 = {t->c, t->a};

        // print out edges
        /* printf("===== (%lf %lf: %lf %lf) =====\n", e1.a.x, e1.a.y, e1.b.x, e1.b.y);
        for (int j = 0; j < edges->size; j ++) {
            Edge *e = (Edge*)vector_index(edges, j);
            printf("(%f %f %f %f)\n", e->a.x, e->a.y, e->b.x, e->b.y);
        } */

        if (vector_find(edges, &e1, compare_edges) == -1) {
            SET_ADD(edges, VAL_TO_POINTER(e1, sizeof(Edge)), compare_edges);
        } else {
            SET_ADD(to_remove, VAL_TO_POINTER(e1, sizeof(Edge)), compare_edges);
        }

        if (vector_find(edges, &e2, compare_edges) == -1) {
            SET_ADD(edges, VAL_TO_POINTER(e2, sizeof(Edge)), compare_edges);
        } else {
            SET_ADD(to_remove, VAL_TO_POINTER(e2, sizeof(Edge)), compare_edges);
        }

        if (vector_find(edges, &e3, compare_edges) == -1) {
            SET_ADD(edges, VAL_TO_POINTER(e3, sizeof(Edge)), compare_edges);
        } else {
            SET_ADD(to_remove, VAL_TO_POINTER(e3, sizeof(Edge)), compare_edges);
        }
    }

    for (int i = 0; i < to_remove->size; i++) { // The problem causing the segfault is that sizeof(to_remove) == sizeof(edges), so it's deleting shit all the way down to -1. this is an issue with items being pushed to to_remove.
        Edge *e = (Edge*)vector_index(to_remove, i);
        /* printf("===== VECTORS =====\n(%f %f %f %f)\n", e->a.x, e->a.y, e->b.x, e->b.y);
        printf("%d\n", vector_find(edges, e, compare_edges));
        for (int j = 0; j < edges->size; j++) {
            Edge *e2 = (Edge*)vector_index(edges, j);
            printf("%d (%f %f %f %f)\n", i, e2->a.x, e2->a.y, e2->b.x, e2->b.y);
        }
        printf("\n"); */
        vector_delete(edges, vector_find(edges, e, compare_edges));
    }

    for (int i = 0; i < edges->size; i++) {
        Edge *e = (Edge*)vector_index(edges, i);
        Triangle t = {e->a, e->b, p};
        vector_push(triangles, VAL_TO_POINTER(t, sizeof(Triangle)));
    }
}

Vector *bw2_do(double w, double h, Vector *p) {
    bw2_initial(w, h);

    /* for (int i = 0; i < triangles->size; i ++) {
        Triangle t = *(Triangle*)vector_index(triangles, i);
        printf("%lf %lf : %lf %lf : %lf %lf\n", t.a.x, t.a.y, t.b.x, t.b.y, t.c.x, t.c.y);
    } */

    for (int i = 0; i < p->size; i++) {
        Point q = *(Point*)vector_index(p, i);
        bw2_run(q);
        printf("[%lf%] : %d / %d\n", (double)i / p->size * 100, i, p->size);
    }

    return triangles;
}
