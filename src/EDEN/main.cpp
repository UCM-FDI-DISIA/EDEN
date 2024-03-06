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
///
//#include <UI/Image.h>
//#include <UI/Texture.h>

/// Engine Input
#include <iostream>

#include "ScriptManager.h"
#include "SceneManager.h"
#include "Scene.h"

int main() {
	// Registramos el componente Transform, que es el único que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();

	//Creamos una escena inicial de pueba 
	eden::SceneManager* scnManager = eden::SceneManager::Instance();
	scnManager->PushScene("test_scene");
	
	eden::Master* master = eden::Master::Instance();
	master->Loop();
	delete master;
	
	return 0;
}