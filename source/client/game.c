// STD
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// External
#include "raylib.h"
#include <raylib.h>
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"
// Local
#include "game.h"
#include "player.h"

typedef struct {
    Vector2 playerPosition;
    Player player;
} GameState;

typedef struct {
    int windowWidth;
    int windowHeight;
    char* windowTitle;
} GameWindow;

GameWindow GameWindowInit(void)
{
    GameWindow window;
    window.windowHeight = 1080;
    window.windowWidth = 1920;
    window.windowTitle = (char*)calloc(255, sizeof(char));
    strncpy_s(window.windowTitle, 254, "ProtoMedal", 254);
    window.windowTitle[254] = '\0';
    printf("Game title is %s\n", window.windowTitle);

    // ------------
    // Raylib window init
    printf("Initializing Raylib\n");
    InitWindow(window.windowWidth, window.windowHeight, window.windowTitle);
    SetTargetFPS(60);
    DisableCursor();
    // ------------

    return window;
}

static Camera3D camera = { .position = { 0.0f, 0.5f, -5.0f }, .target = { 0.0f, 0.0f, 0.0f }, .fovy = 45.0f, .up = { 0.0f, 1.0f, 0.0f }, .projection = CAMERA_PERSPECTIVE };

static bool cursorLocked = true;

void GameHandleInput(GameState* state)
{
    Vector3* playerPos = &state->player.position;
    if (IsKeyDown(KEY_A)) {
        state->playerPosition.x -= 1;
        playerPos->x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        state->playerPosition.x += 1;
        playerPos->x += 1;
    }
    if (IsKeyDown(KEY_W)) {
        playerPos->z -= 1;
    }
    if (IsKeyDown(KEY_S)) {
        playerPos->z += 1;
    }
    if (IsKeyDown(KEY_SPACE)) {
        camera.position.y += 0.1f;

        camera.target.y += 0.1f;
        playerPos->y += 0.1f;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {

        camera.position.y -= 0.1f;
        camera.target.y -= 0.1f;
        playerPos->y -= 0.1f;
    }
    if (IsKeyPressed(KEY_LEFT_ALT)) {
        if (cursorLocked) {
            EnableCursor();
            cursorLocked = false;
        } else {
            DisableCursor();
            cursorLocked = true;
        }
    }
}
void GameHandleUpdate(GameState* state)
{
    if (cursorLocked) {
        UpdateCamera(&state->player.camera, CAMERA_FIRST_PERSON);
    }
}
void GameHandleDraw(GameState* state)
{

    BeginMode3D(state->player.camera);
    DrawCube((Vector3) { 0.0f, 0.0f, 0.0f }, 1, 1, 1, BLUE);
    DrawGrid(10, 1);
    EndMode3D();

    DrawFPS(10, 10);
}

void GameClose(struct nk_context* ctx)
{
    UnloadNuklear(ctx);
    CloseWindow();
}
void GameDrawGUI(GameState* state, struct nk_context* ctx)
{
    UpdateNuklear(ctx);
    static bool showWindow = true;
    if (showWindow) {
        if (nk_begin(ctx, "Debug", nk_rect(0, 0, 400, GetScreenHeight()), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
            nk_layout_row_dynamic(ctx, 32, 1);
            if (nk_button_label(ctx, "Tlacitko")) {
                printf("Button was clicked\n");
            }
            Vector3 pos = state->player.position;
            char playerPosString[200];
            sprintf(playerPosString, "Player position: %5.2f,%5.2f,%5.2f", pos.x, pos.y, pos.z);
            nk_label(ctx, playerPosString, NK_TEXT_LEFT);
        } else {
            showWindow = false;
        }
        nk_end(ctx);
    }
}
void GameMainLoop(GameState* state, struct nk_context* ctx)
{
    while (!WindowShouldClose()) {
        GameHandleInput(state);
        GameHandleUpdate(state);
        // Render
        GameDrawGUI(state, ctx);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameHandleDraw(state);
        DrawNuklear(ctx);
        EndDrawing();
    }
}
void GameStart(void)
{
    GameWindow window = GameWindowInit();
    struct nk_context* ctx = InitNuklear(16);
    GameState gameState = { .playerPosition.x = 50, .playerPosition.y = 50 };
    PlayerInit(&gameState.player);
    GameMainLoop(&gameState, ctx);
}
