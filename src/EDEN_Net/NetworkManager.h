#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <SDL_net.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"

enum class NetworkMode {
    TCP,
    UDP
};

namespace eden_net {
    class NetworkManager : public Singleton<NetworkManager> {
        friend Singleton<NetworkManager>;
    public:
        EDEN_API void Init(NetworkMode mode);
        EDEN_API bool InitNetwork(uint16_t port);
        EDEN_API void ShutdownNetwork();
        EDEN_API void ProcessIncomingPackets();
        EDEN_API void SendPacket(const std::string& data, const IPaddress& dest);
        EDEN_API bool ConnectToHost(const std::string& hostIP, uint16_t port);

        ~NetworkManager() override;
    private:
        NetworkManager();

        NetworkMode _mode;
        IPaddress _ip;
        TCPsocket _tcpSocket;
        UDPsocket _udpSocket;
        UDPpacket* _udpPacket;
    };
}

#endif // NETWORK_MANAGER_H_