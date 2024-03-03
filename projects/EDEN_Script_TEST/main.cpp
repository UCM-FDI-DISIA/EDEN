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

int main() {
	// ---------- TODO ESTO SON PRUEBAS PARA MOSTRAR EL FUNCIONAMIENTO DEL ScriptManager, -------------------
	// ---------- NO LO TOMÉIS COMO CÓDIGO FINAL GRACIAS								  -------------------

	// Cogemos el scriptManager
	eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();

	// Información que se rellenará al leer la escena
	std::vector<eden_script::EntityInfo*> info;

	// Leemos una escena
	scriptManager->ReadScene("test_scene", info);

	// Registramos el componente Transform, que es el único que usaremos de momento
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	std::vector<eden_ec::Entity*> entities;

	// Recorremos la información recibida 
	for (auto it : info) {
		// Decimos qué estamos leyendo por consola
		std::cout << "\n\nEntity: " << it->name << '\n';
		std::cout << "Components:\n--------\n";

		// Cremoas una nueva entidad según el nombre que hayamos recibido en 'info' al leer el .lua
		auto ent = new eden_ec::Entity(it->name);
		entities.push_back(ent);

		// Creamos sus componentes según la info leída
		ent->AddComponents(it);
		for (auto ot : it->components) {

			// Esto es puro Debug, no tiene impacto en la lógica
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
		// Hacemos un GetComponent del Transform y comprobamos si tiene los valores que queríamos
		eden_ec::CTransform* _tr = ent->GetComponent<eden_ec::CTransform>();
		std::cout << (bool)( _tr != nullptr) << '\n';
		std::cout << _tr->GetPosition().GetX() << " " << _tr->GetPosition().GetY() << " " << _tr->GetPosition().GetZ() << '\n';
	}

	for (auto it = entities.begin(); it != entities.end();)
	{
		delete (*it);
		(*it) = nullptr;
		it = entities.erase(it);
	}

	return 0;
}