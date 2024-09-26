#include <enet/enet.h>
#include <iostream>

#include "network.hpp"

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
void NetworkConnect()
{
    client = enet_host_create(NULL, 1, 2, 0, 0);
    if (client == NULL) {
        std::cerr << "An error occurred while creating Enet client." << std::endl;
        exit(EXIT_FAILURE);
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1337;

    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL) {
        std::cerr << "No connection to the server" << std::endl;
        return;
    }
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connection to 127.0.0.1:1337 succeeded!" << std::endl;
    } else {
        enet_peer_reset(peer);
        std::cout << "Connection to 127.0.0.1:1337 failed!" << std::endl;
        return;
    }

    while (enet_host_service(client, &event, 1000) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "A new client connected from " << event.peer->address.host << " : " << event.peer->address.port << std::endl;

            /* Store any relevant client information here. */
            event.peer->data = (void*)"Client information";

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "A packet of length " << event.packet->dataLength << "containing" << event.packet->data << "was received from" << event.peer->address.host << ":" << event.peer->address.port << " %s:%s on channel " << event.channelID << std::endl;

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "disconnected." << event.peer->data << std::endl;

            /* Reset the peer's client information. */

            event.peer->data = NULL;
        }
    }
}

void NetworkSendMessage(std::string message)
{
}
