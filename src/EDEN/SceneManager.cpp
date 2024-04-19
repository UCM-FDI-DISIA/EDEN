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
#include "AudioManager.h"

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

	void SceneManager::CreateScene(std::string& ID)
	{
		eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();
		std::unordered_map<std::string, std::vector<std::string>> collisionInfo;
		std::vector<eden_script::EntityInfo*> info;
		scriptManager->ReadScene(ID, info, collisionInfo);

		eden_render::RenderManager::Instance()->CreateRenderScene(ID);
		physics_manager::PhysicsManager::Instance()->CreatePhysicsScene(ID);
		eden_audio::AudioManager::Instance()->CreateAudioScene(ID);
		Scene* newSc = new Scene(ID, info, collisionInfo);
		for (auto a : info) delete a;
		_scenes.push_front(newSc);
		_currentScenes.insert(ID);
		_activeScene = newSc;
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

	void SceneManager::PushScene(const std::string& ID) {
		_scenesToAdd.push_back(ID);
	}

	void SceneManager::ChangeScene(const std::string& ID) {
		EmptyStack();
		PushScene(ID);
	}

	void SceneManager::PopScene() {
		if (_scenes.size() > 0) {
			_currentScenes.erase(_scenes.front()->GetSceneID());
			_scenesToDestroy.push_back(_scenes.front());
			_scenes.pop_front();
		}
		else {
			eden_error::ErrorHandler::Instance()->Warning("SceneManager ERROR in line 133, scenes deque was empty, so PopScene could not be done");
		}

		if(_scenes.size() > 0)
			_activeScene = _scenes.front();
	}

	void SceneManager::PopUntil(const std::string& ID) {
		while (_scenes.front()->GetSceneID() != ID) PopScene();
	}

	void SceneManager::EmptyStack() {
		while (_scenes.size() > 0) PopScene();
	}

	void SceneManager::Update(float dt) {

		/*auto it = _scenes.end();
		it--;
		for (; it >= _scenes.begin();) {
			if ((*it)->GetToRender()) (*it)->Render();
			if (it > _scenes.begin()) --it;
			else break;
		}*/

		if (_scenes.size() > 0) 
			_scenes.front()->Update(dt);


		std::string newScene = " ";
		if (_scenesToDestroy.size() > 0) {
			if (_scenesToAdd.size() > 0) newScene = (*(--_scenesToAdd.end()));
			else if (_scenes.size() > 0) newScene = _scenes.front()->GetSceneID();
		}

		for (auto it = _scenesToDestroy.begin(); it != _scenesToDestroy.end();) {	
			std::string prevScene = (*it)->GetSceneID();
			
			eden_audio::AudioManager::Instance()->RemoveAudioScene(prevScene, newScene);
			physics_manager::PhysicsManager::Instance()->RemovePhysicsScene(prevScene, newScene);
			delete (*it);
			it = _scenesToDestroy.erase(it);
			eden_render::RenderManager::Instance()->RemoveRenderScene(prevScene, newScene);
		}

		for (auto it = _scenesToAdd.begin(); it != _scenesToAdd.end();) {
			if (_currentScenes.find(*it) == _currentScenes.end()) {
				CreateScene(*it);
			}
		 	it = _scenesToAdd.erase(it);
		}

		if(_scenes.size() <= 0)
			eden_error::ErrorHandler::Instance()->Exception("scene deque empty", "SceneManager ERROR in line 188, scene deque empty");
	}
}