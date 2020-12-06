#include <stdlib.h>
#include "util.h"

double rand_to_range(double x0, double x1) {
    double delta = x1 - x0;
    double rescaled = (double)rand() / RAND_MAX * delta + x0;

    return rescaled;
}
