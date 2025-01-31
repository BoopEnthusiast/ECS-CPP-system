#include "raylib.h"
#include <vector>


struct Component {
};

class Entity {
    std::vector<Component> components;

    friend class System;
};


class System {

};


class SMovement : System {

};
struct CMovement : Component {
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

    mainSystem.draw(GetFrameTime());

    EndDrawing();
}