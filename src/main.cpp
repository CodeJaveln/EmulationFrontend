#include <cstddef>
#include <iostream>
#include <ostream>
#include <filesystem>
#include "config.h"
#include "raylib/raylib.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

int main(int argc, char *argv[]) {
    // Check access to config file, if no then ask to create one
    // DONE: Parse it to get systems
    // Check each system to get rom paths
    // Loop over to find directories (and check if valid passable paths inside)
    // Make a list of names in a struct and an index to the current selected, directory name for now only.
    // Initialize Raylib
    // Logic function to handle current selected
    // Pass names struct as data to draw interface
    // If pressed or entered logic function will call function to execute that rom
    // Exits at user request

    auto systems = emufront::parse_systems("systems.ini");
    if (!systems.has_value()) {
        return 1;
    }

    return 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
