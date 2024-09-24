// STD
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// External
#include <raylib.h>
// Local
#include "window.h"


GameWindow GameWindowInit(void)
{
    GameWindow window;
    window.windowHeight = 720;
    window.windowWidth = 1280;
    window.windowTitle = (char*)calloc(255, sizeof(char));
    strncpy(window.windowTitle, "ProtoMedal", 254);
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
