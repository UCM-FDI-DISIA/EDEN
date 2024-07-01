#include "NetworkSession.h"
#include <iostream>

eden_net::NetworkSession::NetworkSession() : networkManager(eden_net::NetworkManager::Instance()), isHost(false) {
    networkManager->Init(NetworkMode::UDP);
}

eden_net::NetworkSession::~NetworkSession() {
    closeSession();
    delete networkManager;
}

bool eden_net::NetworkSession::createSession(int maxPlayers) {
    isHost = true;
    // Inicializar la red como host aquí
    return true;
}

bool eden_net::NetworkSession::joinSession(const std::string& hostIP, int port) {
    isHost = false;
    // Inicializar la red como guest aquí
    return networkManager->ConnectToHost(hostIP, port);
}

void eden_net::NetworkSession::closeSession() {
    // Limpieza de la sesión
    networkManager->ShutdownNetwork();
}

void eden_net::NetworkSession::updateSession() {
    // Actualizar la gestión de la red (ej. recibir/enviar paquetes)
}
