#define _CRTDBG_MAP_ALLOC
#include "Component.h"
#include "Entity.h"

// std::string eden_ec::Component::_id;

void eden_ec::Component::SetContext(eden_ec::Entity* ent) {
	_ent = ent;
}