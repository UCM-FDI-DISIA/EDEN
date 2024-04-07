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
#include <CButton.h>
#include <CCursor.h>
#include <CCamera.h>

/// Engine Physics
#include "CRigidBody.h"


#include <iostream>

#include "ScriptManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Hito1Prueba.h"
#include "CAnimator.h"

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

int main() {

	// Registramos el componente Transform, que es el unico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_render::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();




#ifdef _DEBUG
	HMODULE game = LoadLibraryA("game_d.dll");
#else
	HMODULE game = LoadLibraryA("game.dll");
#endif
	if (game == NULL) { // mejor con assert
		std::cerr << "no se ha cargado la dll correctamente" << std::endl;
	}

	else {
		typedef void (*SceneFunc)();
		// SaludoFunc saludo = (SaludoFunc)(GetProcAddress(game, "saludo"));
		SceneFunc loadScene = reinterpret_cast<SceneFunc>(GetProcAddress(game, "saludo"));

		if (loadScene == NULL) {
			std::cerr << "no existe el metodo saludo de la dll" << std::endl;
		}

		else {
			try
			{
				eden::Master* master = eden::Master::Instance();
				//Creamos una escena inicial de pueba 
				loadScene();
				master->Loop();
				delete master;
			}

			catch (std::exception e) {}
		}

		FreeLibrary(game);
	}
	
	return 0;
}