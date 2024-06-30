#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <SDL_net.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"
#include "defs.h"

enum class NetworkMode {
    TCP,
    UDP
};

namespace eden_net {
    class NetworkManager : public Singleton<NetworkManager> {
        friend Singleton<NetworkManager>;
    public:
        bool InitNetwork(uint16_t port);
        void ShutdownNetwork();
        void ProcessIncomingPackets();
        void SendPacket(const std::string& data, const IPaddress& dest);
        bool ConnectToHost(const std::string& hostIP, uint16_t port);

        ~NetworkManager() override;
    private:
        NetworkManager(NetworkMode mode);

        NetworkMode _mode;
        IPaddress _ip;
        TCPsocket _tcpSocket;
        UDPsocket _udpSocket;
        UDPpacket* _udpPacket;
    };
}

#endif // NETWORK_MANAGER_H_