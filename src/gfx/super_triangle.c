#include <math.h>
#include <stdbool.h>

#include "triangle.h"
#include "../shp/types.h"

#include "super_triangle.h"
#include "bowyer_watson.h"

double h(double n) {
}

void advance_b_to_right_chain(int *b) {
    while (h(*b + 1) >= h(*b)) {
        *b ++;
    }
}

void move_a_if_low_and_b_if_high(Point *A, int *a, int *b) {
    while (h(*b) > h(*a)) {
        if (gamma(*a, gamma_of(A)) && intersects_below(gamma_of(A), b)) {
            *b ++;
        } else {
            *a ++;
        }
    }
}

void search_for_b_tangency(Point *B, int *a, int *b) {
    while (
            gamma(b, gamma_of(*b)) && 
            intersects_below(gamma_of(*B), *B) && 
            (h(*b) >= h(*a - 1))) {
        *b ++;
    }
}

void update_sides_ca(Triangle *min_area_triangle, int *a, int *c) { // Gotta fix this w/ point != int
    min_area_triangle->a = *a; // May not be entirely correct? Should be a/c - 1 maybe?
    min_area_triangle->c = *c;
}

bool is_not_b_tangency(Point *B, int *a, int *b) {
    return (gamma(*b, gamma_of(*b, gamma_of(*B))) || (h(*b) < h(*b - 1)));
}

void update_sides_ba(Point hull[], Point *B, int *a, int *b) {
    *B = hull[*b];

    if (middle_point_of_side_b())
}

Triangle super_triangle(int n, Point hull[n]) {
    Triangle min_area_triangle;
    double min_area = INFINITY;

    int a = 2;
    int b = 3;

    for (int c = 1; c < n; c ++) {
        advance_b_to_right_chain(&b);
        move_a_if_low_and_b_if_high(&min_area_triangle->a, &a, &b);
        search_for_b_tangency(&min_area_triangle->b, &a, &b);

        update_sides_ca(&min_area_triangle, &a, &c);

        if (is_not_b_tangency(&min_area_triangle->b, &a, &b)) {
            update_sides_ba();
        } else {
            update_side_b();
        }

        if (is_local_minimum_triangle()) {
            update_minimum_area_enclosing_triangle(min_area_triangle, min_area);
        }
    }
}

// Triangle super_triangle(int n, Point hull[n]) {
    /* Point bmin, bmax;

    bmin.x = INFINITY;
    bmin.y = INFINITY;
    bmax.x = -INFINITY;
    bmax.y = -INFINITY;

    for (int i = 0; i < n; i++) {
        if (hull[i].x < bmin.x) {
            bmin.x = hull[i].x;
        }
        if (hull[i].y < bmin.y) {
            bmin.y = hull[i].y;
        }
        if (hull[i].x > bmax.x) {
            bmax.x = hull[i].x;
        }
        if (hull[i].y > bmax.y) {
            bmax.y = hull[i].y;
        }
    }

    double long_x = bmax.x - bmin.x;
    double long_y = bmax.y - bmin.y;

    double long_xx = long_x * 0.01; // TODO: May need to be adjusted for smaller points?
    double long_yy = long_y * 0.01;

    bmin.x -= long_xx;
    bmax.x += long_xx;

    long_x += 2 * long_xx;

    bmin.y -= long_yy;
    bmax.y += long_yy;

    long_y += 2 * long_yy;

    Triangle out;
    out.a = (Point){bmin.x - long_y * sqrt(3) / 3.0, bmin.y}; // it's sqrt3 not sqrt(3) in the reference i used, this might be wrong??
    out.b = (Point){bmin.x + long_y * sqrt(3) / 3.0, bmin.y};
    out.c = (Point){(bmin.x + bmax.x) * 0.5, bmax.y + long_x * sqrt(3) * 0.5};

    return out; */

    /* double   smallest = INFINITY;

    Triangle striangle;
    double   smallest_a = INFINITY;

    for (int i = 0; i < n; i ++) {
        Point p = hull[i];

        double biggest_distance = -1;
        int    furthest_index   = -1;

        for (int j = 0; j < n; j ++) {
            if (i == j) continue;

            Point p2 = hull[j];
            double dist = vector_distance(p, p2);

            if (dist == INFINITY || dist >= biggest_distance) {
                biggest_distance = dist;
                furthest_index   = j;
            }
        }

        Point q = hull[furthest_index];

        Point n1 = hull[furthest_index - 1];
        Point n2 = hull[furthest_index + 1];

        Triangle triangle = (Triangle){q, n1, n2};
        double area = triangle_area(triangle);

        if (smallest_a == INFINITY || area <= smallest_a) {
            smallest_a = area;
            striangle  = triangle;
        }
    }

    return striangle;
} */
