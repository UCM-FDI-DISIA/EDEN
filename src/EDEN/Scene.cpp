#include "Scene.h"
Scene::Scene(std::string id) {
	_ID = id;
	//_renderScene = OgreWrapper::CreateScene(id)
}

Scene::~Scene() {
	for (auto it = _gameEntitiesList.cbegin(); it != _gameEntitiesList.end();) {
		delete it->second; //Llamamos a la destructora de la entidad
		it = _gameEntitiesList.erase(it); //Lo borramos del mapa
	}

	//_renderScene->DestroyEntityNode();
	//_renderScene->Deactivate();
}

void Scene::Update(float dt) {
	for (auto& obj : _gameEntitiesList) {
		obj.second->Update(dt);
	}
}

void Scene::Render() {
	//_renderScene->Render();
}

eden_ec::Entity* Scene::GetEntityByID(std::string id) {
	if (_gameEntitiesList.count(id) == 0)
		return nullptr;
	return _gameEntitiesList[id];
}

void Scene::AddGameObject(std::string id) {
	eden_ec::Entity* newEntity = new eden_ec::Entity();
	//crear la entidad de por si, Lua
	_gameEntitiesList.insert({ id,newEntity });
}
