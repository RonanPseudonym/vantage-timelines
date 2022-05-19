#include <math.h>
#include <stdbool.h>

#include "triangle.h"
#include "../shp/types.h"

#include "super_triangle.h"
#include "bowyer_watson.h"

typedef enum {
    SIDE_A_TANGENT,
    SIDE_B_TANGENT,
    SIDES_FLUSH
} status_flag;

typedef enum {
    ABOVE,
    BELOW,
    CRITICAL
} dir_flag;

status_flag validation_flag;

//double h(double x) {};

dir_flag intersects_above_or_below(succ_or_pred_index, index) {
    if (h(succ_or_pred_index) > h(index)) {
        return ABOVE;
    } else {
        return BELOW;
    }
}

double angle_of_line(Point a, Point b) {
    double y = b.y - a.y;
    double x = b.x - a.x;

    double angle = arctangent(y, x) * 180 / PI;

    if (angle < 0) {
        return angle + 360;
    } else {
        return angle;
    }
}

double opposite_angle(double angle) {
    if (angle > 180) {
        return (angle - 180);
    } else {
        return (angle + 180);
    }
}

bool is_angle_btw_non_reflex(double angle, double angle1, double angle2) {
    if (abs(angle1 - angle2) > 180) {
        if (angle1 > angle2) {
            return (angle1<angle && angle<=360) || 
                (0<=angle && angle<angle2);
        } else {
            return (angle2<angle && angle<=360) ||
                (0<=angle && angle<angle1);
        }
    } else {
        if (((angle1-angle2) % 180) > 0) {
            return (angle2<angle) && (angle<angle1)
        } else {
            return (angle1<angle) && (angle<angle2)
        }
    }
}

bool is_opposite_angle_btw_non_reflex(double angle, double angle1, double angle2) {
    double o_angle = opposite_angle(angle);

    return (is_angle_btw_non_reflex(o_angle, angle1, angle2));
}

/* int sqrt_mult[any x, int y] (
    <- int::(math:sqrt[x] * y) // <- is return, x::(y) is cast

    io:nputs!["Error - failed to return"] // putsn! is a macro on top of puts, which appends a new line at the end of puts. `!` specifies it's a macro
)

fn fizzbuzz[] (
    loop[&(int i), 1, 100] ( // Passing a pointer bcz loop is incrementing 
        io:puts["{i} : "] // String formatting with {}

        ?[!i%3] io:puts["Fizz"] // ? is if, ?? is elif and ??? is else
        ?[!i%5] io:puts["Buzz"]

        io:puts["\n"]
     )
) */

bool is_angle_btw_pred_and_succ(double *angle, double angle_pred, double angle_succ) {
    if (is_angle_btw_non_reflex(angle, angle_pred, angle_succ)) {
        return true;
    } else if (is_opposite_angle_btw_non_reflex(*angle, angle_pred, angle_succ)) {
        *angle = opposite_angle(angle);
        return true;
    }

    return false;
}


dir_flag intersects(int n, Point hull[n], double angle, int index) {
    double angle_pred = angle_of_line(hull[index - 1], polygon[index]);
    double angle_succ = angle_of_line(hull[index + 1], polygon[index]);
    double angle_c    = angle_of_line(hull[c     - 1], polygon[c    ]);

    if (is_angle_btw_pred_and_succ(&angle_c, angle_pred, angle_succ)) {
        if (is_angle_btw_non_reflex(angle, angle_pred, angle_c) ||
                (angle == angle_pred)) {
            return intersects_above_of_below(index - 1, index);
        } else if (is_angle_btw_non_reflex(angle, angle_succ, angle_c) ||
                (angle == angle_succ)) {
            return intersects_above_or_below(index + 1, index);
        }
    } else {
        if (is_angle_btw_non_reflex(angle, angle_pred, angle_succ) ||
                ((angle == angle_pred) && (angle != angle_c)) ||
                ((angle == angle_succ) && (angle != angle_c))) {
            return BELOW;
        }
    }

    return CRITICAL;
}

bool intersects_below(int n, Point hull[n], Point gamma_point, int index) {
    double angle = angle_of_line(hull[index], gamma_point);

    return intersects(angle, index) == BELOW;
}

