#define _CRTDBG_MAP_ALLOC
#include "Canvas.h"
#include "Entity.h"
#include "UIComponent.h"
#include "ErrorHandler.h"
#include "SceneManager.h"
#include "Scene.h"

void eden_canvas::Canvas::Resize() {
	std::string sceneID = eden::SceneManager::Instance()->GetCurrentScene()->GetSceneID();
	std::unordered_set<eden_ec::UIComponent*>* entities = &_entities[sceneID];
	for (eden_ec::UIComponent* ent : (*entities)) {
		ent->Resize();
	}
}

void eden_canvas::Canvas::InitCanvas(){
	std::string sceneID = eden::SceneManager::Instance()->GetCurrentScene()->GetSceneID();
	std::unordered_set<eden_ec::UIComponent*>* entities = &_entities[sceneID];
	for (eden_ec::UIComponent* ent : (*entities)) {
		ent->SetParameters();
	}
}

void eden_canvas::Canvas::addRenderEntity(eden_ec::UIComponent* ent) {
	std::string sceneID = ent->GetSceneID();
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt == _entities.end())
	{
		std::string message = "Canvas ERROR in line 20 could not find scene: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
	else
	{
		sceneIt->second.insert(ent);
	}
}

void eden_canvas::Canvas::removeRenderEntity(eden_ec::UIComponent* ent) {
	std::string sceneID = ent->GetSceneID();
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt == _entities.end())
	{
		std::string message = "Canvas ERROR in line 20 could not find scene: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
	else
	{
		sceneIt->second.erase(ent);
	}
}

void eden_canvas::Canvas::addScene(std::string sceneID)
{
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt == _entities.end())
	{
		_entities.insert({ sceneID,{} });
	}
	else
	{
		std::string message = "Canvas ERROR in line 52 scene already exist: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void eden_canvas::Canvas::removeScene(std::string sceneID)
{
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt != _entities.end())
	{
		_entities.erase(sceneID);
	}
	else
	{
		std::string message = "Canvas ERROR in line 52 scene does not exist: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void eden_canvas::Canvas::ShowScene(std::string sceneID) {
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt != _entities.end()) {
		for (eden_ec::UIComponent* ent : sceneIt->second) {
			ent->Show(true);
		}
	}
	else {
		std::string message = "Canvas ERROR in line 87 scene does not exist: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void eden_canvas::Canvas::HideScene(std::string sceneID) {
	auto sceneIt = _entities.find(sceneID);
	if (sceneIt != _entities.end()) {
		for (eden_ec::UIComponent* ent : sceneIt->second) {
			ent->Hide(true);
		}
	}
	else {
		std::string message = "Canvas ERROR in line 87 scene does not exist: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}
