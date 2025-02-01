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

// Positional Component
struct CPosition : Component { 
    Vector2 position;
};

struct CDrawShape : Component {
    Color color;
    float radius; // temp, will be moved to CDrawCircle
};

// System (base)
struct System {
    virtual void update(Entity e) = 0;
    virtual ~System() = default;
};

// Example System
class SMovement : public System {
private:
    std::vector<std::pair<Entity, CPosition*>> positions;

public:
    void update(Entity entity, CPosition* component) override {
        for (auto& [e, pos] : std::pair<Entity, CPosition*>(entity, component)) {
            if (IsKeyDown(KEY_D))
                pos->position.x += 0.1f;
        }
    }
};

class SDrawShape : public System {
private:
    
}

// Minimal registry
struct Registry {
    std::unordered_map<Entity, std::unordered_set<Component*>> entities;
    SMovement movement;
    
    void update() {
        // Update tracking
        for (auto& [e, comps] : entities) {
            for (auto* c : comps)
                if (auto* p = dynamic_cast<CPosition*>(c))
                    movement.update(e, c);
        }
    }

    void draw() {
        for (auto& [e, comps] : entities) {
            for (auto* c : comps)
                if (auto* p = dynamic_cast<CDrawShape*>(c))
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

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}


// Update and draw game frame
void UpdateDrawFrame()
{   
    registry.update();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    registry.draw();

    EndDrawing();
}