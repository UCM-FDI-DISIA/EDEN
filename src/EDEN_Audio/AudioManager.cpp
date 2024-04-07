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
	for (auto elem : _soundMap) delete elem.second;
	audio_wrapper::AudioEngine::Instance()->Close();
}

void eden_audio::AudioManager::LoadResources() {
	std::set<std::string> audioRoutes = eden_resources::ResourcesManager::Instance()->GetRutesAudios();
	std::set<std::string> audios = eden_resources::ResourcesManager::Instance()->GetAudios();
	auto ot = audioRoutes.begin();
	for (auto it = audios.begin(); it != audios.end(); it++) {
		_soundMap[*it] = new audio_wrapper::SoundClip(*ot);
		ot++;
	}
}

audio_wrapper::SoundClip* eden_audio::AudioManager::GetSoundClip(std::string filename) const {
	auto it = _soundMap.find(filename);
	if (it == _soundMap.end()) eden_error::ErrorHandler::Instance()->Exception("Music file not found", "El archivo de sonido " + filename + " no ha sido encontrado.");
	return it->second;
}