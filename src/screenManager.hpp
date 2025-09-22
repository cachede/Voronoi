//
// Created by reald on 21.09.2025.
//

#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <cstdint>
#include <string>


constexpr uint16_t SCREEN_WIDTH = 1024;
constexpr uint16_t SCREEN_HEIGHT = 768;

class ScreenManager {

public:

    ScreenManager(uint16_t screen_width, uint16_t screen_height);
    explicit ScreenManager(std::string window_name);

    uint16_t m_screen_width;
    uint16_t m_screen_height;
    std::string m_window_name;

};


#endif //SCREENMANAGER_HPP
