#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "utility.h"
#include "entity_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r, const entity& world, int depth) {
    hit_record rec;
    // Check if light bounce limit has been exceeded
    if (depth <= 0)
        return color(0,0,0);

    // Check for hit on entity
    if (world.hit(r,0,infinity,rec)) {
        point3 target = rec.p + rec.normal + vec3::random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target-rec.p), world, depth - 1);
    }
    //Else, render background
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);

    // linear interpolation from white to blue:  (1-t)*'blue' + (t)*'white'
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 384;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

    entity_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.9)); // Small center spere
    world.add(make_shared<sphere>(point3(0,-100.5, -1), 100)); // Large lower sphere

    camera cam;

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_float()) / (image_width - 1);
                auto v = (j + random_float()) / (image_height - 1);
                ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}