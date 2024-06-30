#include "NetworkManager.h"
#include <iostream>

eden_net::NetworkManager::NetworkManager(NetworkMode mode) : mode(mode), tcpSocket(nullptr), udpSocket(nullptr), udpPacket(nullptr) {
    SDLNet_Init();
}

eden_net::NetworkManager::~NetworkManager() {
    shutdownNetwork();
    SDLNet_Quit();
}

bool eden_net::NetworkManager::initNetwork(uint16_t port) {
    if (mode == NetworkMode::TCP) {
        // Configuración TCP
        SDLNet_ResolveHost(&ip, nullptr, port); // nullptr para el host indica "escuchar"
        tcpSocket = SDLNet_TCP_Open(&ip);
        if (!tcpSocket) {
            std::cerr << "Error al abrir conexión TCP\n";
            return false;
        }
    }
    else if (mode == NetworkMode::UDP) {
        // Configuración UDP
        udpSocket = SDLNet_UDP_Open(port);
        if (!udpSocket) {
            std::cerr << "Error al abrir conexión UDP\n";
            return false;
        }
        udpPacket = SDLNet_AllocPacket(512); // Asumiendo un tamaño de paquete
        if (!udpPacket) {
            std::cerr << "Error al asignar paquete UDP\n";
            return false;
        }
    }
    return true;
}

void eden_net::NetworkManager::shutdownNetwork() {
    if (tcpSocket) {
        SDLNet_TCP_Close(tcpSocket);
        tcpSocket = nullptr;
    }
    if (udpSocket) {
        SDLNet_UDP_Close(udpSocket);
        udpSocket = nullptr;
        SDLNet_FreePacket(udpPacket);
        udpPacket = nullptr;
    }
}

void eden_net::NetworkManager::processIncomingPackets() {
    if (mode == NetworkMode::TCP) {
        // Procesamiento de paquetes TCP
    }
    else if (mode == NetworkMode::UDP) {
        // Procesamiento de paquetes UDP
        if (SDLNet_UDP_Recv(udpSocket, udpPacket)) {
            // Hacer algo con udpPacket->data
        }
    }
}

void eden_net::NetworkManager::sendPacket(const std::string& data, const IPaddress& dest) {
    if (mode == NetworkMode::TCP) {
        // Envío de datos TCP
    }
    else if (mode == NetworkMode::UDP) {
        // Envío de datos UDP
        memcpy(udpPacket->data, data.data(), data.size());
        udpPacket->len = data.size();
        udpPacket->address = dest;
        SDLNet_UDP_Send(udpSocket, -1, udpPacket); // -1 significa enviar a cualquier canal
    }
}
