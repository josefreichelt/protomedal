#pragma once
#include <raylib.h>

typedef struct {
    Vector3 position;
    Camera camera;
} Player;

void PlayerInit(Player* self);
