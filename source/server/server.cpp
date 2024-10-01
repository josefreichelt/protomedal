#include <iostream>
#include <sstream>
#include <vector>
#include <enet/enet.h>

int main(int argsCount, char* arguments[])
{
    static std::vector<ENetPeer*> peers = {};
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet." << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "ENet initialized" << std::endl;
    }

    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = 1337;

    ENetHost* server = enet_host_create(&address, 32, 2, 0, 0);

    if (server == nullptr) {
        std::cerr << "Error creating ENET server host." << std::endl;
    } else {
        std::cout << "Server successfuly created" << std::endl;
    }

    ENetEvent event;
    while (true) {
        while (enet_host_service(server, &event, 2000) > 0) {
            if (event.type == ENET_EVENT_TYPE_NONE) {
                continue;
            }
            std::string helloDate = "MSG: Hello there";
            ENetPacket* packet;
            std::ostringstream msg;
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                /* Store any relevant client information here. */
                packet = enet_packet_create(helloDate.data(), helloDate.length(), ENET_PACKET_FLAG_RELIABLE);
                event.peer->data = (void*)"Client information";
                peers.push_back(event.peer);
                enet_peer_send(event.peer, 0, packet);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Incoming packet, dataLength: "
                          << event.packet->dataLength << " data: " << event.packet->data
                          << " from: " << event.peer->address.host
                          << ":" << event.peer->address.port << " on channel: "
                          << event.channelID << std::endl;

                for (auto&& peer : peers) {
                    // if (peer->address.port != event.peer->address.port) {
                    msg.str("");
                    msg.clear();
                    msg << "MSG:" << event.packet->data;
                    packet = enet_packet_create(msg.str().data(), msg.str().length(), ENET_PACKET_FLAG_RELIABLE);
                    std::cout << "Sending msg to " << peer->address.host << ":" << peer->address.port << msg.str() << std::endl;
                    enet_peer_send(peer, 0, packet);
                    // }
                }

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);

                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "disconnected." << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                for (size_t i = 0; i < peers.size(); i++) {
                    if (peers[i]->address.host == event.peer->address.host && peers[i]->address.port == event.peer->address.port) {
                        peers.erase(peers.begin() + i);
                    }
                }
                /* Reset the peer's client information. */

                event.peer->data = nullptr;
            }
        }
    }
    enet_host_destroy(server);
    enet_deinitialize();
    return 0;
}
