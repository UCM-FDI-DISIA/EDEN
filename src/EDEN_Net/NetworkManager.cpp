#include "NetworkManager.h"
#include <iostream>

eden_net::NetworkManager::NetworkManager() : _masterSocket(nullptr) {
    SDLNet_Init();
}

eden_net::NetworkManager::~NetworkManager() {
    ShutdownNetwork();
    SDLNet_Quit();
}

bool eden_net::NetworkManager::InitNetwork(uint16_t port, const std::string& hostIP = "") {
    char buffer[256];

    if (hostIP.empty()) { // Actúa como servidor
        host = true;
        SDLNet_ResolveHost(&_ip, nullptr, port);
        _masterSocket = SDLNet_TCP_Open(&_ip);
        if (!_masterSocket) {
            std::cerr << "Error al abrir socket-servidor TCP: " << SDLNet_GetError() << std::endl;
            return false;
        }
        _socketSet = SDLNet_AllocSocketSet(NUM_SOCKETS + 1);
        SDLNet_TCP_AddSocket(_socketSet, _masterSocket);
        for (int i = 0; i < NUM_SOCKETS; ++i) { _socket[i] = nullptr; }
        std::cout << "Esperando al otro jugador..." << std::endl;
        while (_socket[NUM_SOCKETS - 1] == nullptr) {
            if (SDLNet_CheckSockets(_socketSet, SDL_MAX_UINT32) > 0) {
                TCPsocket client = SDLNet_TCP_Accept(_masterSocket);
                int j = 0;
                while (j < NUM_SOCKETS && _socket[j] != nullptr) ++j;
                if (j < NUM_SOCKETS) {
                    _socket[j] = client;
                    SDLNet_TCP_AddSocket(_socketSet, client);
                    buffer[0] = 0;
                    SDLNet_TCP_Send(client, buffer, 1);
                }
                else {
                    buffer[0] = 1;
                    SDLNet_TCP_Send(client, buffer, 1);
                    SDLNet_TCP_Close(client);
                }
            }
        }
    }
    else { // Actúa como cliente
        bool done;
        host = false;

        _socketSet = SDLNet_AllocSocketSet(NUM_SOCKETS);

        if (SDLNet_ResolveHost(&_ip, hostIP.c_str(), port) < 0) { std::cout << "error\n"; }
        TCPsocket conn = SDLNet_TCP_Open(&_ip);
        if (!conn) { std::cout << "error\n"; }

        // TODO I: WAIT FOR CONFIRMATION MESSAGE
        int result = SDLNet_TCP_Recv(conn, buffer, 1);
        if (result < 0) {
            std::cout << "error\n";
        }
        else if (result == 0) {
            std::cout << "El servidor ha cerrado la conexión..." << std::endl;
        }
        else {
            if (buffer[0] == 0) {
                std::cout << "¡Conectado!" << std::endl;
                _socket[USERNAME] = conn;
                done = false;
            }
            else {
                std::cout << "¡Conexión rechazada!" << std::endl;
                done = true;
            }
        }

        for (int i = 1; i < NUM_SOCKETS; ++i) {
            _socket[i] = SDLNet_TCP_Open(&_ip);
            SDLNet_TCP_AddSocket(_socketSet, _socket[i]);
        }
    }

    active = true;

    return true;
}

void eden_net::NetworkManager::Update()
{
    char buffer[256];

    if (active && SDLNet_CheckSockets(_socketSet, SDL_MAX_UINT32) > 0) {
        int result = 0;
        // TODO II: PROCESS DATA on client sockets
        for (int i = 0; i < NUM_SOCKETS; i++) {
            if (_socket[i] != nullptr && SDLNet_SocketReady(_socket[i])) {
                result = SDLNet_TCP_Recv(_socket[i], buffer, 255);
                if (result <= 0) {
                    SDLNet_TCP_Close(_socket[i]);
                    SDLNet_TCP_DelSocket(_socketSet, _socket[i]);
                    _socket[i] = nullptr;
                }
            }
        }
    }
}

void eden_net::NetworkManager::ShutdownNetwork() {
    if (active) {
        if (host) {
            SDLNet_TCP_Close(_masterSocket);
            SDLNet_TCP_DelSocket(_socketSet, _masterSocket);
            _masterSocket = nullptr;
        }

        for (int i = 0; i < NUM_SOCKETS; ++i) {
            SDLNet_TCP_Close(_socket[i]);
            SDLNet_TCP_DelSocket(_socketSet, _socket[i]);
            _socket[i] = nullptr;
        }
    }
}