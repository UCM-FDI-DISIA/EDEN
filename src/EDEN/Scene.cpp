#include <iostream>

#include "Vector3.h"
#include "Quaternion.h"
#include "Scene.h"
#include <ComponentArguments.h>
#include <ScriptManager.h>
#include <PhysicsManager.h>
#include "Entity.h"
#include "Transform.h"
namespace eden {
	Scene::Scene(const std::string& ID, std::vector<eden_script::EntityInfo*>& info, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo) {
		_ID = ID;
		physics_manager::PhysicsManager* physicsManager = physics_manager::PhysicsManager::Instance();
		physicsManager->CreateCollisionLayer("DEFAULT");
		for (auto it : collisionInfo)
		{
			physicsManager->CreateCollisionLayer(it.first);
		}
		for (auto it : collisionInfo)
		{
			for (auto collisionLayer : it.second) {
				physicsManager->AddCollisionToLayer(it.first, collisionLayer);
			}
		}
		Instantiate(info);
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info) {
		// Decimos qué estamos leyendo por consola
#ifdef _DEBUG
		std::cout << "\n\nEntity: " << info->name << '\n';
		std::cout << "Components:\n--------\n";
#endif
		// Cremoas una nueva entidad según el nombre que hayamos recibido en 'info' al leer el .lua
		auto ent = new eden_ec::Entity(info->name);
		// Creamos sus componentes según la info leída
		ent->AddComponents(info);
#ifdef _DEBUG
		for (auto ot : info->components) {

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
#endif
		AddGameObject(info->name, ent);
		return ent;
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info, eden_utils::Vector3 pos) {
		eden_ec::Entity* ent = Instantiate(info);
		eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
		if (tr != nullptr) tr->SetPosition(pos);
		
		return ent;
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info, eden_utils::Quaternion rot) {
		eden_ec::Entity* ent = Instantiate(info);
		eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
		if (tr != nullptr) tr->SetRotation(rot);

		return ent;
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info, eden_utils::Vector3 pos, eden_utils::Quaternion rot) {
		eden_ec::Entity* ent = Instantiate(info);
		eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
		if (tr != nullptr) 
		{
			tr->SetPosition(pos);
			tr->SetRotation(rot);
		}

		return ent;
	}

	void Scene::Instantiate(std::vector<eden_script::EntityInfo*> info) {
		for (auto it : info) {
			Instantiate(it);
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
		_ent->StartComponents();
		_gameEntitiesList.insert({ ID, _ent });
	}
}