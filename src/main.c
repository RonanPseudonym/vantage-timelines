#include "shp/types.h"
#include "shp/read.h"
#include "gfx/main.h"

#include "gfx/convex_hull.h"
#include "shp/types.h"
// #include "utils/vector.h"
// #include "gfx/triangle.h"
#include "gfx/bowyer_watson.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    //printf("hi :3");

    // gfx_main_loop();
    Point i_points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
{0, 0}, {1, 2}, {3, 1}, {3, 3}};

    // Vector *points = quick_hull(8, i_points);
    // Triangle super = super_triangle(points);

    Vector *points = quick_hull(8, i_points);
    printf("%d\n", points->size);

    // print out points
    for (int i = 0; i < points->size; i++) {
        printf("%d: %lf, %lf\n", i, ((Point*)vector_index(points, i))->x, ((Point*)vector_index(points, i))->y);
    }
}
