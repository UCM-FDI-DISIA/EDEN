#include "Component.h"
#include "Entity.h"

// Definición de ID para el componente. Como se indica en el .h, esta ID
// debe ser cambiada en cada nueva clase de tipo Componente
const std::string eden_ec::Component::_id = "DEFAULT_ID_SHOULD_CHANGE";

std::string eden_ec::Component::GetID() { return _id; }

void eden_ec::Component::SetContext(eden_ec::Entity* ent) {
	_ent = ent;
}