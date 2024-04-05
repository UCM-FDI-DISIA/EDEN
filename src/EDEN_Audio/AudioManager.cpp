#define _CRTDBG_MAP_ALLOC
#include <filesystem>

#include "AudioManager.h"
#include "SoundClip.h"
#include "AudioEngine.h"
#include "ErrorHandler.h"

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
	for (const auto& entry : std::filesystem::directory_iterator(AUDIO_ROUTE)) {
		_soundMap[entry.path().filename().string()] = new audio_wrapper::SoundClip(entry.path().string());
	}
}

audio_wrapper::SoundClip* eden_audio::AudioManager::GetSoundClip(std::string filename) const {
	auto it = _soundMap.find(filename);
	if (it == _soundMap.end()) eden_error::ErrorHandler::Instance()->Exception("Music file not found", "El archivo de sonido " + filename + " no ha sido encontrado.");
	return it->second;
}