bool intersects_above(int n, Point hull[n], Point gamma_point, int index) {
    double angle = angle_of_line(gamma_point, hull[index];

    return intersects(angle, index) == ABOVE;
}

Point intersection(Point a1, Point a2, Point b1, Point b2) {
    double x1 = a1.x;
    double y1 = a1.y;
    double x2 = a2.x;
    double y2 = a2.y;
    double x3 = b1.x;
    double y3 = b1.y;
    double x4 = b2.x;
    double y4 = b2.y;

    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0) {
        return (Point){-1, -1};
    }

    double xi = ((x3 - x4) * (x1 * y2 - y1 * x2) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
    double yi = ((y3 - y4) * (x1 * y2 - y1 * x2) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;

    return (Point){xi, yi};
}

bool point_on_line(Point p, Point a, Point b) {
    double x1 = a.x;
    double y1 = a.y;
    double x2 = b.x;
    double y2 = b.y;
    double x3 = p.x;
    double y3 = p.y;

    double d = (x1 - x2) * (y3 - y1) - (y1 - y2) * (x3 - x1);
    if (d == 0) {
        return true;
    }

    return false;
}

Point middle_point(Point a, Point b) {
    return (Point){(a.x + b.x) / 2, (a.y + b.y) / 2};
}

bool no_intersection(Point a1, Point a2, Point b1, Point b2) {
    return (a1.x == b1.x && a1.y == b1.y) || (a1.x == b2.x && a1.y == b2.y) || (a2.x == b1.x && a2.y == b1.y) || (a2.x == b2.x && a2.y == b2.y);
}

void advance_b_to_right_chain(int *b) {
    while (h(*b + 1) >= h(*b)) {
        *b ++;
    }
}

bool middle_point_of_side_b(Point *A, Point *B, Point *C, Point *middle_point) {
    if (!intersection(*A, *B, *B, *C) || !intersection(*A, *B, *C, *A)) {
        return false;
    }

    *A = intersection(*A, *B, *B, *C);
    *B = intersection(*C, *A, *A, *B);

    *middle_point = middle_point(*A, *B);

    return true;
}

void move_a_if_low_and_b_if_high(Point *A, int *a, int *b) {
    while (h(*b) > h(*a)) {
        if (gamma(*a, gamma_of(A)) && intersects_below(gamma_of(A), b)) {
            *b ++;
        } else {
            *a ++;
        }
    }
}

void search_for_b_tangency(Point *B, int *a, int *b) {
    while (
            gamma(b, gamma_of(*b)) && 
            intersects_below(gamma_of(*B), *B) && 
            (h(*b) >= h(*a - 1))) {
        *b ++;
    }
}

void update_sides_ca(int n, Point hull[n], Triangle *min_area_triangle, int *a, int *c) {
    min_area_triangle->a = hull[*c]; // May not be entirely correct? Should be a/c - 1 maybe?
    min_area_triangle->c = hull[*a];
}

bool is_not_b_tangency(Point *B, int *a, int *b) {
    return (gamma(*b, gamma_of(*B)) && intersects_above(gamma_of(*B), b) || (h(*b) < h(*a - 1)));
}

void update_sides_ba(int n, Point hull[n], Point *A, Point *B, int *a, int *b) {
    *B = hull[*b];

    if (middle_point_of_side_b(middle_point(*A, *B))
            && (h(middle_point(*A, *B)) < h(*a - 1))) {
        *A = find_vertex_c_on_side_b();

        validation_flag = SIDE_A_TANGENT;
    } else {
        validation_flag = SIDES_FLUSH;
    }
}

void update_side_b(int n, Point hull[n], Point *B, int *b) {
    gamma(b, B);
    *B = hull[*b];

    validation_flag = SIDE_B_TANGENT;
}

bool pcomp(Point a, Point b) {
    return (a.x == b.x && a.y == b.y);
}

bool is_valid_minimal_triangle(int n, Point hull[n], Point *A, Point *B, Point *C, int *a, int *b, int *c) {
    Point midpoint_a = middle_point(*B, *C);
    Point midpoint_b = middle_point(*A, *C);
    Point midpoint_c = middle_point(*A, *B);

    bool valid_a;
    bool valid_b;
    bool valid_c;

    if (validation_flag == SIDE_A_TANGENT) {
        valid_a = pcomp(midpoint_a, hull[*a - 1]);
    } else {
        valid_a = point_on_line(midpoint_a, *C, *A);
    }

    if (validation_flag == SIDE_B_TANGENT) {
        valid_b = pcomp(midpoint_b, hull[*b - 1]);
    } else {
        valid_b = point_on_line(midpoint_b, *A, *B);
    }

    valid_c = point_on_line(midpoint_c, *B, *C);

    return (valid_a && valid_b && valid_c);
}

bool is_local_minimum_triangle(int n, Point hull[n], Point *A, Point *B, Point *C, int *a, int *b, int *c) {
    if (no_intersection(*C, *A, *A, *B) || no_intersection(*C, *A, *B, *C)) { // TODO: This could be wrong. Check. Also, the algorithm might think lines sharing a vertex count as intersections? Check that bad boy too.
        return false;
    } else {
        *A = intersection(*A, *B, *B, *C); // TODO: Same here
        *B = intersection(*C, *A, *B, *C);
        *C = intersection(*C, *A, *A, *B);

        return is_valid_minimal_triangle(n, hull, A, B, C, a, b, c);
    }
}


Triangle super_triangle(int n, Point hull[n]) {
    Triangle min_area_triangle;
    double min_area = INFINITY;

    int a = 2;
    int b = 3;

    for (int c = 1; c < n; c ++) {
        advance_b_to_right_chain(&b);
        move_a_if_low_and_b_if_high(&min_area_triangle.a, &a, &b);
        search_for_b_tangency(&min_area_triangle.b, &a, &b);

        update_sides_ca(n, hull, &min_area_triangle, &a, &c);

        if (is_not_b_tangency(&min_area_triangle.b, &a, &b)) {
            update_sides_ba(n, hull, &min_area_triangle.a, &min_area_triangle.b, &a, &b);
        } else {
            update_side_b(n, hull, &min_area_triangle.b, &b);
        }

        if (is_local_minimum_triangle(n, hull, &min_area_triangle.a, &min_area_triangle.b, &min_area_triangle.c, &a, &b, &c)) {
            update_minimum_area_enclosing_triangle(min_area_triangle, min_area);
        }
    }
}

/*
// Triangle super_triangle(int n, Point hull[n]) {
    Point bmin, bmax;

    bmin.x = INFINITY;
    bmin.y = INFINITY;
    bmax.x = -INFINITY;
    bmax.y = -INFINITY;

    for (int i = 0; i < n; i++) {
        if (hull[i].x < bmin.x) {
            bmin.x = hull[i].x;
        }
        if (hull[i].y < bmin.y) {
            bmin.y = hull[i].y;
        }
        if (hull[i].x > bmax.x) {
            bmax.x = hull[i].x;
        }
        if (hull[i].y > bmax.y) {
            bmax.y = hull[i].y;
        }
    }

    double long_x = bmax.x - bmin.x;
    double long_y = bmax.y - bmin.y;

    double long_xx = long_x * 0.01; // TODO: May need to be adjusted for smaller points?
    double long_yy = long_y * 0.01;

    bmin.x -= long_xx;
    bmax.x += long_xx;

    long_x += 2 * long_xx;

    bmin.y -= long_yy;
    bmax.y += long_yy;

    long_y += 2 * long_yy;

    Triangle out;
    out.a = (Point){bmin.x - long_y * sqrt(3) / 3.0, bmin.y}; // it's sqrt3 not sqrt(3) in the reference i used, this might be wrong??
    out.b = (Point){bmin.x + long_y * sqrt(3) / 3.0, bmin.y};
    out.c = (Point){(bmin.x + bmax.x) * 0.5, bmax.y + long_x * sqrt(3) * 0.5};

    return out; */

    /* double   smallest = INFINITY;

    Triangle striangle;
    double   smallest_a = INFINITY;

    for (int i = 0; i < n; i ++) {
        Point p = hull[i];

        double biggest_distance = -1;
        int    furthest_index   = -1;

        for (int j = 0; j < n; j ++) {
            if (i == j) continue;

            Point p2 = hull[j];
            double dist = vector_distance(p, p2);

            if (dist == INFINITY || dist >= biggest_distance) {
                biggest_distance = dist;
                furthest_index   = j;
            }
        }

        Point q = hull[furthest_index];

        Point n1 = hull[furthest_index - 1];
        Point n2 = hull[furthest_index + 1];

        Triangle triangle = (Triangle){q, n1, n2};
        double area = triangle_area(triangle);

        if (smallest_a == INFINITY || area <= smallest_a) {
            smallest_a = area;
            striangle  = triangle;
        }
    }

    return striangle;
} */
