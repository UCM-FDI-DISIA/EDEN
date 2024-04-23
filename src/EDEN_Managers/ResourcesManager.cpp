#define _CRTDBG_MAP_ALLOC
#include <filesystem>

#include "ResourcesManager.h"
#include "ErrorHandler.h"

eden_resources::ResourcesManager* eden_resources::ResourcesManager::getInstance() {
	return static_cast<ResourcesManager*>(Instance());
}

eden_resources::ResourcesManager::ResourcesManager() {
	//Cargamos todos los recursos de sonido
	LoadResources();
}

eden_resources::ResourcesManager::~ResourcesManager() {
}

void eden_resources::ResourcesManager::LoadResources() {
	std::set<std::string> aux;
	std::set<std::string> auxRutes;
	for (const auto& entry : std::filesystem::directory_iterator(MESH_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
	aux.clear();
	auxRutes.clear();
	for (const auto& entry : std::filesystem::directory_iterator(MATERIALS_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
	aux.clear();
	auxRutes.clear();
	for (const auto& entry : std::filesystem::directory_iterator(UI_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
	aux.clear();
	auxRutes.clear();
	for (const auto& entry : std::filesystem::directory_iterator(FONTS_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
	aux.clear();
	auxRutes.clear();
	for (const auto& entry : std::filesystem::directory_iterator(AUDIO_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
	aux.clear();
	auxRutes.clear();
	for (const auto& entry : std::filesystem::directory_iterator(DEFAULT_ROUTE)) {
		aux.insert(entry.path().filename().string());
		auxRutes.insert(entry.path().string());
	}
	_resourcesGeneral.push_back(aux);
	_resourcesRutesGeneral.push_back(auxRutes);
}

bool eden_resources::ResourcesManager::FileExist(std::string name, Resources res) {
	return _resourcesGeneral[res].contains(name);
}

EDEN_API std::set<std::string> eden_resources::ResourcesManager::GetMeshes()
{
	return _resourcesGeneral[Resources::Mesh];
}

std::set<std::string>  eden_resources::ResourcesManager::GetMaterials() {
	return _resourcesGeneral[Resources::Materials];
}

EDEN_API std::set<std::string> eden_resources::ResourcesManager::GetUIElements()
{
	return _resourcesGeneral[Resources::UI];
}

std::set<std::string>  eden_resources::ResourcesManager::GetAudios() {
	return _resourcesGeneral[Resources::Audio];
}

std::set<std::string>  eden_resources::ResourcesManager::GetFonts() {
	return _resourcesGeneral[Resources::Fonts];
}

EDEN_API std::set<std::string> eden_resources::ResourcesManager::GetRoutesMeshes()
{
	return _resourcesRutesGeneral[Resources::Mesh];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRoutesMaterials() {
	return _resourcesRutesGeneral[Resources::Materials];
}

EDEN_API std::set<std::string> eden_resources::ResourcesManager::GetRoutesUIElements()
{
	return _resourcesRutesGeneral[Resources::UI];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRoutesAudios() {
	return _resourcesRutesGeneral[Resources::Audio];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRoutesFonts() {
	return _resourcesRutesGeneral[Resources::Fonts];
}