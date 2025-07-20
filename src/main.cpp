#include <raylib.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

int main(void) {
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
