// STD
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// External
#include <raylib.h>
#include <enet/enet.h>
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"
// Local
#include "game.h"
#include "player.h"
#include "window.h"

typedef struct {
    Vector2 playerPosition;
    Player player;
} GameState;

static bool cursorLocked = true;

void GameHandleInput(GameState* state)
{

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
    float delta = GetFrameTime();
    if (cursorLocked) {
        /* UpdateCamera(&state->player.camera, CAMERA_FIRST_PERSON); */
        PlayerUpdate(&state->player,delta);
    }
}
void GameHandleDraw(GameState* state)
{

    BeginMode3D(state->player.camera);
    DrawGrid(1000, 1);
    DrawCube((Vector3) { 0.0f, -0.1f, 0.0f }, 10, 0.1, 10, (Color){140,230,140,255});
    PlayerDraw(&state->player);
    EndMode3D();

    DrawFPS(10, 10);
}

void GameClose(struct nk_context* ctx)
{
    UnloadNuklear(ctx);
    CloseWindow();
    enet_deinitialize();
}
void GameDrawGUI(GameState* state, struct nk_context* ctx)
{
    UpdateNuklear(ctx);
    static bool showWindow = true;
    if (showWindow) {
        if (nk_begin(ctx, "Debug", nk_rect(0, 0, 200, GetScreenHeight()), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
            nk_layout_row_dynamic(ctx, 32, 1);
            if (nk_button_label(ctx, "Tlacitko")) {
                printf("Button was clicked\n");
            }
            PlayerDebugGUI(&state->player, ctx);
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
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        exit(EXIT_FAILURE);
    }else {
        printf("ENet initialized\n");
    }
    GameWindow window = GameWindowInit();
    struct nk_context* ctx = InitNuklear(12);
    GameState gameState = { .playerPosition.x = 50, .playerPosition.y = 50 };
    PlayerInit(&gameState.player);
    GameMainLoop(&gameState, ctx);
    GameClose(ctx);
}
