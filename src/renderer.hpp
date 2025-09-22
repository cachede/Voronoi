//
// Created by reald on 21.09.2025.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "voronoi.hpp"

static const raylib::Color s_background_color{0xFF, 0xF4, 0xCE};


class Renderer {

public:
    Renderer(Voronoi& game);
    void render();


private:


    Voronoi& m_voronoi;
};

#endif //RENDERER_HPP
