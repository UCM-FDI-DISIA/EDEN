/// Engine Loop
#include "EdenMaster.h"

/// Entity-Component
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "TestComponent.h"
#include "Transform.h"

int main() {
	eden::Master* master = eden::Master::Instance();
	master->Loop();
	delete master;
	auto factory = eden_ec::ComponentFactory::Instance();

	eden_ec::Entity* ent = new eden_ec::Entity();

	factory->RegisterComponent<eden_ec::cTestComponent>();
	factory->RegisterComponent<eden_ec::Transform>();

	ent->addComponent<eden_ec::cTestComponent>();
	ent->addComponent<eden_ec::Transform>();

	while (ent->IsAlive()) {
		ent->update(0);
		ent->SetAlive(false);
	}
	delete ent;
	return 0;
}