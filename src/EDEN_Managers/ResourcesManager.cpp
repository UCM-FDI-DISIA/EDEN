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
	for (const auto& entry : std::filesystem::directory_iterator(MATERIALS_ROUTE)) {
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

std::set<std::string>  eden_resources::ResourcesManager::GetMaterials() {
	return _resourcesGeneral[Resources::Materials];
}

std::set<std::string>  eden_resources::ResourcesManager::GetAudios() {
	return _resourcesGeneral[Resources::Audio];
}

std::set<std::string>  eden_resources::ResourcesManager::GetFonts() {
	return _resourcesGeneral[Resources::Fonts];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRutesMaterials() {
	return _resourcesRutesGeneral[Resources::Materials];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRutesAudios() {
	return _resourcesRutesGeneral[Resources::Audio];
}

std::set<std::string>  eden_resources::ResourcesManager::GetRutesFonts() {
	return _resourcesRutesGeneral[Resources::Fonts];
}