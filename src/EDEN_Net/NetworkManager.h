#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <SDL_net.h>
#include <string>
#include <memory>
#include <unordered_map>

class Entity;

enum class NetworkMode {
    TCP,
    UDP
};

namespace eden_net {
    class NetworkManager {
    public:
        NetworkManager(NetworkMode mode);
        ~NetworkManager();

        bool initNetwork(uint16_t port);
        void shutdownNetwork();
        void processIncomingPackets();
        void sendPacket(const std::string& data, const IPaddress& dest);

    private:
        NetworkMode mode;
        IPaddress ip;
        TCPsocket tcpSocket;
        UDPsocket udpSocket;
        UDPpacket* udpPacket;
    };
}

#endif // NETWORK_MANAGER_H_