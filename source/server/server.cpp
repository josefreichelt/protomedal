#include <enet/enet.h>
#include <iostream>

int main(int argsCount, char* arguments[])
{
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet." << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "ENet initialized" << std::endl;
    }

    ENetAddress address;
    ENetHost* server;

    address.host = ENET_HOST_ANY;
    address.port = 1337;

    server = enet_host_create(&address, 32, 2, 0, 0);

    if (server == NULL) {
        std::cerr << "Error creating ENET server host." << std::endl;
    } else {
        std::cout << "Server successfuly created" << std::endl;
    }

    ENetEvent event;
    while (enet_host_service(server, &event, 1000) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "A new client connected from" << event.peer->address.host << ":" << event.peer->address.port << std::endl;

            /* Store any relevant client information here. */
            event.peer->data = (void*)"Client information";

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "A packet of length containing %s was received from %s:%s on channel"
                      << event.packet->dataLength
                      << event.packet->data
                      << event.peer->address.host
                      << event.peer->address.port
                      << event.channelID << std::endl;

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "disconnected: " <<  event.peer->data << std::endl;

            /* Reset the peer's client information. */

            event.peer->data = NULL;
        }
    }
    enet_host_destroy(server);
    enet_deinitialize();
    return 0;
}
