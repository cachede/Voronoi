//
// Created by reald on 21.09.2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>

#include "raylib-cpp.hpp"

// i guess i can rename this to vornoi.hpp
class Game {

public:

    explicit Game() = default;


private:

    raylib::Rectangle bb_rectangle;

};

#endif //GAME_HPP
