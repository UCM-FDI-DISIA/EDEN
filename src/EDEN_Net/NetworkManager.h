#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <SDL_net.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"

const int NUM_SOCKETS = 4;

namespace eden_net {
    class NetworkManager : public Singleton<NetworkManager> {
        friend Singleton<NetworkManager>;
    public:
        EDEN_API bool InitNetwork(uint16_t port, const std::string& hostIP);
        EDEN_API TCPsocket GetSocket(int _type);
        EDEN_API SDLNet_SocketSet GetSocketSet();
        EDEN_API void ShutdownNetwork();

        EDEN_API ~NetworkManager() override;
    private:
        EDEN_API NetworkManager();

        IPaddress _ip;
        TCPsocket _masterSocket;

        SDLNet_SocketSet _socketSet;
        TCPsocket _socket[NUM_SOCKETS];

        bool host;
        bool active = false;
    };
}

#endif // NETWORK_MANAGER_H_