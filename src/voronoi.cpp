//
// Created by reald on 21.09.2025.
//

#include "voronoi.hpp"
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>

Voronoi::Voronoi(float min_x_pos, float max_x_pos, float min_y_pos, float max_y_pos, float padding) {

    m_bounding_cell.push_back(raylib::Vector2(min_x_pos /*+ padding*/, min_y_pos/* + padding*/));
    m_bounding_cell.push_back(raylib::Vector2(max_x_pos /*+ padding*/, min_y_pos/* + padding*/));
    m_bounding_cell.push_back(raylib::Vector2(max_x_pos /*+ padding*/, max_y_pos/* - padding*/));
    m_bounding_cell.push_back(raylib::Vector2(min_x_pos /*- padding*/, max_y_pos/* - padding*/));
    m_padding = padding;
}

void Voronoi::generate_random(uint16_t amount_sites) {

    for(size_t i = 0; i < amount_sites; i++) {

        float random_x = generate_random_number(m_bounding_cell.at(TL_INDEX).x + m_padding, m_bounding_cell.at(TR_INDEX).x - m_padding);
        float random_y = generate_random_number(m_bounding_cell.at(TL_INDEX).y, m_bounding_cell.at(BL_INDEX).y - m_padding);

        m_sites.push_back(raylib::Vector2(random_x, random_y));
    }

}

void Voronoi::generate_at(Site site) {

    m_sites.push_back(site);

}

int Voronoi::generate() {

    if(m_sites.empty()) {
        std::cerr << "Must generate at least 1 site..." << std::endl;
        return -1;
    }

    size_t current_site_index = 0;
    for(auto& current_site : m_sites) {

        auto cell = m_bounding_cell;
        auto _current_site = current_site.getPosition();


        for(auto& neighbor_site : m_sites) {

            auto _neighbor_site = neighbor_site.getPosition();
            if(_current_site == _neighbor_site) {
                continue;
            }
            size_t cell_size = cell.size();

            std::vector<raylib::Vector2> current_new_cell;

            raylib::Vector3 bisector = calculate_bisector(_current_site, _neighbor_site);

            if(bisector.GetX() == 0 && bisector.GetY() == 0) continue; //undefined

            size_t first_intersection_index = 0;
            size_t second_intersection_start_index = 0;
            std::optional<raylib::Vector2> first_intersection;
            std::optional<raylib::Vector2> second_intersection;
            // finde die erste intersection in aktueller zelle
            for(size_t i = 0; i < cell.size(); i++) {

                auto current_cell = cell.at(i);
                auto next_cell = cell.at((i + 1) % cell.size());

                first_intersection = line_segment_intersection(bisector, current_cell, next_cell);

                if(first_intersection.has_value()) {

                    current_new_cell.push_back(first_intersection.value());
                    current_new_cell.push_back(next_cell);

                    first_intersection_index = (i+1) % cell_size;

                    break;
                }
            }

            if(current_new_cell.size() == 0) {
                current_new_cell = cell; //keine intersection gefunden, muss eigentlich falsch sein
            } else {

                //finde die zweite intersection in aktueller zelle
                for(size_t k = first_intersection_index; k < cell.size(); k++) {

                    auto current_vertex = cell.at(k);
                    auto next_vertex = cell.at((k+1) % cell.size());

                    second_intersection = line_segment_intersection(bisector, current_vertex, next_vertex);

                    if(second_intersection) {

                        current_new_cell.push_back(second_intersection.value());

                        second_intersection_start_index = k + 1;
                        break;
                    }
                    // alle vertexe auf dem weg zur nächsten intersection werden mitgenommen
                    current_new_cell.push_back(next_vertex);

                }


                //wenn punkt nicht im polygon, dann andere richtung
                if(!point_in_polygon(_current_site, current_new_cell)) {
                    current_new_cell.clear();
                    current_new_cell.push_back(second_intersection.value());   //jetzt fängt celle mit t2 an

                    raylib::Vector2 v1;
                    raylib::Vector2 v2;

                    for(size_t k = second_intersection_start_index; k % cell_size > first_intersection_index || k % cell_size < first_intersection_index; k++) {

                        v1 = cell[k % cell_size];
                        v2 = cell[(k + 1) % cell_size];

                        if(v1 == v2) continue;

                        current_new_cell.push_back(v1);
                    }

                    if(first_intersection != v1) current_new_cell.push_back(first_intersection.value());

                }
            }

            cell = current_new_cell;    //update aktuelle zelle

        }//for neightbor_site

        if(!cell.empty()) {
            m_voronoi_cells.push_back(cell);
        }

        current_site_index++;
    }//for current_site

    return 0;
}

