#pragma once
#include <raylib.h>
 
typedef struct {
    Vector3 position;
    Camera camera;
    float angle;
    float movementSpeed;
    float rotationSpeed;
} Player;

void PlayerInit(Player* self);
void PlayerUpdate(Player* self,float deltaTime);
void PlayerDraw(Player* self);
void PlayerDebugGUI(Player* self,struct nk_context* ctx);
