#pragma once
#include <string>
#include <functional>

using ChatMessageSentCallback = std::function<void(std::string)>;

void ChatInit();
void ChatRender(bool* isFocused, ChatMessageSentCallback callback);
void ChatAddMessage(std::string msg);
