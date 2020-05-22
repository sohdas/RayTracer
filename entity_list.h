#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H
#include "entity.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class entity_list: public entity {
    public:
        entity_list() {}
        entity_list(shared_ptr<entity> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<entity> object) { objects.push_back(object);}

        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    public:
        std::vector<shared_ptr<entity>> objects;
};

bool entity_list::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest = tmax;

    for (const auto& object : objects) {
        if (object -> hit(r, tmin, closest, temp_rec)) {
            hit_anything = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif