#include "raylib.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>


void UpdateDrawFrame();

struct Player 
{
    const float SPEED = 10.0f;
    const float RADIUS = 10.0f;

    Vector2 position;
    Vector2 velocity;

    void update(float delta) 
    {   
        Vector2 direction{};
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) 
            direction.y -= 1;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            direction.y += 1;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            direction.x -= 1;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            direction.x += 1;
        
        velocity = (Vector2){direction.x * SPEED, direction.y * SPEED};

        position.x += velocity.x * delta;
        position.y += velocity.y * delta;

        std::cout << velocity.x << " " << velocity.y << std::endl;
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