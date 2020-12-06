#include <stdio.h>
#include <math.h>
#include "util.h"
#include "vec.h"

vec2 vec2_create(double x_, double y_) {
    vec2 v = {.x = x_, .y = y_};
    return v;
}

vec2 vec2_create_zero() {
    return vec2_create(0.0, 0.0);
}

vec2 vec2_create_random(vec2 min_r, vec2 max_r) {
    double x = rand_to_range(min_r.x, max_r.x);
    double y = rand_to_range(min_r.y, max_r.y);

    vec2 r = vec2_create(x, y);

    return r;
}

vec2 vec2_add(vec2 lhs, vec2 rhs) {
    return vec2_create(
        lhs.x + rhs.x,
        lhs.y + rhs.y
    );
}

vec2 vec2_sub(vec2 lhs, vec2 rhs) {
    return vec2_create(
        lhs.x - rhs.x,
        lhs.y - rhs.y
    );
}

vec2 vec2_mul(double scalar, vec2 lhs) {
    return vec2_create(
        scalar * lhs.x,
        scalar * lhs.y
    );
}

double vec2_dot(vec2 lhs, vec2 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double vec2_norm_sqr(vec2 v) {
    return vec2_dot(v, v);
}

double vec2_norm(vec2 v) {
    return sqrt(vec2_norm_sqr(v));
}

vec2 vec2_normalize(vec2 v) {
    double norm = vec2_norm(v);

    return vec2_mul(1.0 / norm, v);
}

bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps) {
    return vec2_norm(vec2_sub(lhs, rhs)) < eps;
}

void vec2_print(vec2 v) {
    printf("x = %g, y = %g\n", v.x, v.y);
}