// STD
#include <iostream>
#include <sstream>
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
#include "chat.hpp"

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
static bool writingText { false };
static bool writingUserName { false };
const float NETWORK_PING_TIME = 150; // ms
static float pingTime = 0.0f;
static GameWindow window;
void GameHandleUpdate(GameState& state)
{
    float delta = GetFrameTime();
    std::ostringstream title;
    title << window.windowTitle << " - " << delta;
    SetWindowTitle(title.str().c_str());
    pingTime += delta * 1000;
    if (!writingText) {
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
    static std::string username(64, '\0');
    if (showWindow) {
        if (GuiButton(Rectangle { 0, 0, 100, 30 }, "Connect")) {
            NetworkConnect();
            std::cout << "Button click" << std::endl;
        }
        PlayerDebugGUI(state.player);

        if (GuiTextBox({ 10, 40, 100, 20 }, username.data(), 64, writingUserName)) {
            writingUserName = !writingUserName;
        }
        ChatRender(&writingText, [](std::string msg) -> void {
            std::cout << "Msg: " << "[" << "]: " << msg << std::endl;
            NetworkSendMessage(msg);
        });
        // if (nk_begin(ctx, "Debug", nk_rect(0, 0, 200, GetScreenHeight()), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
        //     nk_layout_row_dynamic(ctx, 32, 1);
        //     if (nk_button_label(ctx, "Tlacitko")) {
        //         printf("Button was clicked%s\n",editstringa);
        //     }
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
        if (pingTime > NETWORK_PING_TIME) {
            pingTime = 0;

            NetworkCheckServer();
        }
        // Render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameHandleDraw(state);
        GameDrawGUI(state);
        EndDrawing();
    }
}
void GameStart(void)
{
    NetworkInit();
    window = GameWindowInit();
    GameState gameState;
    gameState.playerPosition.x = 50;
    gameState.playerPosition.y = 50;
    PlayerInit(gameState.player);
    ChatInit();
    GameMainLoop(gameState);
    GameClose();
}
