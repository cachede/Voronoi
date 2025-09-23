//
// Created by reald on 21.09.2025.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "voronoi.hpp"


class Renderer {

public:
    Renderer(Voronoi& game);
    void render();


private:


    Voronoi& m_voronoi;
};

#endif //RENDERER_HPP
