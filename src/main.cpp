#include <iostream>
#include "raylib-cpp.hpp"

// own includes
#include "screenManager.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"         // Hier steht jetzt die RAYGUI-IMPLEMENTATION
#define GUI_VORONOI_IMPLEMENTATION
#include "gui_voronoi.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    ScreenManager screen_manager("Voronoi");

    raylib::InitWindow(screen_manager.m_screen_width, screen_manager.m_screen_height, screen_manager.m_window_name);

    GuiVoronoiState guiState = InitGuiVoronoi(0, screen_manager.m_screen_height);

    Button current_button = Button::NO_BUTTON;

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


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            current_button = GuiVoronoi(&guiState);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
