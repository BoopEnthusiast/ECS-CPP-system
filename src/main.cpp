#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>


struct Player {
    Vector2 position;
    
};


const int screenWidth = 850;
const int screenHeight = 500;

int main() {

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}


// Update and draw game frame
void UpdateDrawFrame() {   
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    EndDrawing();
}