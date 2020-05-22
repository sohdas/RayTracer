#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "ray.h"
#include "vec3.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

inline float deg_to_rad(float deg) {
    return deg * pi / 180;
}

#endif