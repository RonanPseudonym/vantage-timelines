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
#include <string.h>

#define INTENT_UKRAINE

int main(int argc, char *argv[]) {
    // gfx_main_loop();
    Vector *shapes = shp_read("data/2022");
    Vector *points_v = VECTOR_NEW();
    double w, h;

    # ifdef INTENT_RANDOM

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

    w = 0.0;
    h = 0.0;

    bw2_init();
    Vector *points = bw2_do(w, h, points_v);
    gfx_main_loop(points, shapes, w, h, 0, 0);

    # endif

    # ifdef INTENT_UKRAINE
    double least_x = 10000;
    double least_y = 10000;
    double most_x  = -10000;
    double most_y  = -10000;

    char name[32];

    printf("Country name: ");
    scanf("%s", &name);

    Polygon *ukraine;
    for (int i = 0; i < shapes->size; i ++) {
        ukraine = vector_index(shapes, i);
        if (ukraine->name[0] == name[0] && ukraine->name[1] == name[1] && ukraine->name[2] == name[2]) break; // yoinked ukraine!
    }

    Point p2[ukraine->num_points];
    memcpy(&p2, ukraine->points, sizeof(Point) * ukraine->num_points);

    for (int i = 0; i < ukraine->num_points; i ++) {
        Point *p = &p2[i];

        if (p->x < least_x) least_x = p->x;
        if (p->x > most_x ) most_x  = p->x;
        if (p->y < least_y) least_y = p->y;
        if (p->y > most_y ) most_y  = p->y;
    }

    w = most_x - least_x;
    h = most_y - least_y;

    for (int i = 0; i < ukraine->num_points; i ++) {
        p2[i].x -= least_x;
        p2[i].y -= least_y;

        vector_push(points_v, &p2[i]);
    }

    bw2_init();

    Vector *points = bw2_do(w, h, points_v);

    gfx_main_loop(points, shapes, w, h, 1, 1);

    # endif


    // Vector *points = quick_hull(8, i_points);
    // Triangle super = super_triangle(points);

    // Vector *points = jarvis_algorithm(8, i_points);

    // Point p2[points->size];
    // for (int i = 0; i < points->size; i ++) {
    //     p2[i] = *(Point *)vector_index(points, i);
    // }

    // Triangle super = super_triangle(points->size, p2);

    // Vector *points = bowyer_watson(8, i_points);

    // bw2_init();

    // Vector *points = bw2_do(w, h, points_v);

    /* for (int i = 0; i < points->size; i ++) {
        Triangle *c = vector_index(points, i);

        for (int j = 0; j < 3; j ++) {
            Point jp;

            switch (j) {
                case 0: jp = c->a; break;
                case 1: jp = c->b; break;
                case 2: jp = c->c; break;
            }

            if (jp.x == 0 || jp.x == w || jp.y == 0 || jp.y == h) {
                printf("HI %d\n", i);
                vector_delete(points, i);
                break;
            }
        }
    } */

    // gfx_main_loop(points, shapes, w, h, 1);

    // printf("TRIANGLE :: (%lf %lf) (%lf %lf) (%lf %lf)\n", super.a.x, super.a.y, super.b.x, super.b.y, super.c.x, super.c.y);
}
