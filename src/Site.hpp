//
// Created by reald on 03.10.2025.
//

#ifndef SITE_HPP
#define SITE_HPP

#include <vector>
#include "raylib-cpp.hpp"

class Site {

public:
    Site(raylib::Vector2 position, raylib::Color color);
    Site(raylib::Vector2 position);

    raylib::Vector2& getPosition();
    raylib::Color& getColor();


private:

    static const unsigned char U_CHAR_VALUES = 255;

    raylib::Vector2 m_position;
    raylib::Color   m_color;

};



#endif //SITE_HPP
