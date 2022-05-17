#ifndef CONVEX_HULL

#ifndef STD_VECTOR
#include "../utils/vector.h"
#endif

#ifndef TRIANGLE_TYPES
#include "triangle.h"
#endif

Vector  *quick_hull(int num_points, Point points[num_points]);
Triangle super_triangle(Vector *hull);

#endif
