#include "NetworkManager.h"
#include <iostream>

eden_net::NetworkManager::NetworkManager() : _tcpSocket(nullptr), _udpSocket(nullptr), _udpPacket(nullptr) {
    SDLNet_Init();
}

eden_net::NetworkManager::~NetworkManager() {
    ShutdownNetwork();
    SDLNet_Quit();
}

void eden_net::NetworkManager::Init(NetworkMode mode) {
    _mode = mode;
}

bool eden_net::NetworkManager::InitNetwork(uint16_t port) {
    if (_mode == NetworkMode::TCP) {
        // Configuración TCP
        SDLNet_ResolveHost(&_ip, nullptr, port); // nullptr para el host indica "escuchar"
        _tcpSocket = SDLNet_TCP_Open(&_ip);
        if (!_tcpSocket) {
            std::cerr << "Error al abrir conexión TCP\n";
            return false;
        }
    }
    else if (_mode == NetworkMode::UDP) {
        // Configuración UDP
        _udpSocket = SDLNet_UDP_Open(port);
        if (!_udpSocket) {
            std::cerr << "Error al abrir conexión UDP\n";
            return false;
        }
        _udpPacket = SDLNet_AllocPacket(512); // Asumiendo un tamaño de paquete
        if (!_udpPacket) {
            std::cerr << "Error al asignar paquete UDP\n";
            return false;
        }
    }
    return true;
}

void eden_net::NetworkManager::ShutdownNetwork() {
    if (_tcpSocket) {
        SDLNet_TCP_Close(_tcpSocket);
        _tcpSocket = nullptr;
    }
    if (_udpSocket) {
        SDLNet_UDP_Close(_udpSocket);
        _udpSocket = nullptr;
        SDLNet_FreePacket(_udpPacket);
        _udpPacket = nullptr;
    }
}

void eden_net::NetworkManager::ProcessIncomingPackets() {
    if (_mode == NetworkMode::TCP) {
        // Procesamiento de paquetes TCP
    }
    else if (_mode == NetworkMode::UDP) {
        // Procesamiento de paquetes UDP
        if (SDLNet_UDP_Recv(_udpSocket, _udpPacket)) {
            // Hacer algo con _udpPacket->data
        }
    }
}

void eden_net::NetworkManager::SendPacket(const std::string& data, const IPaddress& dest) {
    if (_mode == NetworkMode::TCP) {
        // Envío de datos TCP
    }
    else if (_mode == NetworkMode::UDP) {
        // Envío de datos UDP
        memcpy(_udpPacket->data, data.data(), data.size());
        _udpPacket->len = data.size();
        _udpPacket->address = dest;
        SDLNet_UDP_Send(_udpSocket, -1, _udpPacket); // -1 significa enviar a cualquier canal
    }
}

bool eden_net::NetworkManager::ConnectToHost(const std::string& hostIP, uint16_t port) {
    if (_mode == NetworkMode::TCP) {
        IPaddress hostIPaddress;
        SDLNet_ResolveHost(&hostIPaddress, hostIP.c_str(), port);
        _tcpSocket = SDLNet_TCP_Open(&hostIPaddress);
        if (!_tcpSocket) {
            std::cerr << "Failed to connect to host: " << SDLNet_GetError() << std::endl;
            return false;
        }
    }
    else if (_mode == NetworkMode::UDP) {
        // Para UDP, configuramos el socket para enviar paquetes al host especificado
        _udpSocket = SDLNet_UDP_Open(0);  // 0 para que SDL_net elija un puerto
        if (!_udpSocket) {
            std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
            return false;
        }
        SDLNet_ResolveHost(&_ip, hostIP.c_str(), port);
        _udpPacket->address = _ip;  // Configura la dirección del paquete UDP
    }
    return true;
}