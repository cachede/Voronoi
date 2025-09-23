//
// Created by reald on 21.09.2025.
//

#include "voronoi.hpp"
#include <random>
#include <iostream>

Voronoi::Voronoi(float min_x_pos, float max_x_pos, float min_y_pos, float max_y_pos, float padding) {

    m_bb_rectangle = raylib::Rectangle(min_x_pos - padding, min_y_pos - padding, max_x_pos - min_x_pos + 2 * padding, max_y_pos - min_y_pos + 2 * padding);

    m_padding = padding;
}

void Voronoi::generate(uint16_t amount_sites) {

    m_sites.clear();

    for(size_t i = 0; i < amount_sites; i++) {

        float random_x = generate_random_number(m_bb_rectangle.x + m_padding, m_bb_rectangle.x + m_bb_rectangle.width -  2 * m_padding);
        float random_y = generate_random_number(m_bb_rectangle.y + m_padding, m_bb_rectangle.y + m_bb_rectangle.height - 2 * m_padding);

        m_sites.push_back(raylib::Vector2(random_x, random_y));
    }

}

void Voronoi::generate_at(raylib::Vector2 pos) {

    m_sites.push_back(pos);
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

    raylib::Rectangle rec(m_bb_rectangle.x + m_padding, m_bb_rectangle.y + m_padding, m_bb_rectangle.width -  2 * m_padding,
        m_bb_rectangle.height - 2 * m_padding);
    return m_bb_rectangle;
}

std::vector<raylib::Vector2>& Voronoi::get_sites() {
    return m_sites;
}
