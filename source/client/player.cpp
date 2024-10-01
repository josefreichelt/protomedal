// STD
#include <iostream>
#include <sstream>
#include <iomanip>
// External
#include <raylib.h>
#include <raygui.h>
#include <rlgl.h>
#include <raymath.h>
// Local
#include "player.hpp"

void PlayerInit(Player& self)
{
    self.camera = (Camera) {
        .position = { 0.0f, 5.0f, 5.0f }, // from player pos
        .target = { 0.0f, 0.0f, 0.0f },
        .fovy = 45.0f,
        .up = { 0.0f, 1.0f, 0.0f },
        .projection = CAMERA_PERSPECTIVE
    };
    self.position = (Vector3) { 0.0f, 0.5f, 0.0f };
    self.angle = 0.0f;
    self.movementSpeed = 10.0f;
    self.rotationSpeed = 100.0f;
}
static Vector3 cameraOffset = { 0.0f, 5.0f, 5.0f };
void PlayerUpdate(Player& self, float deltaTime)
{
    Vector3* playerPos = &self.position;
    Camera3D* cam = &self.camera;
    Vector3 direction = { 0, 0, 0 };
    if (IsKeyDown(KEY_Q)) {
        /* playerPos->x -= 0.1f; */
        self.angle += self.rotationSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_E)) {
        /* playerPos->x += 0.1f; */
        self.angle -= self.rotationSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        /* playerPos->z -= 0.1f; */
        direction.x -= self.movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_D)) {
        /* playerPos->z += 0.1f; */
        direction.x += self.movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_W)) {
        /* playerPos->z -= 0.1f; */
        direction.z -= self.movementSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        /* playerPos->z += 0.1f; */
        direction.z += self.movementSpeed * deltaTime;
        ;
    }
    if (IsKeyPressed(KEY_H)) {
        self.position = Vector3 { 0, 0, 0 };
        self.angle = 0;
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
    cam->position = Vector3RotateByAxisAngle(cameraOffset, (Vector3) { 0, 1.0f, 0 }, DEG2RAD * self.angle);
    /* cam->position = Vector3Add(*playerPos, cam->position); */
    direction = Vector3RotateByAxisAngle(direction, (Vector3) { 0, 1.0f, 0 }, DEG2RAD * self.angle);
    *playerPos = Vector3Add(*playerPos, direction);
    cam->position = Vector3Add(*playerPos, cam->position);
    cam->target = *playerPos;
}

void PlayerDraw(Player& self)
{
    rlPushMatrix();
    rlTranslatef(self.position.x, self.position.y, self.position.z);
    rlRotatef(self.angle, 0, 1, 0);
    DrawCube((Vector3) { 0, 0, 0 }, 0.1f, 1.0f, 0.1f, ORANGE);
    DrawCube((Vector3) { 0, 0.3f, -0.1f }, 0.1f, 0.1f, 0.1f, GREEN);
    rlPopMatrix();
    DrawCube(self.camera.target, 0.2f, 0.2f, 0.2f, Color { 120, 120, 120, 120 });
    DrawCube(Vector3Subtract(self.camera.target, self.position), 0.2f, 0.2f, 0.2f, Color { 120, 40, 120, 40 });
    auto unTranslatedTarget = Vector3Subtract(self.camera.target, self.position);
    auto unTranslatedCamPos = Vector3Subtract(self.camera.position, self.position);
    DrawCube(unTranslatedTarget, 0.2f, 0.2f, 0.2f, Color { 120, 40, 120, 40 });
    DrawCube(unTranslatedCamPos, 0.2f, 0.2f, 0.2f, Color { 120, 120, 40, 40 });
}

void PlayerDebugGUI(Player& self)
{
    auto screenWidth = GetScreenWidth();
    Vector3 pos = self.position;
    auto camPos = self.camera.position;
    auto camTarget = self.camera.target;

    std::ostringstream playerPosText;
    playerPosText << "Player x: " << pos.x << "y: " << pos.y << "z: " << pos.z << std::endl;
    std::ostringstream camPosText;
    camPosText << "CamPos x: " << camPos.x << "y: " << camPos.y << "z: " << camPos.z << std::endl;
    std::ostringstream camPosTargetText;
    camPosTargetText << "CamTarget x: " << camTarget.x << "y: " << camTarget.y << "z: " << camTarget.z << std::endl;

    auto unTranslatedCamPos = Vector3Subtract(self.camera.position, self.position);
    auto angle = Vector3Angle(unTranslatedCamPos, Vector3 { 0, 1.0f, 0 });
    std::ostringstream camAngleText;
    camAngleText << "CamAngle: " << std::fixed << std::setprecision(2) << RAD2DEG * angle << std::endl;

    GuiLabel({ static_cast<float>(screenWidth - MeasureText(playerPosText.str().c_str(), 12)), 40.0f, 200, 20 }, playerPosText.str().c_str());
    GuiLabel({ static_cast<float>(screenWidth - MeasureText(camPosText.str().c_str(), 12)), 60.0f, 200, 20 }, camPosText.str().c_str());
    GuiLabel({ static_cast<float>(screenWidth - MeasureText(camPosTargetText.str().c_str(), 12)), 80.0f, 200, 20 }, camPosTargetText.str().c_str());
    GuiLabel({ static_cast<float>(screenWidth - MeasureText(camAngleText.str().c_str(), 12)), 100.0f, 200, 20 }, camAngleText.str().c_str());
    // char playerPosString[200];
    // sprintf(playerPosString, "Player position:\n %5.2f,%5.2f,%5.2f", pos.x, pos.y, pos.z);
    // nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    // Vector3 camPos = self->camera.position;
    // sprintf(playerPosString, "Camera position:\n %5.2f,%5.2f,%5.2f", camPos.x, camPos.y, camPos.z);
    // nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    // sprintf(playerPosString, "Angle:\n %5.2f", self->angle);
    // nk_label(ctx, playerPosString, NK_TEXT_LEFT);
    // if (nk_button_label(ctx, "Reset")) {
    //     printf("Button was clicked\n");
    //     self->position = (Vector3) { 0, 0, 0 };
    //     self->camera.position = (Vector3) { 0, 2.5f, 5.0f };
    //     self->camera.target = self->position;
    //     self->angle = 0;
    // }
}
