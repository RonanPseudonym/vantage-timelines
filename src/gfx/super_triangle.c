#include <math.h>

#include "triangle.h"
#include "../shp/types.h"

#include "super_triangle.h"
#include "bowyer_watson.h"

Triangle super_triangle(int n, Point hull[n]) {
    Triangle out;
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

    return striangle; */
}
