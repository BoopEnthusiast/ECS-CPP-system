#include "raylib.h"
#include <vector>


class Component {
protected:
    void setup() {

    }

    void draw(const float delta) {

    }

    friend class System;
};

class Entity {
private:
    std::vector<Component> components;

    friend class System;
};


class System {
private:
    std::vector<Entity> entities;

public:
    void setupComponents() {
        for (Entity entity : entities) {
            for (Component component : entity.components) {
                component.setup();
            }
        }
    }

    void draw(const float delta) {
        for (Entity entity : entities) {
            for (Component component : entity.components) {
                component.draw(delta);
            }
        }
    }
};


int screenWidth = 800;
int screenHeight = 450;

Camera camera = { 0 };

System mainSystem = System();

void UpdateDrawFrame();



int main() {

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    mainSystem.setupComponents();

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

    mainSystem.draw(GetFPS());

    EndDrawing();
}