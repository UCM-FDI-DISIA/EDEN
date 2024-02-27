/// Engine Loop
#include "EdenMaster.h"

/// Entity-Component
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "TestComponent.h"
#include "Transform.h"

// Engine Render
#include <RenderManager.h>

int main() {
	eden_render::RenderManager* renderManager = eden_render::RenderManager::Instance();

	renderManager->InitManager();
	renderManager->StartRendering();


	eden::Master* master = eden::Master::Instance();
	master->Loop();
	delete master;
	auto factory = eden_ec::ComponentFactory::Instance();

	eden_ec::Entity* ent = new eden_ec::Entity();

	factory->RegisterComponent<eden_ec::cTestComponent>();
	factory->RegisterComponent<eden_ec::CTransform>();

	ent->AddComponent<eden_ec::cTestComponent>();
	ent->AddComponent<eden_ec::CTransform>();

	while (ent->IsAlive()) {
		ent->Update(0);
		ent->SetAlive(false);
	}

	renderManager->CloseManager();

	delete ent;
	return 0;
}