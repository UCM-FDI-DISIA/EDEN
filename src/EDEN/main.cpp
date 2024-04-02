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

#ifdef _DEBUG
	HMODULE game = LoadLibraryA("game_d.dll");
#else
	HMODULE game = LoadLibraryA("game.dll");
#endif
	if (game == NULL) { // mejor con assert
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
		}

		FreeLibrary(game);
	}
	
	return 0;
}