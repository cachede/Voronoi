//
// Created by reald on 21.09.2025.
//

#include "renderer.hpp"
#include <iostream>
Renderer::Renderer(Voronoi& game) : m_voronoi{game} {

}


void Renderer::render() {

    for(auto& elem : m_voronoi.get_sites()) {
        DrawCircle(elem.x, elem.y, 3.0, RED);
    }

    for(auto& elem : m_voronoi.get_voronoi_cells()) {

        for(auto& point : elem) {

            DrawCircle(point.x, point.y, 5.0, BLUE);

        }

    }


}
