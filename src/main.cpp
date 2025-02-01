#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Entity (just an ID)
struct Entity { int id; };

// Component (base)
struct Component { virtual ~Component() = default; };

// Example Component
struct Position : Component { float x, y; };

// System (base)
struct System {
    virtual void update() = 0;
    virtual ~System() = default;
};

// Example System
class MovementSystem : public System {
public:
    void update() override {
        for (auto& [e, pos] : positions)
            pos->x += 0.1f;  // Simple movement logic
    }
    
    void track(Entity e, Position* p) { positions.emplace_back(e, p); }
    
private:
    std::vector<std::pair<Entity, Position*>> positions;
};

// Minimal registry
struct Registry {
    std::unordered_map<Entity, std::vector<Component*>> entities;
    MovementSystem movement;
    
    void update() {
        // Update tracking
        for (auto& [e, comps] : entities)
            for (auto* c : comps)
                if (auto* p = dynamic_cast<Position*>(c))
                    movement.track(e, p);
        
        movement.update();
    }
};

int screenWidth = 800;
int screenHeight = 450;

Camera camera = { 0 };

System mainSystem = System();

void UpdateDrawFrame();




int main() {

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    Entity circle = Entity();

    circle.joinSystem(ecs.drawnEntities, new CDraw);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}


// Update and draw game frame
void UpdateDrawFrame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    EndDrawing();
}