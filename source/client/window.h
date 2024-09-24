#pragma once

typedef struct {
    int windowWidth;
    int windowHeight;
    char* windowTitle;
} GameWindow;

GameWindow GameWindowInit(void);
