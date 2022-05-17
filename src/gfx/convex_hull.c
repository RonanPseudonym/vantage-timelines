#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "../shp/types.h"
#include "../utils/vector.h"

#include "triangle.h"

// float area(Point a, Point b, Point c) {
//     return abs((a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y))/2.0);
// }

bool is_inside(Point a, Point b, Point c, Point p) {
    double c1 = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    double c2 = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
    double c3 = (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x);

    return (c1<0 && c2<0 && c3<0) || (c1>0 && c2>0 && c3>0);
}

void print_hull(Vector *points) {
    for (size_t i = 0; i < points->size; i ++) {
        Point *p = (Point*)vector_index(points, i);
        printf("(%lf %lf)\n", p->x, p->y);
    }
}

double get_dir_from_line(Point a, Point b, Point p) {
    Point v1 = {(b.x)-(a.x), (b.y)-(a.y)};
    Point v2 = {(b.x)-(p.x), (b.y)-(p.y)};

    double xp = ((v1.x * v2.y) - (v1.y * v2.x));

    // printf("(%lf %lf) (%lf %lf)\n", v1.x, v1.y, v2.x, v2.y);

    return xp;
}

double min_distance(Point a, Point b, Point p) {
    Point v1 = {(b.x)-(a.x), (b.y)-(a.y)};
    Point v2 = {(b.x)-(p.x), (b.y)-(p.y)};

    double t = (v1.x*v2.y - v1.y*v2.x)/(v1.x*v1.x + v1.y*v1.y);
    Point q = {a.x + v1.x*t, a.y + v1.y*t};

    return sqrt((q.x-p.x)*(q.x-p.x) + (q.y-p.y)*(q.y-p.y));
}

void find_hull(Vector *convex_hull, Vector *sk, Point p, size_t p_index, Point q) {
    /* print_hull(convex_hull);
    printf("/\n");
    print_hull(sk);
    printf("/\n");
    printf("(%lf %lf) (%lf %lf)\n", p.x, p.y, q.x, q.y);
    printf("===\n");

    printf("p: (%lf %lf)\n", p.x, p.y);
    printf("q: (%lf %lf)\n", q.x, q.y);
    printf("p_index: %lu\n", p_index);
    printf("sk size: %lu\n", sk->size);
    printf("convex_hull size: %lu\n", convex_hull->size); */

    if (!sk->size) {
        return;
    }

    Point  c;
    size_t f_i;
    double last_dist = -1;

    for (size_t i = 0; i < sk->size; i ++) {
        Point *x = (Point*)vector_index(sk, i);

        double dist = min_distance(p, q, *x); // Fix this

        if (last_dist == -1 || dist >= last_dist) {
            c = *x;
            f_i = i;

            last_dist = dist;
        }

    }

    // size_t ppos = vector_find(convex_hull 
    vector_insert(convex_hull, p_index + 1, memcpy(malloc(sizeof(Point)), &c, sizeof(Point))); // Wrong index?
    vector_delete(sk, f_i);

    /* print_hull(convex_hull);
    printf(";;\n");
    print_hull(sk);
    printf("============\n"); */

    /* for (int i = 0; i < convex_hull->size; i ++) {
        printf("::(%lf %lf)\n", ((Point*)vector_index(convex_hull, i))->x, ((Point*)vector_index(convex_hull, i))->y);
    } */

    Vector *s0 = VECTOR_NEW();
    Vector *s1 = VECTOR_NEW();
    Vector *s2 = VECTOR_NEW();

    for (int i = 0; i < sk->size; i ++) {
        Point *x = (Point*)vector_index(sk, i);

        //printf("\n(%lf %lf)\n(%lf %lf)\n(%lf %lf)\n(%lf %lf)\n", p.x, p.y, q.x, q.y, c.x, c.y, x->x, x->y);

        if (is_inside(p, q, c, *x)) {
            //printf("INSIDE\n\n");
            vector_push(s0, x);
        } else {
            double angle_pc = get_dir_from_line(p, c, *x);
            double angle_cq = get_dir_from_line(c, q, *x);

            printf("%lf %lf\n", angle_pc, angle_cq);

            if (angle_pc > 0) {
                vector_push(s1, x);
            } else if (angle_cq > 0) {
                vector_push(s2, x);
            }
        }
    }

    find_hull(convex_hull, s1, p, p_index, c);
    find_hull(convex_hull, s2, c, f_i, q);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

Vector *jarvis_algorithm(int n, Point points[n]) {
    Vector *hull = VECTOR_NEW();

    int l = 0; // Find the leftmost point
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x) {
            l = i;
        }
    }

    int p = l, q;

    do {
        vector_push(hull, memcpy(malloc(sizeof(Point)), &points[p], sizeof(Point)));

        q = (p+1)%n;

        for (int i = 0; i < n; i ++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        p = q;
    } while (p != l);

    return hull;
}

Vector *quick_hull(int num_points, Point points[num_points]) {
    Vector *remaining_hull = VECTOR_NEW();
    Vector *convex_hull    = VECTOR_NEW();

    for (int i = 0; i < num_points; i ++) vector_push(remaining_hull, &points[i]);

    Point  a;
    size_t a_i;
    bool set_a = false;

    Point  b;
    size_t b_i;
    bool set_b = false;

    for (size_t i = 0; i < num_points; i ++) {
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

    if (b_i > a_i) {
        vector_delete(remaining_hull, b_i);
        vector_delete(remaining_hull, a_i);
    } else {
        vector_delete(remaining_hull, a_i);
        vector_delete(remaining_hull, b_i);
    }

    vector_push(convex_hull, &a);
    vector_push(convex_hull, &b);

    Vector *s1 = VECTOR_NEW();
    Vector *s2 = VECTOR_NEW();

    for (size_t i = 0; i < remaining_hull->size; i ++) {
        Point *p = vector_index(remaining_hull, i);

        double cross_product = get_dir_from_line(a, b, *p);

        if (cross_product > 0 || cross_product == 0) vector_push(s2, p);
        if (cross_product < 0) vector_push(s1, p);
    }

    find_hull(convex_hull, s1, a, 0, b);
    find_hull(convex_hull, s2, b, 1, a);

    // print_hull(convex_hull);
    return convex_hull;
}

/* Triangle super_triangle(Vector *hull) {
    double min_x = INFINITY;
    double min_y = INFINITY;
    double max_x = -INFINITY;
    double max_y = -INFINITY;

    for (int i = 0; i < hull->size; i ++) {
        Point *p = (Point*)vector_index(hull, i);

        if (p->x < min_x) min_x = p->x;
        if (p->x > max_x) max_x = p->x;
        if (p->y < min_y) min_y = p->y;
        if (p->y > max_y) max_y = p->y;
    }

    double dx = max_x - min_x;
    double dy = max_y - min_y;

    double dmax = (dx > dy) ? dx : dy;

    return (Triangle){
        .a = {min_x - dmax, min_y - dmax},
        .b = {min_x - dmax, max_y + dmax},
        .c = {max_x + dmax, min_y - dmax}
    };
} */
