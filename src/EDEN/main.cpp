/// Engine Loop3
#include "EdenMaster.h"

/// Entity-Component
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "TestComponent.h"
#include "Transform.h"

/// Engine Render
#include <RenderManager.h>

/// Engine Input
#include <InputManager.h>
#include <iostream>

int main() {
	eden_render::RenderManager* renderManager = eden_render::RenderManager::Instance();

	renderManager->InitManager("EDEN Engine"); // sustituir por nombre del juego a arrancar
	while (true) {
		renderManager->Update();
	}
	
	// eden_input::InputManager* inputManager = eden_input::InputManager::Instance();


	eden::Master* master = eden::Master::Instance();
	// master->Loop();
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

	/*while (!inputManager->isKeyDown(inputManager->SPACE))
	{
		inputManager->update();
		std::cout << "he";
	}*/
	
	renderManager->CloseManager();
	// inputManager->Clean();
	// delete inputManager;
	
	delete ent;
	return 0;
}