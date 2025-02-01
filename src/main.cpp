#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>


void UpdateDrawFrame();

struct Player 
{
    const float SPEED = 200.0f;
    const float RADIUS = 40.0f;

    Vector2 position;
    Vector2 velocity;

    void update(float delta) 
    {   
        Vector2 direction{};
        direction.x = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
        direction.y = (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP)   || IsKeyDown(KEY_W));

        position = Vector2Add(position, Vector2Scale(Vector2Multiply(Vector2Normalize(direction), (Vector2) {SPEED, SPEED}), delta));
    }
} player;

const int screenWidth = 850;
const int screenHeight = 500;

int main() 
{
    InitWindow(screenWidth, screenHeight, "Raylib Test");

    while (!WindowShouldClose()) 
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}


// Update and draw game frame
void UpdateDrawFrame() 
{   
    player.update(GetFrameTime());

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    DrawCircle(player.position.x, player.position.y, player.RADIUS, RED);

    EndDrawing();
}