#ifndef TRIANGLE_TYPES
#define TRIANGLE_TYPES

#ifndef STD_VECTOR
#include "../utils/vector.h"
#endif

#ifndef SHP_TYPES
#include "../shp/types.h"
#endif

typedef struct _Triangle Triangle;
typedef struct _Edge     Edge;

struct _Triangle {
    Point a;
    Point b;
    Point c;
};

struct _Edge {
    Point a;
    Point b;
};

#endif
