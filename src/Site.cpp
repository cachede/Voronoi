//
// Created by reald on 03.10.2025.
//

#include "Site.hpp"
#include <cstdlib>

Site::Site(raylib::Vector2 position, raylib::Color color) : m_position(position), m_color(color) {

}


Site::Site(raylib::Vector2 position) : m_position(position){

    unsigned char random_r = rand() % U_CHAR_VALUES;
    unsigned char random_g = rand() % U_CHAR_VALUES;
    unsigned char random_b = rand() & U_CHAR_VALUES;

    m_color = raylib::Color(random_r, random_g, random_b);


}

raylib::Vector2& Site::getPosition() {
    return m_position;
}

raylib::Color& Site::getColor() {
    return m_color;
}