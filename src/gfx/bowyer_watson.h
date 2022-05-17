#ifndef BOWYER_WATSON
#define BOWYER_WATSON

#ifndef STD_VECTOR
#include "../utils/vector.h"
#endif

#ifndef SHP_TYPES
#include "../shapes/types.h"
#endif

#include "triangle.h"

Vector *bowyer_watson  (int num_points, Point points[num_points], Triangle striangle);
double  vector_distance(Point a, Point b);
double  triangle_area  (Triangle t);
#endif
