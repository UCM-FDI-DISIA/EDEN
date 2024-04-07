#define _CRTDBG_MAP_ALLOC
#include <filesystem>

#include "AudioManager.h"
#include "SoundClip.h"
#include "AudioEngine.h"
#include "ErrorHandler.h"
#include "ResourcesManager.h"

eden_audio::AudioManager::AudioManager() {
	//Inicializamos el motor de sonido en caso de que no se haya creado
	audio_wrapper::AudioEngine::Instance();
	//Cargamos todos los recursos de sonido
	LoadResources();
}

eden_audio::AudioManager::~AudioManager() {
	_soundMap.clear();
	audio_wrapper::AudioEngine::Instance()->Close();
}

void eden_audio::AudioManager::LoadResources() {
	eden_resources::ResourcesManager* resManager = eden_resources::ResourcesManager::Instance();
	auto ot = resManager->GetRutesAudios().begin();
	for (auto it = resManager->GetAudios().begin(); it != resManager->GetAudios().end(); it++) {
		_soundMap[*it] = new audio_wrapper::SoundClip(*ot);
		ot++;
	}
	resManager = nullptr;
}

audio_wrapper::SoundClip* eden_audio::AudioManager::GetSoundClip(std::string filename) const {
	auto it = _soundMap.find(filename);
	if (it == _soundMap.end()) eden_error::ErrorHandler::Instance()->Exception("Music file not found", "El archivo de sonido " + filename + " no ha sido encontrado.");
	return it->second;
}