#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../shp/types.h"
#include "../utils/vector.h"

#include "triangle.h"

void print_hull(Vector *points) {
    for (size_t i = 0; i < points->size; i ++) {
        Point *p = (Point*)vector_index(points, i);
        printf("(%lf %lf)\n", p->x, p->y);
    }
}

void find_hull(Vector *sk, Point p, Point q) {
    
}

Vector *quick_hull(int num_points, Point points[num_points]) {
    Vector *convex_hull = VECTOR_NEW();

    for (int i = 0; i < num_points; i ++) vector_push(convex_hull, &points[i]);

    Point  a;
    size_t a_i;
    bool set_a = false;

    Point  b;
    size_t b_i;
    bool set_b = false;

    for (int i = 0; i < num_points; i ++) {
        double x = points[i].x;

        if (!set_a || x < a.x) {
            a = points[i];
            a_i = (size_t)i;
            set_a = true;
        } 

        if (!set_b || x > b.x) {
            b = points[i];
            b_i = (size_t)i;
            set_b = true;
        }

    }

    vector_delete(convex_hull, a_i);
    vector_delete(convex_hull, b_i);

    Vector *s1 = VECTOR_NEW();
    Vector *s2 = VECTOR_NEW();

    for (size_t i = 0; i < convex_hull->size; i ++) {
        Point *p = vector_index(convex_hull, i);

        Point v1 = {(b.x)-(a.x ), (b.y )-(a.y )};
        Point v2 = {(b.x)-(p->x), (b.y )-(p->y)};

        double cross_product = v1.x*v2.y - v1.y*v2.x;

        printf("[%lf %lf]\n", p->x, p->y);

        if (cross_product > 0 || cross_product == 0) vector_push(s2, &p);
        if (cross_product < 0) vector_push(s1, &p);
    }

    printf("\n");
    print_hull(s1);
    printf("===\n");
    print_hull(s2);

    find_hull(s1, a, b);
    find_hull(s1, b, a);
}