void Voronoi::clear() {

    m_sites.clear();
    m_voronoi_cells.clear();
}

std::vector<std::vector<raylib::Vector2>>& Voronoi::get_voronoi_cells() {
    return m_voronoi_cells;
}


float Voronoi::generate_random_number(float min, float max) {

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<float> uniform_dist(min, max);
    float random_value = uniform_dist(e1);

    return random_value;
}

bool Voronoi::point_in_polygon(raylib::Vector2 point, std::vector<raylib::Vector2> polygon) {

    size_t n = polygon.size();

    for(int i = 0; i < n; i++) {

        raylib::Vector2 t(polygon[i].x - polygon[(i+1)%n].x, polygon[i].y - polygon[(i+1)%n].y);
        raylib::Vector2 u(point.x - polygon[(i+1)%n].x, point.y - polygon[(i+1)%n].y);
        raylib::Vector2 v(polygon[(i+2)%n].x - polygon[(i+1)%n].x, polygon[(i+2)%n].y - polygon[(i+1)%n].y);

        float t_cross_u = t.x * u.y - t.y * u.x;
        float t_cross_v = t.x * v.y - t.y * v.x;
        float v_cross_u = v.x * u.y - v.y * u.x;
        float v_cross_t = v.x * t.y - v.y * t.x;

        if(!(t_cross_u * t_cross_v >= 0.0 && v_cross_u * v_cross_t >= 0.0)) {
            return false;
        }

    }

    return true;
}

raylib::Vector3 Voronoi::calculate_bisector(raylib::Vector2 A, raylib::Vector2 B) {

    raylib::Vector2 middle_point((A.x + B.x) / 2, (A.y + B.y) / 2);

    float a = B.x - A.x;
    float b = B.y - A.y;
    float c = -a * middle_point.x -b * middle_point.y;

    return raylib::Vector3(a, b, c);
}

std::optional<raylib::Vector2> Voronoi::line_segment_intersection(raylib::Vector3 line, raylib::Vector2 point_A, raylib::Vector2 point_B) {

    float a = point_A.y - point_B.y;
    float b = point_B.x - point_A.x;
    float c = point_A.x * point_B.y - point_B.x * point_A.y;

    raylib::Vector3 AB_line(a,b,c);

    if((line.x / line.y == AB_line.x / AB_line.y) && (line.z / line.y == AB_line.z / AB_line.y)) return raylib::Vector2(); //idk what this does

    raylib::Vector3 p = line.CrossProduct(AB_line);

    if(p.z == 0) {
        return std::nullopt;
    }

    raylib::Vector2 intersection(ceil(p.x / p.z), ceil(p.y / p.z)); // homogen(3d) -> heterogen(2d)
    //check ob intersection zwischen A und B
    bool is_intersecting_x = intersection.GetX() <= std::max(point_A.x, point_B.x)
                             && intersection.GetX() >= std::min(point_A.x, point_B.x);

    bool is_intersecting_y = intersection.GetY() <= std::max(point_A.y, point_B.y)
                             && intersection.GetY() >= std::min(point_A.y, point_B.y);

    if (is_intersecting_x && is_intersecting_y) {
        return intersection;
    }


    return std::nullopt;

}

std::vector<raylib::Vector2>& Voronoi::getBBBox() {

    //raylib::Rectangle rec(m_bounding_cell.x + m_padding, m_bounding_cell.y + m_padding, m_bounding_cell.width -  2 * m_padding,
     //   m_bounding_cell.height - 2 * m_padding);
    return m_bounding_cell;
}

std::vector<Site>& Voronoi::get_sites() {
    return m_sites;
}
