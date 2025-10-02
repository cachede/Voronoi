//
// Created by reald on 21.09.2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <optional>
#include <vector>

#include "raylib-cpp.hpp"


class Voronoi {

public:

    explicit Voronoi(float min_x_pos, float max_x_pos, float min_y_pos, float max_y_pos, float padding);
    void generate_random(uint16_t amount_sites);
    void generate_at(raylib::Vector2 pos);
    int generate();
    void clear();
    std::vector<raylib::Vector2>& getBBBox();
    std::vector<raylib::Vector2>& get_sites();
    std::vector<std::vector<raylib::Vector2>>& get_voronoi_cells();

private:

    static constexpr size_t TL_INDEX = 0;
    static constexpr size_t TR_INDEX = 1;
    static constexpr size_t BR_INDEX = 2;
    static constexpr size_t BL_INDEX = 3;


    std::vector<raylib::Vector2>    m_cell;
    std::vector<raylib::Vector2>    m_sites;
    float m_padding;
    std::vector<std::vector<raylib::Vector2>> m_voronoi_cells;

    static float generate_random_number(float min, float max);
    static raylib::Vector3 calculate_bisector(raylib::Vector2 a, raylib::Vector2 b);
    static std::optional<raylib::Vector2> line_segment_intersection(raylib::Vector3 line, raylib::Vector2 point_A, raylib::Vector2 point_B);
    static bool point_in_polygon(raylib::Vector2 point, std::vector<raylib::Vector2> polygon);
};

#endif //GAME_HPP
