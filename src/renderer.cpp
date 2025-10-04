//
// Created by reald on 21.09.2025.
//

#include "renderer.hpp"
#include <iostream>
#include <cstdlib>

Renderer::Renderer(Voronoi& game) : m_voronoi{game} {

}


void Renderer::render() {

    for(size_t site_index = 0; site_index < m_voronoi.get_sites().size(); site_index++) {

        auto& current_site = m_voronoi.get_sites().at(site_index);
        auto _current_site = current_site.getPosition();
        auto _current_site_color = current_site.getColor();

        DrawCircle(_current_site.x, _current_site.y, 3.0f, _current_site_color);


        if(m_voronoi.get_voronoi_cells().size() != 0) {

            auto& voronoi_cells = m_voronoi.get_voronoi_cells().at(site_index); //dangerous if another site is added

            Vector2 polygon[voronoi_cells.size() + 2] = {_current_site};
            int index = voronoi_cells.size() + 1;
            for(auto& voronoi_point : voronoi_cells) {

                DrawCircle(voronoi_point.x, voronoi_point.y, 6.0f, _current_site_color);
                polygon[index] = voronoi_point;
                index--;

                DrawLine(_current_site.x, _current_site.y, voronoi_point.x, voronoi_point.y, _current_site_color);
            }
            polygon[index] = voronoi_cells.at(0);

            DrawTriangleFan(polygon, voronoi_cells.size() + 2, _current_site_color);


        }


    }


}
