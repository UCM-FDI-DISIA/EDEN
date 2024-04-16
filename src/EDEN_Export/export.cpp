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


#include <iostream>
#include <filesystem>

#include "ErrorHandler.h"

#include "InputManager.h"

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
#include "CAnimator.h"

#include "RenderManager.h"

#include <string>
#include "Export.h"

void RegisterEngineComponents() {
	// Registramos el componente Transform, que es el unico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CText>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CLight>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CLuaBehaviour>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CParticleEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioListener>();
}

void eden_export::RunEDEN()
{

	// Cogemos una instancia del manejador de errores
	errorHandler = eden_error::ErrorHandler::Instance();

	// Hacemos try-catch de las excepciones generadas.
	try
	{
#ifdef __APPLE__
		std::filesystem::current_path(std::filesystem::canonical(std::string(argv[0]) + "/.."));
#endif
		master = eden::Master::Instance();
		//Creamos una escena inicial de pueba 
		// scnManager = eden::SceneManager::Instance();
#ifdef _DEBUG
		game = LoadLibraryA("game_d.dll");
#else
		game = LoadLibraryA("game.dll");
#endif

		if (game == NULL) {
			throw std::domain_error("aqui no hay dll");
		}
		else {
			typedef void (*CompFunc)(eden_ec::ComponentFactory*);
			CompFunc RegisterGameComponents = reinterpret_cast<CompFunc>(GetProcAddress(game, "RegisterComponents"));

			typedef void (*SceneFunc)(eden::SceneManager*);
			SceneFunc LoadScene = reinterpret_cast<SceneFunc>(GetProcAddress(game, "LoadScene"));

			if (LoadScene == NULL) {
				throw std::domain_error("no existe la funcion de carga de escena");
			}

			else if (RegisterGameComponents == NULL) {
				throw std::domain_error("no existe la funcion de registro de componentes");
			}

			else {
				// Registro de componentes
				RegisterEngineComponents();
				eden_ec::ComponentFactory* factory = eden_ec::ComponentFactory::Instance();
				RegisterGameComponents(factory);

				master = eden::Master::Instance(); // creación instancia master
				scnManager = eden::SceneManager::Instance(); // creación instancia de gestor de escenas
				eden_input::InputManager::Instance();
				LoadScene(scnManager); // carga de escena del juego
				master->Loop(); // bucle de juego
			}
		}
	}

	catch (std::exception e) {
		errorHandler->HandleException(e);
	}
}

void eden_export::StopEDEN()
{
	master->Close();
	FreeLibrary(game); // liberación de memoria de la .dll del juego
	errorHandler->Close();
}
