//
// Created by reald on 21.09.2025.
//

#include "renderer.hpp"

Renderer::Renderer(Voronoi& game) : m_voronoi{game} {

}


void Renderer::render() {

    DrawRectangle(m_voronoi.getBBBox().x, m_voronoi.getBBBox().y, m_voronoi.getBBBox().width, m_voronoi.getBBBox().height, s_background_color);

    for(auto& elem : m_voronoi.get_sites()) {
        DrawCircle(elem.x, elem.y, 3.0, RED);
    }

}
