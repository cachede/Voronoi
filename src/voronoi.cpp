//
// Created by reald on 21.09.2025.
//

#include "voronoi.hpp"
#include <random>
#include <iostream>

Voronoi::Voronoi() {

    m_bb_rectangle = raylib::Rectangle(s_min_x_pos - s_padding, s_min_y_pos - s_padding, s_max_x_pos - s_min_x_pos + s_padding, s_max_y_pos - s_min_y_pos + s_padding);
}

void Voronoi::generate(uint16_t amount_sites) {

    m_sites.clear();

    for(size_t i = 0; i < amount_sites; i++) {

        float random_x = generate_random_number(s_min_x_pos, s_max_x_pos);
        float random_y = generate_random_number(s_min_y_pos, s_max_y_pos);

        m_sites.push_back(raylib::Vector2(random_x, random_y));
    }

}

void Voronoi::clear() {

    m_sites.clear();


}


float Voronoi::generate_random_number(float min, float max) {

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<float> uniform_dist(min, max);
    float random_value = uniform_dist(e1);

    return random_value;
}

raylib::Rectangle Voronoi::getBBBox() {
    return m_bb_rectangle;
}

std::vector<raylib::Vector2>& Voronoi::get_sites() {
    return m_sites;
}
