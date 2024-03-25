#define _CRTDBG_MAP_ALLOC
#include "Component.h"
#include "Entity.h"

const std::string eden_ec::Component::_id = "DEFAULT_ID_SHOULD_CHANGE";

void eden_ec::Component::SetContext(eden_ec::Entity* ent) {
	_ent = ent;
}