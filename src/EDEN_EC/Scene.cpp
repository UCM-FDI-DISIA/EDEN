#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "SceneManager.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Scene.h"
#include "ComponentArguments.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "Transform.h"

namespace eden {
	Scene::Scene(const std::string& ID, std::vector<eden_script::EntityInfo*>& info, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo) {
		_ID = ID;
		physics_manager::PhysicsManager::Instance()->InitLayers(ID, collisionInfo);
		Instantiate(info);
		AwakeEntities();
	}

	Scene::Scene(const std::string& ID)
	{
		_ID = ID;
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info) {
		// Decimos que estamos leyendo por consola
#ifdef _DEBUG
		std::cout << "\n\nEntity: " << info->name << '\n';
		std::cout << "Components:\n--------\n";
#endif

		eden_ec::Entity* ent;
		if (info->isBlueprint) {
			// ModifyEntity() with BlueprintInfo
			std::unordered_map<std::string, eden_script::ComponentArguments> entityComponents;

			for (int i = 0; i < info->components.size(); ++i) {
				entityComponents.insert({ info->components[i].GetID(), info->components[i] });
			}

			SceneManager* scnMngr = SceneManager::getInstance();
			auto bInfo = scnMngr->GetBlueprintComponents(info->name);
			std::unordered_map<std::string, eden_script::ComponentArguments> blueprintComponents;
			for (int i = 0; i < bInfo.size(); ++i) {
				blueprintComponents.insert({ bInfo[i].GetID(), bInfo[i] });
			}

			for (auto it : blueprintComponents) {
				auto component = entityComponents.find(it.first);
				if (component == entityComponents.end()) {
					info->components.push_back(it.second);
				}
			}

			ent = new eden_ec::Entity(info->name + "_" + std::to_string(scnMngr->GetBlueprintNumInstances(info->name)), _ID);
			scnMngr->IncreaseBlueprintNumInstances(info->name);
		}
		else {
		   ent = new eden_ec::Entity(info->name, _ID);
		}
		// Cremoas una nueva entidad seg�n el nombre que hayamos recibido en 'info' al leer el .lua
		// Creamos sus componentes seg�n la info le�da
		ent->AddComponents(info);
#ifdef _DEBUG
		for (auto ot : info->components) {

			// Esto es puro Debug, no tiene impacto en la logica
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
		AddNewGameObject(ent);
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
		StartEntities();
		for (auto& obj : _gameEntitiesList) {
			obj.second->Update(dt);
		}
		AwakeEntities();
	}

	void Scene::Render() {
		//_renderScene->Render();
	}

	eden_ec::Entity* Scene::GetEntityByID(const std::string& ID) {
		if (_gameEntitiesList.count(ID) == 0)
			return nullptr;
		return _gameEntitiesList[ID];
	}

	void Scene::AddNewGameObject(eden_ec::Entity* _ent)
	{
		_newEntities.push_back(_ent);
	}

	void Scene::AddExistingGameObject(eden_ec::Entity* _ent) {
		_gameEntitiesList[_ent->GetEntityID()] = _ent;
	}

	void Scene::RemoveGameObject(eden_ec::Entity* _ent)
	{
		_gameEntitiesList.erase(_ent->GetEntityID());
	}

	void Scene::AwakeEntities() {
		for (auto it : _newEntities) {
			it->AwakeComponents();
		}
	}

	void Scene::StartEntities() {
		for (auto it = _newEntities.begin(); it != _newEntities.end();) {
			(*it)->StartComponents();
			_gameEntitiesList.insert({ (*it)->GetEntityID(), (*it) });
			it = _newEntities.erase(it);
		}
	}
}