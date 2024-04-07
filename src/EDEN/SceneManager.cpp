#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <unordered_map>

#include "SceneManager.h"
#include "ScriptManager.h"
#include "Scene.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Entity.h"
#include "ErrorHandler.h"
#include "Transform.h"
#include "ComponentArguments.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

namespace eden {

	std::unordered_map<std::string, SceneManager::BlueprintInfo> SceneManager::_Blueprints = std::unordered_map<std::string, SceneManager::BlueprintInfo>();


	SceneManager::SceneManager() {
		eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();
		std::vector<eden_script::EntityInfo*> blueprints;
		scriptManager->ReadBlueprints(blueprints);

		_Blueprints.clear();

		for (auto it : blueprints) {
			BlueprintInfo info;
			info.numInstances = 0;
			info.components = it->components;
			_Blueprints[it->name] = info;
		}

		for (int i = 0; i < blueprints.size(); ++i) {
			delete blueprints[i];
		}
		blueprints.clear();
	}

	SceneManager::~SceneManager() {
		for (auto it = _scenes.begin(); it != _scenes.end();) {
			delete (*it);
			it = _scenes.erase(it);
		}
		_activeScene = nullptr;
	}

	eden_ec::Entity* SceneManager::InstantiateBlueprint(std::string blueprintID) {

		auto it = _Blueprints.find(blueprintID);

		eden_ec::Entity* ent = nullptr;

		if (it != _Blueprints.end()) {
			std::string name = it->first + "_(" + std::to_string(it->second.numInstances) +')';
			it->second.numInstances++;
			eden_script::EntityInfo* info = new eden_script::EntityInfo();
			info->name = name;
			info->components = it->second.components;
			ent = _activeScene->Instantiate(info);
		}
		else {
			eden_error::ErrorHandler::Instance()->Exception("Blueprint '" + blueprintID + "' Instance failed", "'" + blueprintID + "' was not found in the Blueprints file. Are you missing any definition?");
		}

		return ent;
	}

	eden_ec::Entity* SceneManager::InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos) {
		eden_ec::Entity* ent = InstantiateBlueprint(blueprintID);
		if (ent != nullptr) {
			eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
			if (tr != nullptr) {
				tr->SetPosition(pos);
			}
		}

		return ent;
	}

	eden_ec::Entity* SceneManager::InstantiateBlueprint(std::string blueprintID, eden_utils::Quaternion rot) {
		eden_ec::Entity* ent = InstantiateBlueprint(blueprintID);
		if (ent != nullptr) {
			eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
			if (tr != nullptr) {
				tr->SetRotation(rot);
			}
		}

		return ent;
	}

	eden_ec::Entity* SceneManager::InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos, eden_utils::Quaternion rot) {
		eden_ec::Entity* ent = InstantiateBlueprint(blueprintID);
		if (ent != nullptr) {
			eden_ec::CTransform* tr = ent->GetComponent<eden_ec::CTransform>();
			if (tr != nullptr) {
				tr->SetPosition(pos);
				tr->SetRotation(rot);
			}
		}

		return ent;
	}

	Scene* SceneManager::PushScene(const std::string& ID) {

		eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();
		std::unordered_map<std::string, std::vector<std::string>> collisionInfo;
		std::vector<eden_script::EntityInfo*> info;
		scriptManager->ReadScene(ID, info, collisionInfo);

		physics_manager::PhysicsManager::Instance()->CreatePhysicsScene(ID);
		eden_render::RenderManager::Instance()->CreateRenderScene(ID);
		Scene* newSc = new Scene(ID, info, collisionInfo);
		for (auto a : info) delete a;
		_scenes.push_front(newSc);
		_activeScene = newSc;
		return newSc;
	}

	Scene* SceneManager::ChangeScene(const std::string& ID) {
		EmptyStack();
		return PushScene(ID);
	}

	void SceneManager::PopScene() {
		std::string prevScene = _scenes.front()->GetSceneID();
		_scenesToDestroy.push_back(_scenes.front());
		_scenes.pop_front();
		std::string currentScene = " ";
		if (_scenes.size() > 0) {
			currentScene = _scenes.front()->GetSceneID();
			_activeScene = _scenes.front();
		}

		physics_manager::PhysicsManager::Instance()->RemovePhysicsScene(prevScene, currentScene);
		eden_render::RenderManager::Instance()->RemoveRenderScene(prevScene, currentScene);
	}

	void SceneManager::PopUntil(const std::string& ID) {
		while (_scenes.front()->GetSceneID() != ID) PopScene();
	}

	void SceneManager::EmptyStack() {
		while (_scenes.size() > 0) PopScene();
	}

	void SceneManager::Update(float dt) {
		_scenes.front()->Update(dt);

		/*auto it = _scenes.end();
		it--;
		for (; it >= _scenes.begin();) {
			if ((*it)->GetToRender()) (*it)->Render();
			if (it > _scenes.begin()) --it;
			else break;
		}*/

		for (auto it = _scenesToDestroy.begin(); it != _scenesToDestroy.end();) {	
			delete (*it);
			it = _scenesToDestroy.erase(it);
		}
	}
}