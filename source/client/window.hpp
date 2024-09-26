#pragma once
#include <string>

struct GameWindow {
    int windowWidth;
    int windowHeight;
    std::string  windowTitle;
};

GameWindow GameWindowInit();
