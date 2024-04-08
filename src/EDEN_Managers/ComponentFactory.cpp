#define _CRTDBG_MAP_ALLOC
#include "ComponentFactory.h"
#include "Component.h"

bool eden_ec::ComponentFactory::ComponentExists(std::string id) {
	return _currentComponents.count(id);
}
eden_ec::Component* eden_ec::ComponentFactory::CreateComponentByName(std::string id) {
	auto it = _currentComponents.find(id);
	if (it == _currentComponents.end()) return nullptr;

	// Crea el componente a partir de la función guardada en el mapa _currentComponents
	Component* c = it->second();

	return c;
}