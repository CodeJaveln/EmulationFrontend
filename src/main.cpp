#include "inipp/inipp.h"
#include "raylib/raylib.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

int main(int argc, char *argv[]) {
    // Check access to config file, if no then ask to create one
    // Parse it to get systems (NULL terminated or rather nullptr)
    // Check each system to get rom paths
    // Loop over to find directories (and check if valid passable paths inside)
    // Make a list of names in a struct and an index to the current selected, directory name for now only.
    // Initialize Raylib
    // Logic function to handle current selected
    // Pass names struct as data to draw interface
    // If pressed or entered logic function will call function to execute that rom
    // Exits at user request
    
    inipp::Ini<char> ini;
    std::ifstream is("systems.ini");
    ini.parse(is);
    std::cout << "ini file:" << std::endl;
    ini.generate(std::cout);

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
