#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>


struct Component {
};

class Entity {
    std::vector<Component> components;

    template <typename T>
    void joinSystem(std::unordered_map<Entity, T>& systemToJoin, const T& component) {
        systemToJoin[&this] = component;
    }

    friend class System;
};


class System {

};


class SMovement : System {

};
class SDraw : System {

};
struct CTransform : Component {

};

struct CDraw : Component {
    Color color;
};

struct CDrawShape : CDraw {
    Vector2 offsetPosition;
};

struct CDrawCircle : CDrawShape {
    float radius;
};


struct ECS {
    std::unordered_set<Entity> allEntities;
    std::unordered_map<Entity, CTransform> transformEntities;
    std::unordered_map<Entity, CDraw> drawnEntities;
} ecs;

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