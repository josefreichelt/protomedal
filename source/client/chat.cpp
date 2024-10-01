// STD
#include <vector>
#include <string>
#include <iostream>
// External
#include <raylib.h>
#include <raygui.h>
// Local
#include "chat.hpp"

static std::vector<std::string> messages = {};

void ChatInit()
{
    messages.clear();
    messages.push_back("Zpráva 1");
    messages.push_back("Zpráva 2");
    messages.push_back("Zpráva 3");
    messages.push_back("Zpráva 4");
    messages.push_back("Zpráva 5");
    messages.push_back("Zpráva 6");
}

void ChatRender(bool* isFocused, ChatMessageSentCallback onSendMessage)
{
    static Rectangle chatWindowRect = { 10, 100, 300, 200 };
    static Rectangle panelContentRec = { 0, 0, chatWindowRect.width - 15, 340 };
    static Rectangle panelView = { 0 };
    static Vector2 panelScroll = { 0, 0 };
    static std::string msg(256, '\0');
    GuiScrollPanel(chatWindowRect, "CHAT", panelContentRec, &panelScroll, &panelView);

    // Content
    BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);
    int xOffset = panelView.x + panelScroll.x;
    int yOffset = panelView.y + panelScroll.y;
    for (auto&& message : messages) {
        GuiLabel({ static_cast<float>(xOffset), static_cast<float>(yOffset), panelView.width, 12 }, message.c_str());
        yOffset += 12;
    }
    EndScissorMode();
    if (GuiTextBox({ panelView.x, panelView.y + panelView.height, 250, 20 }, msg.data(), 255, *isFocused)) {
        *isFocused = !(*isFocused);
    }
    if (GuiButton(Rectangle { panelView.x + 250, panelView.y + panelView.height, 50, 20 }, "Send")) {
        if (msg[0] != '\0') {
            onSendMessage(msg);
            msg.assign(255, '\0');
        }
    }
}

void ChatAddMessage(std::string msg)
{
    messages.push_back(msg);
}
