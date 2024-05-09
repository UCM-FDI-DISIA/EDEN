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
#include "ErrorHandler.h"

namespace eden {
	Scene::Scene(const std::string& ID, bool setDebugLog)
	{
		_ID = ID;
		_debugLog = setDebugLog;
	}

	std::vector<eden_ec::Entity*> Scene::GetEntitiesWithComponent(std::string componentID) {
		std::vector<eden_ec::Entity*> vec = std::vector<eden_ec::Entity*>();
		for (auto it : _gameEntitiesList) {
			if (it.second.first->HasComponent(componentID)) vec.push_back(it.second.first);
		}

		for (auto it : _newEntities[_currentIteration]) {
			if (it.second->HasComponent(componentID)) vec.push_back(it.second);
		}

		return vec;
	}

	eden_ec::Entity* Scene::Instantiate(eden_script::EntityInfo* info) {
		if (!_newEntities[_currentIteration].count(info->name)) {

			// Decimos que estamos leyendo por consola
			if (_debugLog) {
				std::cout << "\n\nEntity: " << info->name << '\n';
				std::cout << "Components:\n--------\n";
			}
			eden_ec::Entity* ent;
			if (info->isBlueprint) {
				if(_debugLog) std::cout << "THIS IS A BLUEPRINT!!!\n";
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
			try {
				ent->AddComponents(info);
			}
			catch (std::exception e) {
				delete ent;
				eden_error::ErrorHandler::Instance()->Exception("Scene ERROR in line 62", "could not create entity" + info->name + "\n" + e.what() + "\n");
			}

			if (_debugLog) {
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
			}

			AddNewGameObject(ent);
			return ent;
		}
	}

	void Scene::InitScene(std::vector<eden_script::EntityInfo*>& info, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo)
	{
		physics_manager::PhysicsManager::Instance()->InitLayers(_ID, collisionInfo);
		Instantiate(info);
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
			if(it->second.second) delete it->second.first; //Llamamos a la destructora de la entidad
			it->second.first = nullptr;
			it = _gameEntitiesList.erase(it); //Lo borramos del mapa
		}

		for (auto it = _newEntities.begin(); it != _newEntities.end(); ++it) {
			for (auto it2 = it->second.begin(); it2 != it->second.end();) {
				delete it2->second; //Llamamos a la destructora de la entidad
				it2->second = nullptr;
				it2 = it->second.erase(it2); //Lo borramos del mapa
			}
		}
	}

 	void Scene::Update(float dt) {
		AwakeEntities();
		StartEntities();
		for (auto obj = _gameEntitiesList.begin(); obj != _gameEntitiesList.end();) {
			if (obj->second.first->IsAlive()) {
				if (obj->second.first->IsActive()) {
					obj->second.first->Update(dt);
				}
				++obj;
			}
			else{
				delete obj->second.first; //Llamamos a la destructora de la entidad
				obj->second.first = nullptr;
				obj = _gameEntitiesList.erase(obj); //Lo borramos del mapa
			}
		}
	}

	void Scene::Render() {
		//_renderScene->Render();
	}

	eden_ec::Entity* Scene::GetEntityByID(const std::string& ID) {
		if (_gameEntitiesList.count(ID) == 0)
			if (_newEntities[_currentIteration].count(ID) == 0)
				return nullptr;
			else
				return _newEntities[_currentIteration][ID];
		return _gameEntitiesList[ID].first;
	}

	void Scene::AddNewGameObject(eden_ec::Entity* _ent)
	{
		_newEntities[_currentIteration].insert({ _ent->GetEntityID(), _ent });
	}

	bool Scene::AddExistingGameObject(eden_ec::Entity* _ent) {
		if (!_gameEntitiesList.contains(_ent->GetEntityID()))
		{
			_gameEntitiesList[_ent->GetEntityID()] = { _ent,true };
			return true;
		}
		return false;		
	}

	bool Scene::RemoveGameObject(eden_ec::Entity* _ent)
	{
		if (_gameEntitiesList.contains(_ent->GetEntityID()))
		{
			_gameEntitiesList.erase(_ent->GetEntityID());
			return true;
		}
		return false;
	}

	void Scene::AwakeEntities() {
		for (auto it : _newEntities[_currentIteration]) {
			it.second->AwakeComponents();
			_gameEntitiesList.insert({ it.second->GetEntityID(), { it.second, false} });
		}
	}

	void Scene::StartEntities() {
		int lastIteration = _currentIteration;
		_currentIteration++;
		for (auto it = _newEntities[lastIteration].begin(); it != _newEntities[lastIteration].end();) {
			eden_ec::Entity* ent = it->second;
			_gameEntitiesList[ent->GetEntityID()] = { ent, true};
			it = _newEntities[lastIteration].erase(it);
			ent->StartComponents();
		}
	}
}