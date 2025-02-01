#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Entity (just an ID)
struct Entity { 
    int id; 
};

// Component (base)
struct Component { 
    virtual ~Component() = default; 
};

// Example Component
struct Position : Component { 
    Vector2 position;
};

// System (base)
struct System {
    virtual void update(Entity e) = 0;
    virtual ~System() = default;
};

// Example System
class MovementSystem : public System {
private:
    std::vector<std::pair<Entity, Position*>> positions;

public:
    void update(Entity e) override {
        for (auto& [e, pos] : positions) {
            if (IsKeyDown(KEY_D))
                pos->position.x += 0.1f;
        }
    }
    
    void track(Entity e, Position* p) { positions.emplace_back(e, p); }
};

// Minimal registry
struct Registry {
    std::unordered_map<Entity, std::unordered_set<Component*>> entities;
    MovementSystem movement;
    
    void update() {
        // Update tracking
        for (auto& [e, comps] : entities) {
            for (auto* c : comps)
                if (auto* p = dynamic_cast<Position*>(c))
                    movement.track(e, p);
        
            movement.update(e);
        }
    }
} registry;

Entity player{1};

int screenWidth = 800;
int screenHeight = 450;

Camera camera = { 0 };

void UpdateDrawFrame();




int main() {

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    Entity circle = Entity();

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