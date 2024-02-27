#include "SceneManager.h"
#include <iostream>
#include "Scene.h";

SceneManager::~SceneManager() {
	for (auto it = _scenes.begin(); it != _scenes.end();) {
		delete (*it);
		it = _scenes.erase(it);
	}
	if (_activeScene != nullptr) delete _activeScene;
}

Scene* SceneManager::PushScene(const std::string& ID) {
	Scene* newSc = new Scene(ID);
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
		if((*it)->GetToRender()) (*it)->Render();
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
