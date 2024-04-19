// Memory Leaks Check
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

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
#include "CText.h"
#include "CButton.h"
#include "CBar.h"
#include "CCursor.h"
#include "CCamera.h"
#include "CParticleEmitter.h"
#include "CLight.h"

/// Engine Physics
#include "CRigidBody.h"
#include "CLuaBehaviour.h"

// Engine Script
#include <ScriptManager.h>
#include "SceneManager.h"
#include "Scene.h"

// Engine Audio
#include "CAudioEmitter.h"
#include "CAudioListener.h"

#include "Hito1Prueba.h"
#include "Hito2Prueba.h"
#include "Hito2MenuPausa.h"
#include "CAnimator.h"

#include "RenderManager.h"


#include <string>

void RegisterComponents() {
	// Registramos el componente Transform, que es el unico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CText>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CLight>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito2Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CLuaBehaviour>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CBar>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CParticleEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioListener>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito2MenuPausa>();
}

int main(int argc, char* argv[]) {

	//char *leak;
	//leak = new char[256];
	//strcpy_s(leak, 256, "LEAK CANARIO");

	// Memory Leaks Check
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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
		/// ----------- TESTEO REFACTORIZACION DE ESCENAS, NO BORRAR --------------------
		/*scnManager->PushScene("test_scene2");		
		scnManager->PopScene();*/
		/// ------------------------------------------------------------------------------ 
		
		scnManager->PushScene("Menu");
		//scnManager->PushScene("CrossThePathFinal");
		master->Loop();
		master->Close();
	}
#ifdef __clang__
	catch (std::runtime_error e) {
		errorHandler->HandleExceptionNWin(e);
	}
#endif
#ifdef _MSC_VER
	catch (std::exception e){
		// en caso de generar una excepci�n no tratada, se llamar� a este m�todo, que genera (en windows) un pop-up informando del error
		errorHandler->HandleException(e);
	}
#endif
	errorHandler->Close();
	return 0;
}

#endif