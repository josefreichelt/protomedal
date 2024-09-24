// STD
#include <stdio.h>
// External
#include <raylib.h>
#include <rlgl.h>
#include <nuklear.h>
// Local
#include "player.h"
#include "raylib.h"
#include "raymath.h"

void PlayerInit(Player* self)
{
    self->camera = (Camera) {
        .position = { 0.0f, 2.5f, 5.0f }, // from player pos
        .target = { 0.0f, 0.0f, 0.0f },
        .fovy = 45.0f,
        .up = { 0.0f, 1.0f, 0.0f },
        .projection = CAMERA_PERSPECTIVE
    };
    printf("Initialized player\n");
    self->position = (Vector3) { 0.0f, 0.5f, 0.0f };
    self->angle = 0.0f;
    self->movementSpeed = 10.0f;
    self->rotationSpeed = 100.0f;
}
void PlayerUpdate(Player* self, float deltaTime)
{
    static Vector3 cameraOffset = { 0.0f, 2.5f, 5.0f };
    Vector3* playerPos = &self->position;
    Camera3D* cam = &self->camera;
    Vector3 direction = { 0, 0, 0 };
    if (IsKeyDown(KEY_Q)) {
        /* playerPos->x -= 0.1f; */
        self->angle += self->rotationSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_E)) {
        /* playerPos->x += 0.1f; */
        self->angle -= self->rotationSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        /* playerPos->z -= 0.1f; */
        direction.x -= self->movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_D)) {
        /* playerPos->z += 0.1f; */
        direction.x += self->movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_W)) {
        /* playerPos->z -= 0.1f; */
        direction.z -= self->movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        /* playerPos->z += 0.1f; */
        direction.z += self->movementSpeed * deltaTime;
        ;
    }
    if (IsKeyDown(KEY_SPACE)) {
        cam->position.y += 0.1f;
        cam->target.y += 0.1f;
        playerPos->y += 0.1f;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {

        cam->position.y -= 0.1f;
        cam->target.y -= 0.1f;
        playerPos->y -= 0.1f;
    }
    if (IsKeyDown(KEY_UP)) {
        cameraOffset.y += 0.1f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        cameraOffset.y -= 0.1f;
    }
    cam->position = Vector3RotateByAxisAngle(cameraOffset, (Vector3) { 0, 1.0f, 0 }, DEG2RAD * self->angle);
    /* cam->position = Vector3Add(*playerPos, cam->position); */
    direction = Vector3RotateByAxisAngle(direction, (Vector3) { 0, 1.0f, 0 }, DEG2RAD * self->angle);
    *playerPos = Vector3Add(*playerPos, direction);
    cam->position = Vector3Add(*playerPos, cam->position);
    cam->target = *playerPos;
}

void PlayerDraw(Player* self)
{
    rlPushMatrix();
    rlTranslatef(self->position.x, self->position.y, self->position.z);
    rlRotatef(self->angle, 0, 1, 0);
    DrawCube((Vector3) { 0, 0, 0 }, 0.25f, 1.0f, 0.25f, ORANGE);
    DrawCube((Vector3) { 0, 0.3f, -0.25f }, 0.25f, 0.25f, 0.25f, GREEN);
    rlPopMatrix();
}

void PlayerDebugGUI(Player* self, struct nk_context* ctx)
{
    Vector3 pos = self->position;
    char playerPosString[200];
    sprintf(playerPosString, "Player position:\n %5.2f,%5.2f,%5.2f", pos.x, pos.y, pos.z);
    nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    Vector3 camPos = self->camera.position;
    sprintf(playerPosString, "Camera position:\n %5.2f,%5.2f,%5.2f", camPos.x, camPos.y, camPos.z);
    nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    sprintf(playerPosString, "Angle:\n %5.2f", self->angle);
    nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    if (nk_button_label(ctx, "Reset")) {
        printf("Button was clicked\n");
        self->position = (Vector3) { 0, 0, 0 };
        self->camera.position = (Vector3) { 0, 2.5f, 5.0f };
        self->camera.target = self->position;
        self->angle = 0;
    }
}
