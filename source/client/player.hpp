#pragma once
#include <raylib.h>

struct Player {
    Vector3 position;
    Camera camera;
    float angle;
    float movementSpeed;
    float rotationSpeed;
};

void PlayerInit(Player& self);
void PlayerUpdate(Player& self, float deltaTime);
void PlayerDraw(Player& self);
void PlayerDebugGUI(Player& self);
