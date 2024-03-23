#include <iostream>

#include "SceneManager.h"
#include <ScriptManager.h>
#include "Scene.h";
#include <unordered_map>

namespace eden {

	SceneManager::~SceneManager() {
		for (auto it = _scenes.begin(); it != _scenes.end();) {
			delete (*it);
			it = _scenes.erase(it);
		}
		//Está borrando una escena que YA se ha borrado
		//if (_activeScene != nullptr) delete _activeScene;
	}

	Scene* SceneManager::PushScene(const std::string& ID) {

		eden_script::ScriptManager* scriptManager = eden_script::ScriptManager::Instance();
		std::unordered_map<std::string, std::vector<std::string>> collisionInfo;
		std::vector<eden_script::EntityInfo*> info;
		scriptManager->ReadScene(ID, info, collisionInfo);
		Scene* newSc = new Scene(ID, info, collisionInfo);
		_scenes.push_front(newSc);
		_activeScene = newSc;
		return newSc;
	}

	Scene* SceneManager::ChangeScene(const std::string& ID) {
		EmptyStack();
		return PushScene(ID);
	}

	void SceneManager::PopScene() {
		_scenes.front()->SetToDestroy();
		_scenes.pop_front();
	}

	void SceneManager::PopUntil(const std::string& ID) {
		while (_scenes.front()->GetSceneID() != ID) PopScene();
	}

	void SceneManager::EmptyStack() {
		while (_scenes.size() > 0) PopScene();
	}

	void SceneManager::Update(float dt) {
		_scenes.front()->Update(dt);

		auto it = _scenes.end();
		it--;
		for (; it >= _scenes.begin();) {
			if ((*it)->GetToRender()) (*it)->Render();
			if (it > _scenes.begin()) --it;
			else break;
		}

		for (auto it = _scenes.begin(); it != _scenes.end();) {
			if ((*it)->GetToDestroy()) {
				delete (*it);
				it = _scenes.erase(it);
			}
			else ++it;
		}
	}
}