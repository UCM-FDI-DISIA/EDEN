#ifndef NETWORK_SESSION_H_
#define NETWORK_SESSION_H_

#include <string>
#include <vector>
#include "NetworkManager.h"

namespace eden_net {
    class NetworkSession {
    public:
        NetworkSession();
        ~NetworkSession();

        bool createSession(int maxPlayers);
        bool joinSession(const std::string& hostIP, int port);
        void closeSession();
        void updateSession();  // Manejar la recepci�n de datos y mantener la sesi�n activa

        // Getters y setters si son necesarios
    private:
        NetworkManager* networkManager;
        std::string sessionID;
        std::vector<std::string> participants;
        bool isHost;
    };
}

#endif // NETWORK_SESSION_H_