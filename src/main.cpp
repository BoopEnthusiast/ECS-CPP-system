/* raylib */
#include "raylib.h"
#include "raymath.h"

/* std */
// misc
#include <iostream>
#include <memory>
// data structures
#include <vector>
#include <map>
#include <set>


struct System
{
    virtual void process() = 0;
};

struct Component
{

};

class Registry
{
public:
    std::vector<int> entities = {0};
    std::set<std::unique_ptr<System>> systems;
    std::map<int, std::set<Component>> components;

    int newEntity()
    {
        entities.push_back(entities.back() + 1);
        return entities.back();
    }

    template <typename ComponentType>
    std::vector<Component> getAllOfComponent() 
    {
        std::vector<Component> componentsToReturn;
        for (std::set<Component> component : components)
        {

        }
        return componentsToReturn;
    }
} registry;

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


struct DrawSystem : System
{
    void process() override {
        DrawCircle(100, 100, 50.0f, RED);
    }
};


int main()
{
    InitWindow(screenWidth, screenHeight, "Raylib Test");

    registry.systems.emplace(std::make_unique<DrawSystem>());

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
    for (const std::unique_ptr<System>& system : registry.systems)
    {
        system->process();
    }

    // Show FPS
    DrawFPS(10, 10);

    EndDrawing();
    /* End draw phase */
}