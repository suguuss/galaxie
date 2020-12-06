#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vec.h"

typedef struct _particle {
    vec2 r;
    double m;
} particle;

particle particle_create(vec2 r_, double m_);

particle particle_create_random(vec2 min_r, vec2 max_r, double min_m, double max_m);

particle *particle_create_random_list(vec2 min_r, vec2 max_r, double min_m, double max_m, int number);

vec2 particle_compute_grav_force(particle lhs, particle rhs);

vec2 *particle_compute_grav_resultant_forces(particle *parts, int number);

vec2 *particle_compute_grav_friction_resultant_forces(particle *parts, vec2 *vel, double k, int number);

void particle_print(particle p);

void particle_print_list(particle *p, int number);


#endif