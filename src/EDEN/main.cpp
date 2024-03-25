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

#include <windows.h>


int main() {

#ifdef _DEBUG
	HMODULE game = LoadLibraryA("game_d.dll");
#else
	HMODULE game = LoadLibraryA("game.dll");
#endif
	if (game == NULL) {
		std::cerr << "no se ha cargado la dll correctamente" << std::endl;
	}

	else {
		typedef std::string (*SaludoFunc)();
		// SaludoFunc saludo = (SaludoFunc)(GetProcAddress(game, "saludo"));
		SaludoFunc saludo = reinterpret_cast<SaludoFunc>(GetProcAddress(game, "saludo"));

		if (saludo == NULL) {
			std::cerr << "no existe el metodo saludo de la dll" << std::endl;
		}

		else {
			std::cout << saludo() << std::endl;

			//// Registramos el componente Transform, que es el unico que usaremos de momento
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_render::CCamera>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
			//eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();

			//try {
			//	eden::Master* master = eden::Master::Instance();
			//	//Creamos una escena inicial de pueba 
			//	eden::SceneManager* scnManager = eden::SceneManager::Instance();
			//	scnManager->PushScene("test_scene");
			//	master->Loop();
			//	delete scnManager;
			//	delete master;
			//}

			//catch (std::exception e) {

			//}
		}

		FreeLibrary(game);
	}
	
	return 0;
}