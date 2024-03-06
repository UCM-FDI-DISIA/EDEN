#include "Scene.h"
#include "Entity.h"
#include <iostream>
#include "ComponentArguments.h"
#include "ScriptManager.h"

namespace eden {
	Scene::Scene(const std::string& ID, std::vector<eden_script::EntityInfo*> info) {
		_ID = ID;
		for (auto it : info) {
			// Decimos qué estamos leyendo por consola
			std::cout << "\n\nEntity: " << it->name << '\n';
			std::cout << "Components:\n--------\n";

			// Cremoas una nueva entidad según el nombre que hayamos recibido en 'info' al leer el .lua
			auto ent = new eden_ec::Entity(it->name);
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
			AddGameObject(it->name, ent);
		}

	}

	Scene::~Scene() {
		for (auto it = _gameEntitiesList.begin(); it != _gameEntitiesList.end();) {
			delete it->second; //Llamamos a la destructora de la entidad
			it->second = nullptr;
			it = _gameEntitiesList.erase(it); //Lo borramos del mapa
		}
	}

	void Scene::Update(float dt) {
		for (auto& obj : _gameEntitiesList) {
			obj.second->Update(dt);
		}
	}

	void Scene::Render() {
		//_renderScene->Render();
	}

	eden_ec::Entity* Scene::GetEntityByID(const std::string& ID) {
		if (_gameEntitiesList.count(ID) == 0)
			return nullptr;
		return _gameEntitiesList[ID];
	}

	void Scene::AddGameObject(const std::string& ID, eden_ec::Entity* _ent) {
		_gameEntitiesList.insert({ ID, _ent });
	}
}