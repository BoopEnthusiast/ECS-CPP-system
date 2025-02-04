/* raylib */
#include "raylib.h"
#include "raymath.h"

/* std */
// misc
#include <iostream>
#include <memory>
// data structures
#include <vector>



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
        // Normalize direction // Vector2Normalize(direction)
        // Multiply direction by speed to make velocity // Vector2Multiply(normalized_direction, (Vector2) {SPEED, SPEED})
        // Multiply velocity by delta // Vector2Scale(velocity, delta)
        // Add velocity to position // Vector2Add(position, delta_velocity)
        position = Vector2Add(position, Vector2Scale(Vector2Multiply(Vector2Normalize(direction), (Vector2) {SPEED, SPEED}), delta));
    }
} player;

const int screenWidth = 850;
const int screenHeight = 500;

struct System
{
    virtual void process() = 0;
};

struct PrintSystem : System
{
    void process() override {
        std::cout << "Hello, testing, testing 123" << std::endl;
    }
};


class Registry
{
private:
    std::vector<std::unique_ptr<System>> systems;

public:
    void add_system(std::unique_ptr<System> system_ptr)
    {
        systems.push_back(system_ptr);
    }

    std::vector<std::unique_ptr<System>> get_systems()
    {
        return systems;
    }
} registry;


int main()
{
    InitWindow(screenWidth, screenHeight, "Raylib Test");

    std::shared_ptr<Player> player_ptr; // TODO: Fix this

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
    
    // Go through systems
    for (std::unique_ptr<System> system : registry.get_systems())
    {
        system->process();
    }

    // Show FPS
    DrawFPS(10, 10);

    EndDrawing();
    /* End draw phase */
}