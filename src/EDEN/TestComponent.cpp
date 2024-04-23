#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "TestComponent.h"

/// @brief Nueva ID
const std::string eden_ec::cTestComponent::_id = "TEST_COMPONENT";

/// @brief Update de prueba
void eden_ec::cTestComponent::update(float t) {
	// Renderiza el ID del componente y un mensaje diciendo que esta activa
	std::cout << cTestComponent::GetID() + ": is active and running!\n";
}