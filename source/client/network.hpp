#pragma once
#include <string>
void NetworkInit();
void NetworkSendMessage(std::string message);
void NetworkConnect();
void NetworkCheckServer(int timeout = 0);
