#include "shp/types.h"
#include "shp/read.h"
#include "gfx/main.h"

#include "gfx/convex_hull.h"
#include "shp/types.h"
// #include "utils/vector.h"
// #include "gfx/triangle.h"
// #include "gfx/bowyer_watson.h"
// #include "gfx/super_triangle.h"
#include "gfx/bowyer_watson2.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    // gfx_main_loop();
    Vector *points_v = VECTOR_NEW();

    Point p[24];
    p[0] = (Point){0.0, 0.0};
    p[1] = (Point){1.0, 0.0};
    p[2] = (Point){1.0, 1.0};
    p[3] = (Point){0.0, 1.0};

    srand(time(NULL));

    int i = 4;
    while (i < 24) {
        p[i] = (Point){(double)rand() / INT_MAX, (double)rand() / INT_MAX};

        i ++;
    }

    for (int i = 0; i < sizeof(p)/sizeof(Point); i++) {
        vector_push(points_v, &p[i]);
    }


    // Vector *points = quick_hull(8, i_points);
    // Triangle super = super_triangle(points);

    // Vector *points = jarvis_algorithm(8, i_points);

    // Point p2[points->size];
    // for (int i = 0; i < points->size; i ++) {
    //     p2[i] = *(Point *)vector_index(points, i);
    // }

    // Triangle super = super_triangle(points->size, p2);

    // Vector *points = bowyer_watson(8, i_points);

    bw2_init();

    Vector *points = bw2_do(1.0, 1.0, points_v);

    gfx_main_loop(points);

    // printf("TRIANGLE :: (%lf %lf) (%lf %lf) (%lf %lf)\n", super.a.x, super.a.y, super.b.x, super.b.y, super.c.x, super.c.y);
}
