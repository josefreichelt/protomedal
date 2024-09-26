// STD
#include <iostream>
// External
#include <raylib.h>
// Local
#include "window.hpp"

GameWindow GameWindowInit()
{
    GameWindow window;
    window.windowHeight = 720;
    window.windowWidth = 1280;
    window.windowTitle = "ErPeGe";
    std::cout << "Game title is " << window.windowTitle << std::endl;

    // ------------
    // Raylib window init
    std::cout << "Initializing Raylib" << std::endl;
    InitWindow(window.windowWidth, window.windowHeight, window.windowTitle.c_str());
    SetTargetFPS(60);
    // DisableCursor();
    // ------------

    return window;
}
