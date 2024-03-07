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
#include <RenderManager.h>
#include <CImage.h>

/// Engine Input
#include <iostream>

#include "ScriptManager.h"
#include "SceneManager.h"
#include "Scene.h"

int main() {
	// Registramos el componente Transform, que es el �nico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	
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