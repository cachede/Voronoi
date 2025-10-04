#include <iostream>
#include "raylib-cpp.hpp"

// own includes
#include "screenManager.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"         // Hier steht jetzt die RAYGUI-IMPLEMENTATION
#define GUI_VORONOI_IMPLEMENTATION
#include "gui_voronoi.h"
#include "voronoi.hpp"
#include "renderer.hpp"
#include "Site.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    ScreenManager screen_manager("Voronoi");

    raylib::InitWindow(screen_manager.m_screen_width, screen_manager.m_screen_height, screen_manager.m_window_name);

    GuiVoronoiState guiState = InitGuiVoronoi(0, screen_manager.m_screen_height);

    Button current_button = Button::NO_BUTTON;

    Voronoi game(s_min_x_pos, s_max_x_pos, s_min_y_pos, s_max_y_pos, s_padding);
    Renderer renderer(game);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // TODO: evaluate the current user input
        if(current_button == Button::GENERATE_BUTTON) {

            int amount_sites = guiState.SiteSpinnerValue;
            game.generate_random(amount_sites);
            std::cout << "BEFORE" << std::endl;
            game.generate();
            std::cout << "AFTER" << std::endl;
        } else if (current_button == Button::CLEAR_BUTTON) {

            game.clear();
        } else if (current_button == Button::RANDOM_BUTTON) {

            int random_number = rand() % 100 + 1;
            guiState.SiteSpinnerValue = random_number;
        } else if(current_button == Button::WINDOW_PRESSED) {
            raylib::Vector2 current_mouse_pos = GetMousePosition();
            if(game.get_sites().size() == 0) {
                Site site(current_mouse_pos, RED);
                game.generate_at(site);
            } else {
                Site site(current_mouse_pos, BLUE);
                game.generate_at(site);
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            current_button = GuiVoronoi(&guiState);
            renderer.render();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
