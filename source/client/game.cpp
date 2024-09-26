// STD
#include <iostream>
#include <string>
// External
#include <raylib.h>
#include <enet/enet.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
// Local
#include "game.hpp"
#include "player.hpp"
#include "window.hpp"
#include "network.hpp"

struct GameState {
    Vector2 playerPosition;
    Player player;
};

static bool cursorLocked = true;

void GameHandleInput(GameState& state)
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
void GameHandleUpdate(GameState& state)
{
    float delta = GetFrameTime();
    if (cursorLocked) {
        /* UpdateCamera(&state->player.camera, CAMERA_FIRST_PERSON); */
        PlayerUpdate(state.player, delta);
    }
}
void GameHandleDraw(GameState& state)
{

    BeginMode3D(state.player.camera);
    DrawGrid(1000, 1);
    DrawCube((Vector3) { 0.0f, -0.1f, 0.0f }, 10, 0.1, 10, (Color) { 140, 230, 140, 255 });
    PlayerDraw(state.player);
    EndMode3D();

    DrawFPS(GetScreenWidth() - 30, 10);
}

void GameClose()
{
    CloseWindow();
    enet_deinitialize();
}

void GameDrawGUI(GameState& state)
{
    static bool showWindow = true;
    if (showWindow) {
        if (GuiButton(Rectangle { 0, 0, 100, 30 }, "Connect")) {
            //         NetworkConnect();
            std::cout << "Button click" << std::endl;
        }
        // if (nk_begin(ctx, "Debug", nk_rect(0, 0, 200, GetScreenHeight()), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
        //     nk_layout_row_dynamic(ctx, 32, 1);
        //     if (nk_button_label(ctx, "Tlacitko")) {
        //         printf("Button was clicked%s\n",editstringa);
        //     }
        //     PlayerDebugGUI(&state->player, ctx);
        //     if(nk_button_label(ctx,"Connect")){
        //     }
        //     nk_layout_row_static(ctx,30,100,2);
        //     nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, editstringa, 255, nk_filter_default);
        //     if(nk_button_label(ctx,">")){
        //         printf("Chat: %s\n",editstringa);
        //         NetworkSendMessage(editstringa);
        //     }
        // } else {
        //     showWindow = false;
        // }
        // nk_end(ctx);
    }
}
void GameMainLoop(GameState& state)
{
    while (!WindowShouldClose()) {
        GameHandleInput(state);
        GameHandleUpdate(state);
        // Render
        GameDrawGUI(state);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameHandleDraw(state);
        EndDrawing();
    }
}
void GameStart(void)
{
    NetworkInit();
    GameWindow window = GameWindowInit();
    GameState gameState;
    gameState.playerPosition.x = 50;
    gameState.playerPosition.y = 50;
    PlayerInit(gameState.player);
    GameMainLoop(gameState);
    GameClose();
}
