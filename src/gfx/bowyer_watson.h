#ifndef BOWYER_WATSON
#define BOWYER_WATSON

#ifndef STD_VECTOR
#include "../utils/vector.h"
#endif

#ifndef SHP_TYPES
#include "../shapes/types.h"
#endif

Vector *bowyer_watson(int num_points, Point points[num_points]);
#endif
