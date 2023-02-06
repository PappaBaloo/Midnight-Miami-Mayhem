#include "raylib.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "raymath.h"
#include "rlgl.h"
#include <float.h>

long oldseed;

int getRand(int min, int max)
{
    time_t seed;
    seed = time(NULL) + oldseed;

    oldseed = seed;

    srand(seed);

    int n = max - min + 1;
    int i = rand() % n;

    if (i < 0)
    {
        i = -i;
    }
    return min + i;
}

int main(void)
{
    // Initialize the window and the game context
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Main Menu");

    // Define the main menu options
    const char *options[3] = {
        "New Game",
        "Options",
        "Exit"};
    int currentOption = 0;

    // Define the font and the font size
    Font font = GetFontDefault();
    int fontSize = 20;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Check for user input
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            currentOption = (currentOption + 1) % 3;
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            currentOption = (currentOption + 2) % 3;
        }
        else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        {
            switch (currentOption)
            {
            case 0:
                // Start the new game
                break;
            case 1:
                // Open the options menu
                break;
            case 2:
                // Exit the game
                CloseWindow();
                return 0;
                break;
            }
        }

        // Clear the screen to a light blue color
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the main menu options
        for (int i = 0; i < 3; i++)
        {
            if (i == currentOption)
            {
                DrawText(options[i], screenWidth / 2 - MeasureText(options[i], fontSize) / 2, screenHeight / 2 - fontSize * 1.5f + i * fontSize * 2, fontSize, BLACK);
            }
            else
            {
                DrawText(options[i], screenWidth / 2 - MeasureText(options[i], fontSize) / 2, screenHeight / 2 - fontSize * 1.5f + i * fontSize * 2, fontSize, GRAY);
            }
        }

        EndDrawing();
    }

    // Close the window and de-initialize the game context
    CloseWindow();
    return 0;
}