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

int main(int argc, char *argv[]) {

    // gfx_main_loop();
    Point i_points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
{0, 0}, {1, 2}, {3, 1}, {3, 3}};
    Vector *points_v = VECTOR_NEW();


    for (int i = 0; i < 8; i++) {
        vector_push(points_v, &i_points[i]);
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

    Vector *points = bw2_do(4.0, 4.0, points_v);

    // print out points
    for (int i = 0; i < points->size; i++) {
        printf("%d: %lf, %lf\n", i, ((Point*)vector_index(points, i))->x, ((Point*)vector_index(points, i))->y);
    }

    // printf("TRIANGLE :: (%lf %lf) (%lf %lf) (%lf %lf)\n", super.a.x, super.a.y, super.b.x, super.b.y, super.c.x, super.c.y);
}
