#ifndef SPHERE_H
#define SPHERE_H

#include "entity.h"
#include "vec3.h"

class sphere: public entity {
    public:
        sphere() {}
        sphere(point3 cen, float r) : center(cen), radius(r) {};

        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    public:
        point3 center;
        float radius;
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - 4*a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;

        // If intersection is in accepted hit interval, then it is a hit
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            
            return true;
        }
    }
    return false;
}

#endif