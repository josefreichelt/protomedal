#include "player.h"
#include <stdio.h>

void PlayerInit(Player* self)
{
    self->camera = (Camera) {
        .position = { 0.0f, 0.5f, -5.0f }, // Offset from player pos
        .target = { 0.0f, 0.0f, 0.0f },
        .fovy = 45.0f,
        .up = { 0.0f, 1.0f, 0.0f },
        .projection = CAMERA_PERSPECTIVE
    };
    printf("Initialized player\n");
    self->position = (Vector3) { 0.0f, 0.0f, -5.0f };
}
