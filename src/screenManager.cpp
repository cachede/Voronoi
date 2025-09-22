//
// Created by reald on 21.09.2025.
//

#include "screenManager.hpp"

ScreenManager::ScreenManager(std::string window_name) : m_screen_width{SCREEN_WIDTH}, m_screen_height{SCREEN_HEIGHT}, m_window_name{window_name} {

}

ScreenManager::ScreenManager(uint16_t screen_width, uint16_t screen_height)
    : m_screen_width{screen_width}, m_screen_height{screen_height} {

}
