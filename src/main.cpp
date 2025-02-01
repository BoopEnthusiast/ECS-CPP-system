#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <unordered_set>


void UpdateDrawFrame();

struct Entity
{
    virtual void init() = 0;
};

struct Player : Entity
{
    const float SPEED = 200.0f;
    const float RADIUS = 40.0f;

    Vector2 position;
    Vector2 velocity;

    void init() override
    {

    }

    void update(float delta)
    {
        // Get direction of movement
        Vector2 direction{};
        direction.x = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
        direction.y = (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP)   || IsKeyDown(KEY_W));

        // Steps happening here:
        // Normalize direction
        // Multiply direction by speed to make velocity
        // Multiply velocity by delta
        // Add velocity to position
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
    // Update player
    player.update(GetFrameTime());


    /* Draw phase */
    BeginDrawing();
    // Set background/clear previous frame
    ClearBackground(RAYWHITE);
    
    // Draw player
    DrawCircle(player.position.x, player.position.y, player.RADIUS, RED);

    // Show FPS
    DrawFPS(10, 10);

    EndDrawing();
    /* End draw phase */
}