#pragma once

#include <iostream>

#include <lua.hpp>

#include "Component.cpp"
#include "ComponentFactory.cpp"
#include "Entity.cpp"
#include "TestComponent.h"
#include "Transform.cpp"
#include "Vector3.cpp"
#include "Quaternion.cpp"

#include "ScriptManager.h"
#include "ComponentArguments.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "EdenMaster.h"
#include "SceneManager.h"
#include "Scene.h"

int main() {

	// Cogemos el scriptManager
	eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();

	// Informaci�n que se rellenar� al leer la escena
	std::vector<eden_script::EntityInfo*> info;

	// Leemos una escena
	scriptManager->ReadScene("test_scene", info);

	// Registramos el componente Transform, que es el �nico que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	std::vector<eden_ec::Entity*> entities;

	//Creamos una escena inicial de pueba 
	SceneManager* scnManager = new SceneManager();
	Scene* testScene = scnManager->PushScene("testScene");

	// Recorremos la informaci�n recibida 
	for (auto it : info) {
		// Decimos qu� estamos leyendo por consola
		std::cout << "\n\nEntity: " << it->name << '\n';
		std::cout << "Components:\n--------\n";

		// Cremoas una nueva entidad seg�n el nombre que hayamos recibido en 'info' al leer el .lua
		auto ent = new eden_ec::Entity(it->name);
		entities.push_back(ent);
		testScene->AddGameObject(it->name, ent);

		// Creamos sus componentes seg�n la info le�da
		ent->AddComponents(it);
		for (auto ot : it->components) {

			// Esto es puro Debug, no tiene impacto en la l�gica
			std::cout << "\tid: " << ot.GetID() << '\n';
			std::cout << "\tArguments: \n";
			for (auto ut : ot.GetArgs()) {
				std::cout << "\t\t" << ut.first << " ";
				for (auto at : ut.second) {
					std::cout << at << ' ';
				}
				std::cout << '\n';
			}
			std::cout << "--------\n";
		}
		// Hacemos un GetComponent del Transform y comprobamos si tiene los valores que quer�amos
		eden_ec::CTransform* _tr = ent->GetComponent<eden_ec::CTransform>();
		std::cout << (bool)(_tr != nullptr) << '\n';
		std::cout << _tr->GetPosition().GetX() << " " << _tr->GetPosition().GetY() << " " << _tr->GetPosition().GetZ() << '\n';
	}

	
	eden_render::RenderManager* renderManager = eden_render::RenderManager::Instance();

	renderManager->InitManager("EDEN Engine"); // sustituir por nombre del juego a arrancar
	eden_input::InputManager* inputManager = eden_input::InputManager::Instance();


	eden::Master* master = eden::Master::Instance();
	master->Loop();
	delete master;

	renderManager->CloseManager();
	inputManager->~InputManager();

	for (auto it = entities.begin(); it != entities.end();)
	{
		delete (*it);
		(*it) = nullptr;
		it = entities.erase(it);
	}

	return 0;
}