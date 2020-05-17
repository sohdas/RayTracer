#ifndef ENTITY_H
#define ENTITY_H

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    float t;
    bool frontface;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        frontface = dot(r.direction(), outward_normal) < 0;
        normal = frontface ? outward_normal : -outward_normal;
    }
};

class entity {
    public:
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const = 0;
};

#endif