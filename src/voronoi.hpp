//
// Created by reald on 21.09.2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <vector>

#include "raylib-cpp.hpp"


class Voronoi {

public:

    explicit Voronoi(float min_x_pos, float max_x_pos, float min_y_pos, float max_y_pos, float padding);
    void generate(uint16_t amount_sites);
    void generate_at(raylib::Vector2 pos);
    void clear();
    raylib::Rectangle getBBBox();
    std::vector<raylib::Vector2>& get_sites();
    //TODO: hardcoded values

private:

    raylib::Rectangle               m_bb_rectangle;
    std::vector<raylib::Vector2>    m_sites;
    float m_padding;

    static float generate_random_number(float min, float max);


};

#endif //GAME_HPP
