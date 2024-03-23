#ifndef EDEN_MAIN_CPP
#define EDEN_MAIN_CPP

#include <iostream>
#include <filesystem>

#include "ErrorHandler.h"

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
#include "CImage.h"
#include "CButton.h"
#include "CCursor.h"
#include "CCamera.h"

/// Engine Physics
#include "CRigidBody.h"
#include "CButtonBehaviour.h"

#include <ScriptManager.h>
#include "SceneManager.h"
#include "Scene.h"

#include "Hito1Prueba.h"
#include "CAnimator.h"

void RegisterComponents() {
	// Registramos el componente Transform, que es el unico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButtonBehaviour>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
}

int main(int argc, char* argv[]) {
	
	// Registro de componentes
	RegisterComponents();

	// Cogemos una instancia del manejador de errores
	eden_error::ErrorHandler* errorHandler = eden_error::ErrorHandler::Instance();

	// Hacemos try-catch de las excepciones generadas.
	try
	{
#ifdef __APPLE__
		std::filesystem::current_path(std::filesystem::canonical(std::string(argv[0]) + "/.."));
#endif
		eden::Master* master = eden::Master::Instance();
		//Creamos una escena inicial de pueba 
		eden::SceneManager* scnManager = eden::SceneManager::Instance();
		scnManager->PushScene("test_scene");
		master->Loop();
		delete scnManager;
		delete master;
	}
	catch (std::exception e){
		// en caso de generar una excepci�n no tratada, se llamar� a este m�todo, que genera (en windows) un pop-up informando del error
		errorHandler->HandleException(e);
	}
	
	return 0;
}

#endif