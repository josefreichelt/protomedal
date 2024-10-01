#include <enet/enet.h>
#include <iostream>

#include "network.hpp"
#include "chat.hpp"

static ENetHost* client;
static ENetAddress address;
static ENetEvent event;
static ENetPeer* peer;

void NetworkInit()
{
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "ENet initialized" << std::endl;
    }
}

void NetworkCheckServer(int timeout)
{
    if (client == nullptr)
        return;
    // static int pingCount = 0;
    // std::cout << "Pinging" << pingCount++ << std::endl;
    while (enet_host_service(client, &event, timeout) > 0) {
        std::string msg;
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "A new client connected from " << event.peer->address.host << " : " << event.peer->address.port << std::endl;

            /* Store any relevant client information here. */
            event.peer->data = (void*)"Client information";

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "Incoming packet, dataLength: "
                      << event.packet->dataLength << " data: " << event.packet->data
                      << " from: " << event.peer->address.host
                      << ":" << event.peer->address.port << " on channel: "
                      << event.channelID << std::endl;

            msg = std::string { reinterpret_cast<char*>(event.packet->data), event.packet->dataLength };
            if (msg.rfind("MSG", 0) == 0) {
                ChatAddMessage(msg);
            }
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "disconnected." << event.peer->address.host << ":" << event.peer->address.port << std::endl;

            /* Reset the peer's client information. */

            event.peer->data = nullptr;
        }
    }
}

void NetworkConnect()
{
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (client == nullptr) {
        std::cerr << "An error occurred while creating Enet client." << std::endl;
        exit(EXIT_FAILURE);
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1337;

    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == nullptr) {
        std::cerr << "No connection to the server" << std::endl;
        return;
    }
    if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connection to 127.0.0.1:1337 succeeded!" << std::endl;
    } else {
        enet_peer_reset(peer);
        std::cout << "Connection to 127.0.0.1:1337 failed!" << std::endl;
        return;
    }
    NetworkCheckServer(1000);
}

void SendPacket(ENetPeer* peer, std::string data)
{
    ENetPacket* packet = enet_packet_create(data.data(), data.length(), ENET_PACKET_FLAG_RELIABLE);
    if (enet_peer_send(peer, 0, packet) == 0) {
        std::cout << "Message sent succesfully" << std::endl;
    };
}

void NetworkSendMessage(std::string message)
{
    if (peer != nullptr) {
        std::cout << "Sending msg" << message << std::endl;
        SendPacket(peer, message);
    }
}
