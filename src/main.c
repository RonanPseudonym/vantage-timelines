#include "shp/types.h"
#include "shp/read.h"
#include "gfx/main.h"

#include "gfx/bowyer_watson.h"
#include "shp/types.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("hi :3");

    // gfx_main_loop();
    Point points[5];

    points[0] = (Point){-2, 0};
    points[1] = (Point){0, 2};
    points[2] = (Point){2, 0};
    points[3] = (Point){0, -2};
    points[4] = (Point){1, 1};

    quick_hull(5, points);
}
