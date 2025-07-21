#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
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

    auto system_profiles = emufront::parse_systems("systems.ini");
    if (!system_profiles.has_value()) {
        return 1;
    }

    auto rom_profiles = emufront::read_roms(system_profiles.value());

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");

    SetTargetFPS(60);

    ssize_t rom_index = 0;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) {
            rom_index--;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            rom_index++;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            rom_profiles[rom_index].system.emulator.run(rom_profiles[rom_index].rom_path);
        }

        if (rom_index < 0) rom_index = 0;
        if (rom_index >= static_cast<ssize_t>(rom_profiles.size())) rom_index = rom_profiles.size() - 1; 

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawText(rom_profiles[rom_index].dir_name.c_str(), 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
