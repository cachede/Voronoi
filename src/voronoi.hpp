//
// Created by reald on 21.09.2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <vector>

#include "raylib-cpp.hpp"

// i guess i can rename this to vornoi.hpp
class Voronoi {

public:

    explicit Voronoi();
    void generate(uint16_t amount_sites);
    void clear();
    raylib::Rectangle getBBBox();
    std::vector<raylib::Vector2>& get_sites();
    //TODO: hardcoded values
    static constexpr float s_min_x_pos = 50;
    static constexpr float s_max_x_pos = 1024 - 50;
    static constexpr float s_min_y_pos = 50;
    static constexpr float s_max_y_pos = 768 - 120 - 50;
    static constexpr float s_padding   = 10.0f;

private:

    raylib::Rectangle               m_bb_rectangle;
    std::vector<raylib::Vector2>    m_sites;


    static float generate_random_number(float min, float max);


};

#endif //GAME_HPP
