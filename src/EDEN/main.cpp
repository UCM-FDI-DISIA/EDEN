#pragma once
/// Engine Loop3
#include "EdenMaster.h"

/// Entity-Component
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "TestComponent.h"
#include "Transform.h"
#include "CMeshRenderer.h"

/// Engine Render
#include <CImage.h>
#include <CCamera.h>

/// Engine Input
#include <InputManager.h>
#include <iostream>

#include "ScriptManager.h"
#include "SceneManager.h"
#include "Scene.h"

int main() {

	bool aux= eden_input::InputManager().Instance()->CloseWindowEvent();
	// Registramos el componente Transform, que es el �nico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_render::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	
	try
	{
		eden::Master* master = eden::Master::Instance();

		//Creamos una escena inicial de pueba 
		eden::SceneManager* scnManager = eden::SceneManager::Instance();
		scnManager->PushScene("test_scene");
		master->Loop();
		delete master;

	}
	catch (std::exception e){}
	
	return 0;
}