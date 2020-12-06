#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "particles.h"
#include "util.h"

static double G = 6.27e-11;

particle particle_create(vec2 r_, double m_) {
    particle p = {.r = r_, .m = m_};
    return p;
}

particle particle_create_random(vec2 min_r, vec2 max_r, double min_m, double max_m) {
    double m = rand_to_range(min_m, max_m);
    vec2 r = vec2_create_random(min_r, max_r);

    return particle_create(r, m);
}

particle *particle_create_random_list(vec2 min_r, vec2 max_r, double min_m, double max_m, int number) {
    particle *p = malloc(number * sizeof(particle));

    srand(time(NULL));

    for (int ip = 0; ip < number; ++ip) {
        p[ip] = particle_create_random(min_r, max_r, min_m, max_m);
    }

    return p;
}

vec2 particle_compute_grav_force(particle lhs, particle rhs) {
    vec2 rij = vec2_sub(lhs.r, rhs.r);
    double distance = vec2_norm(rij);
    assert(distance > 1e-10);
    double factor = G * lhs.m * rhs.m / (distance * distance * distance);
    //printf("factor = %g %g %g %g %g\n", factor, lhs.m, rhs.m, distance, G);
    return vec2_mul(factor, rij);
}

vec2 *particle_compute_grav_resultant_forces(particle *parts, int number) {
    vec2 *forces = malloc(number * sizeof(vec2));
    for (int ip = 0; ip < number; ++ip) {
        forces[ip] = vec2_create_zero();
    }
    for (int ip = 0; ip < number; ++ip) {
        for (int iq = ip + 1; iq < number; ++iq) {
            forces[ip] = vec2_add(forces[ip], particle_compute_grav_force(parts[ip], parts[iq]));
            forces[iq] = vec2_add(forces[iq], particle_compute_grav_force(parts[iq], parts[ip]));
        }
    }
    return forces;
}

vec2 *particle_compute_grav_friction_resultant_forces(particle *parts, vec2 *vel, double k, int number) {
    vec2 *forces = particle_compute_grav_resultant_forces(parts, number);
    for (int ip = 0; ip < number; ++ip) {
        forces[ip] = vec2_sub(forces[ip], vec2_mul(k, vel[ip]));
    }
    return forces;
}

void particle_print(particle p) {
    printf("m = %g\n", p.m);
    vec2_print(p.r);
}

void particle_print_list(particle *p, int number) {
    for (int ip = 0; ip < number; ++ip) {
        printf("particle %d: \n", ip);
        particle_print(p[ip]);
    }
}
