#include <math.h>

#include "triangle.h"
#include "../shp/types.h"

#include "super_triangle.h"
#include "bowyer_watson.h"

Triangle super_triangle(int n, Point hull[n]) {
    double   smallest = INFINITY;

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
}
