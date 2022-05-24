/*
   CONSTRUCTORS FOR BASIC SHAPEFILE TYPES

   -1    IS A  NON-CONSTANT NUMBER  TO BE  ASSIGNED
   NULL  IS A  VOID* VLA            TO BE  ALLOCATED
*/

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Point NEW_POINT() {
    Point x = {0.0, 0.0};
    return x;
}

bool compare_points(void *a, void *b) {
    Point *p1 = (Point *) a;
    Point *p2 = (Point *) b;

    return (p1->x == p2->x && p1->y == p2->y);
}

/*
MultiPoint NEW_MULTIPOINT(int num_points) {
    return false;
    MultiPoint x = {{0.0, 0.0, 0.0, 0.0}, -1, NULL};

    x.num_points = num_points;
    x.points     = malloc(sizeof(Point) * num_points);

    return x;
}

PolyLine NEW_POLYLINE(int num_parts, int num_points) {
    PolyLine x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)   * num_parts);
    x.points     = malloc(sizeof(Point) * num_points);

    return x;
}
*/
Polygon* NEW_POLYGON(int num_parts, int num_points) {
    Polygon *x = malloc(sizeof(int) * 2 + sizeof(Point) * num_points + sizeof(int) * num_parts + sizeof(double) * 4 + sizeof(char) * 32 /* could be just `32` but this is more readable */);
    x->num_parts  = num_parts;
    x->num_points = num_points;
    x->parts      = malloc(sizeof(int)   * num_parts);
    x->points     = malloc(sizeof(Point) * num_points);

    return x;
}
/*
PointM NEW_POINTM() {
    PointM x = {0.0, 0.0, 0.0};
    return x;
}

MultiPointM NEW_MULTIPOINTM(int num_points) {
    MultiPointM x = {{0.0, 0.0, 0.0, 0.0}, -1, NULL, {0.0, 0.0}, NULL};

    x.num_points = num_points;
    x.points     = malloc(sizeof(PointM) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

PolyLineM NEW_POLYLINEM(int num_parts, int num_points) {
    PolyLineM x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL, {0.0, 0.0}, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)    * num_parts);
    x.points     = malloc(sizeof(PointM) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

PolygonM NEW_POLYGONM(int num_parts, int num_points) {
    PolygonM x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL, {0.0, 0.0}, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)    * num_parts);
    x.points     = malloc(sizeof(PointM) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

PointZ NEW_POINTZ() {
    PointZ x = {0.0, 0.0, 0.0, 0.0};
    return x;
}

MultiPointZ NEW_MULTIPOINTZ(int num_points) {
    MultiPointZ x = {{0.0, 0.0, 0.0, 0.0}, -1, NULL, {0.0, 0.0}, NULL, {0.0, 0.0}, NULL};

    x.num_points = num_points;
    x.points     = malloc(sizeof(PointZ) * num_points);
    x.z_array    = malloc(sizeof(double) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

PolyLineZ NEW_POLYLINEZ(int num_parts, int num_points) {
    PolyLineZ x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL, {0.0, 0.0}, NULL, {0.0, 0.0}, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)    * num_parts);
    x.points     = malloc(sizeof(PointZ) * num_points);
    x.z_array    = malloc(sizeof(double) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

PolygonZ NEW_POLYGONZ(int num_parts, int num_points) {
    PolygonZ x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL, {0.0, 0.0}, NULL, {0.0, 0.0}, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)    * num_parts);
    x.points     = malloc(sizeof(PointZ) * num_points);
    x.z_array    = malloc(sizeof(double) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}

MultiPatch NEW_MULTIPATCH(int num_parts, int num_points) {
    MultiPatch x = {{0.0, 0.0, 0.0, 0.0}, -1, -1, NULL, NULL, NULL, {0.0, 0.0}, NULL, {0.0, 0.0}, NULL};

    x.num_parts  = num_parts;
    x.num_points = num_points;
    x.parts      = malloc(sizeof(int)    * num_parts);
    x.part_types = malloc(sizeof(int)    * num_parts);
    x.points     = malloc(sizeof(PointZ) * num_points);
    x.z_array    = malloc(sizeof(double) * num_points);
    x.m_array    = malloc(sizeof(double) * num_points);

    return x;
}
*/
ShpHeader NEW_SHPHEADER() {
    ShpHeader x = {0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    return x;
}
