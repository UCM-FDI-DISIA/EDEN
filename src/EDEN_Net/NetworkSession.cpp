#include "NetworkSession.h"
#include <iostream>

eden_net::NetworkSession::NetworkSession() : networkManager(new NetworkManager(NetworkMode::UDP)), isHost(false) {}

eden_net::NetworkSession::~NetworkSession() {
    closeSession();
    delete networkManager;
}

bool eden_net::NetworkSession::createSession(int maxPlayers) {
    isHost = true;
    // Inicializar la red como host aqu�
    return true;
}

bool eden_net::NetworkSession::joinSession(const std::string& hostIP, int port) {
    isHost = false;
    // Inicializar la red como guest aqu�
    return networkManager->ConnectToHost(hostIP, port);
}

void eden_net::NetworkSession::closeSession() {
    // Limpieza de la sesi�n
    networkManager->ShutdownNetwork();
}

void eden_net::NetworkSession::updateSession() {
    // Actualizar la gesti�n de la red (ej. recibir/enviar paquetes)
}
