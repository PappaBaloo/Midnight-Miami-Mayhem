#include "raylib.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "raymath.h"
#include "rlgl.h"
#include <float.h>

// DEV MODE
#define DEV_MODE

long oldseed;
Color neonBlue = (Color){135, 206, 250, 255};
Color neonPurple = (Color){255, 0, 255, 255};
Color neonRed = (Color){255, 0, 128, 255};

void drawBackgroundLevel(Texture background)
{
    DrawTexture(background, 0, 0, WHITE);
}

void getControls(Rectangle *player, Camera2D *characterCamera)
{

    if (IsKeyDown(KEY_W))
    {
        player->y -= 5.5f;
    }
    if (IsKeyDown(KEY_A))
    {
        player->x -= 5.5f;
    }
    if (IsKeyDown(KEY_S))
    {
        player->y += 5.5f;
    }
    if (IsKeyDown(KEY_D))
    {
        player->x += 5.5f;
    }
    characterCamera->target = (Vector2){player->x, player->y};
}

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

    // Load custom font
    Font font = LoadFont("fonts/Alien-Encounters-Italic.ttf");

    // Load level textures
    Texture2D level1 = LoadTexture("textures/level1.png");

    // Define the main menu options
    const char *options[3] = {
        "New Game",
        "Options",
        "Exit"};
    int currentOption = 0;

    // Define the font size
    int fontSize = 40;

    // Define timer
    float timer = 0.0f;
    float duration = 2.0f;

    // Define level 1 start
    Vector2 levelStartPos = {30, 30};

    // Define player rec in temporary replacement for the texture
    Rectangle player;
    player.height = 15;
    player.width = 15;
    player.x = levelStartPos.x;
    player.y = levelStartPos.y;

    // Initialize camera
    Camera2D characterCamera = {0};
    characterCamera.target = (Vector2){player.x, player.y};
    characterCamera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    characterCamera.zoom = 1.0f;

    // Main game loop
    SetTargetFPS(60);
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

                // Main game loop
                while (!WindowShouldClose())
                {

                    // Player movement and camera controls
                    getControls(&player, &characterCamera);
                    characterCamera.zoom += ((float)GetMouseWheelMove() * 0.05f);
                    characterCamera.zoom = Clamp(characterCamera.zoom, 0.5f, 2.0f);

                    // Clear the screen
                    BeginDrawing();
                    ClearBackground(BLACK);
                    BeginMode2D(characterCamera);
                    {
                        DrawTexture(level1, 0, 0, WHITE);
                        DrawRectangleRec(player, WHITE);
                    }

                    EndDrawing();
                }

                // End the game
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

        // Clear the screen
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the main menu options and game name

        DrawTextEx(font, "Midnight Miami Mayhem", (Vector2){screenWidth / 2 - MeasureTextEx(font, "Midnight Miami Mayhem", fontSize * 1.5, 2).x / 2, screenHeight / 2 - fontSize * 3.5f}, fontSize * 1.5, 2, neonRed);

        for (int i = 0; i < 3; i++)
        {
            if (i == currentOption)
            {
                DrawTextEx(font, options[i], (Vector2){screenWidth / 2 - MeasureTextEx(font, options[i], fontSize, 2).x / 2, screenHeight / 2 - fontSize * 1.5f + i * fontSize * 2}, fontSize, 2, neonPurple);
            }
            else
            {
                DrawTextEx(font, options[i], (Vector2){screenWidth / 2 - MeasureTextEx(font, options[i], fontSize, 2).x / 2, screenHeight / 2 - fontSize * 1.5f + i * fontSize * 2}, fontSize, 2, neonBlue);
            }
        }
        EndDrawing();
    }

    // Close the window and de-initialize the game context
    UnloadTexture(level1);
    UnloadFont(font);
    CloseWindow();
    return 0;
}