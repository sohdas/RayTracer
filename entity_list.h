#define ENTITY_LIST_H
#include "entity.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class entity_list: public entity {
    private:
        entity_list() {}
        entity_list(shared_ptr<entity> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<entity> object) { objects.push_back(object);}

        virtual bool hit (const ray& r, float tmin, float tmax, hit_record& rec) const;

    public:
        std::vector<shared_ptr<entity>> objects;
};