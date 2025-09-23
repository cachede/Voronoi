/*******************************************************************************************
*
*   Voronoi v1.0.0 - GUI for the user input
*
*   MODULE USAGE:
*       #define GUI_VORONOI_IMPLEMENTATION
*       #include "gui_voronoi.h"
*
*       INIT: GuiVoronoiState state = InitGuiVoronoi();
*       DRAW: GuiVoronoi(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"     // HIER STEHEN NUR FUNKTIONS-PROTOTYPEN

#include <string.h>     // Required for: strcpy()

#ifndef GUI_VORONOI_H
#define GUI_VORONOI_H

typedef struct {
    Vector2 anchor;
    
    bool SiteSpinnerEditMode;
    int SiteSpinnerValue;

    Rectangle layoutRecs[6];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required
    raylib::Rectangle voronoi_window;

} GuiVoronoiState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...
enum class Button : char {RANDOM_BUTTON, GENERATE_BUTTON, CLEAR_BUTTON, SAVE_FILE_BUTTON, WINDOW_PRESSED, NO_BUTTON};

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiVoronoiState InitGuiVoronoi(void);
inline Button GuiVoronoi(GuiVoronoiState *state);
static Button RandomButton();
static Button GenerateButton();
static Button ClearButton();
static Button SaveFileButton();

#ifdef __cplusplus
}
#endif

#endif // GUI_VORONOI_H

/***********************************************************************************
*
*   GUI_VORONOI IMPLEMENTATION - HAS TO HAPPEN ONCE, IT HAS TO
*
************************************************************************************/
#if defined(GUI_VORONOI_IMPLEMENTATION)

#include "raygui.h"
#include <iostream>

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...
static constexpr float GROUP_BOX_WIDTH = 392;
static constexpr float GROUP_BOX_HEIGHT = 120;
static constexpr float GUI_VORONOI_PADDING = 5;

static constexpr float s_min_x_pos = 50;
static constexpr float s_max_x_pos = 1024 - 50;
static constexpr float s_min_y_pos = 50;
static constexpr float s_max_y_pos = 768 - 120 - 50;
static constexpr float s_padding   = 10.0f;

static const raylib::Color s_background_color{0xFF, 0xF4, 0xCE};


//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiVoronoiState InitGuiVoronoi(const float x_position, const float y_position)
{
    GuiVoronoiState state = { 0 };

    state.anchor = (Vector2){ x_position + GUI_VORONOI_PADDING, y_position - GROUP_BOX_HEIGHT - GUI_VORONOI_PADDING};

    state.SiteSpinnerEditMode = false;
    state.SiteSpinnerValue = 0;

    state.layoutRecs[0] = (Rectangle){ state.anchor.x + 0, state.anchor.y + 0, GROUP_BOX_WIDTH, GROUP_BOX_HEIGHT };
    state.layoutRecs[1] = (Rectangle){ state.anchor.x + 168, state.anchor.y + 24, 120, 24 };
    state.layoutRecs[2] = (Rectangle){ state.anchor.x + 312, state.anchor.y + 24, 72, 24 };
    state.layoutRecs[3] = (Rectangle){ state.anchor.x + 272, state.anchor.y + 80, 120, 40 };
    state.layoutRecs[4] = (Rectangle){ state.anchor.x + 152, state.anchor.y + 80, 120, 40 };
    state.layoutRecs[5] = (Rectangle){ state.anchor.x + 32, state.anchor.y + 80, 120, 40 };

    // Custom variables initialization

    state.voronoi_window = raylib::Rectangle(s_min_x_pos, s_min_y_pos, s_max_x_pos - s_min_x_pos, s_max_y_pos - s_min_y_pos);


    return state;
}
static Button RandomButton()
{
    return Button::RANDOM_BUTTON;
}
static Button GenerateButton()
{
    return Button::GENERATE_BUTTON;
}
static Button ClearButton()
{
    return Button::CLEAR_BUTTON;
}
static Button SaveFileButton()
{
    return Button::SAVE_FILE_BUTTON;
}


inline Button GuiVoronoi(GuiVoronoiState *state)
{
    const char *VoronoiGroupboxText = "Voronoi Diagram Editor";
    const char *RandomButtonText = "Random";
    const char *GenerateText = "GENERATE";
    const char *ClearButtonText = "CLEAR";
    const char *SaveFileText = "SAVE FILE";
    const char *SitesSpinnerText = "Amount of sites to generate: ";

    Button button_pressed = Button::NO_BUTTON;

    GuiGroupBox(state->layoutRecs[0], VoronoiGroupboxText);
    if (GuiSpinner(state->layoutRecs[1], SitesSpinnerText, &state->SiteSpinnerValue, 0, 100, state->SiteSpinnerEditMode)) state->SiteSpinnerEditMode = !state->SiteSpinnerEditMode;
    if (GuiButton(state->layoutRecs[2], RandomButtonText)) button_pressed = RandomButton();
    if (GuiButton(state->layoutRecs[5], SaveFileText)) button_pressed = SaveFileButton();
    if (GuiButton(state->layoutRecs[4], ClearButtonText)) button_pressed = ClearButton();
    if (GuiButton(state->layoutRecs[3], GenerateText)) button_pressed = GenerateButton();

    state->voronoi_window.Draw(s_background_color);
    state->voronoi_window.DrawLines(BLACK);

    raylib::Vector2 current_mouse_pos = GetMousePosition();
    bool left_click_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool intersection = CheckCollisionPointRec(current_mouse_pos, state->voronoi_window);

    if(!left_click_pressed && intersection) {
        current_mouse_pos.DrawCircle(3.0f, BLACK);
    } else if (left_click_pressed && intersection) {
        button_pressed = Button::WINDOW_PRESSED;
    }

    return button_pressed;
}

#endif // GUI_VORONOI_IMPLEMENTATION
