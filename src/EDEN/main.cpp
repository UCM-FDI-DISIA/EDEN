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
#include <CImage.h>

/// Engine Input
#include <InputManager.h>
#include <iostream>

int main() {
	eden_render::RenderManager* renderManager = eden_render::RenderManager::Instance();

	renderManager->InitManager("EDEN Engine"); // sustituir por nombre del juego a arrancar
	eden_input::InputManager* inputManager = eden_input::InputManager::Instance();

	eden::Master* master = eden::Master::Instance();
	// master->Loop();
	delete master;
	auto factory = eden_ec::ComponentFactory::Instance();

	eden_ec::Entity* ent = new eden_ec::Entity();

	factory->RegisterComponent<eden_ec::cTestComponent>();
	factory->RegisterComponent<eden_ec::CTransform>();
	factory->RegisterComponent<eden_ec::CImage>();

	ent->AddComponent<eden_ec::cTestComponent>();
	ent->AddComponent<eden_ec::CTransform>();
	std::string aux = "C:/Users/juanf/Desktop/Proyectos3/EDEN/bin/assets/imagen.png";
	//ent->AddComponent<eden_ec::CImage>("image",0,0,50,50,aux,0);

	while (ent->IsAlive() && !inputManager->IsKeyDown(inputManager->SPACE) && !inputManager->CloseWindowEvent()) {
		ent->Update(0);
		renderManager->Update();
		inputManager->Update();
	}
	renderManager->CloseWindow();
	ent->SetAlive(false);


	renderManager->CloseManager();
	inputManager->~InputManager();
	delete ent;
	return 0;
}