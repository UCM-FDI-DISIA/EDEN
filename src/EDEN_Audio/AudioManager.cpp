#include <filesystem>

#include "AudioManager.h"
#include "SoundClip.h"
#include "AudioEngine.h"
#include "ErrorHandler.h"
#include "ResourcesManager.h"
#include "Entity.h"
#include "CAudioEmitter.h"
#include "Sound.h"
#include "SceneManager.h"

eden_audio::AudioManager::AudioManager() : _globalVolume(1.0f) {
	//Inicializamos el motor de sonido en caso de que no se haya creado
	audio_wrapper::AudioEngine::Instance();
	//Cargamos todos los recursos de sonido
	LoadResources();
}

eden_audio::AudioManager::~AudioManager() {
	for (auto elem : _soundMap) delete elem.second;
	for (auto scene : _audioScenes) delete scene.second;
	audio_wrapper::AudioEngine::Instance()->Close();
}

eden_audio::AudioManager* eden_audio::AudioManager::GetInstance() {
	return static_cast<AudioManager*>(Instance());
}

void eden_audio::AudioManager::LoadResources() {
	std::set<std::string> audioRoutes = eden_resources::ResourcesManager::Instance()->GetRoutesAudios();
	std::set<std::string> audios = eden_resources::ResourcesManager::Instance()->GetAudios();
	auto ot = audioRoutes.begin();
	for (auto it = audios.begin(); it != audios.end(); it++) {
		_soundMap[*it] = new audio_wrapper::SoundClip(*ot);
		ot++;
	}
}

void eden_audio::AudioManager::Update(float dt) {
	for (auto ent : _currentAudioScene->_entities) {
		auto s = ent->GetComponent<eden_ec::CAudioEmitter>()->GetSound();
		if (s && s->HasBeingCreated() && s->HasEnded()) s->Stop();
	}
	for (auto ent : _dontDestroyOnLoad->_entities) {
		auto s = ent->GetComponent<eden_ec::CAudioEmitter>()->GetSound();
		if (s && s->HasBeingCreated() && s->HasEnded()) s->Stop();
	}
}

EDEN_API void eden_audio::AudioManager::AddAudioEntityToDontDestroyOnLoad(eden_ec::Entity* e)
{
	std::unordered_map<std::string, InfoAudioWorld*>::iterator it = _audioScenes.find(eden::SceneManager::Instance()->GetDontDestroyOnLoadID());
	if (it != _audioScenes.end()) {
		if (e != nullptr) it->second->_entities.insert(e);
	}
	else eden_error::ErrorHandler::Instance()->Warning("AudioManager ERROR in line 44 could not find scene: " + e->GetSceneID() + "\n");
}

audio_wrapper::SoundClip* eden_audio::AudioManager::GetSoundClip(std::string filename) const {
	auto it = _soundMap.find(filename);
	if (it == _soundMap.end()) eden_error::ErrorHandler::Instance()->Exception("Music file not found", "El archivo de sonido " + filename + " no ha sido encontrado.");
	return it->second;
}

void eden_audio::AudioManager::AddAudioEntity(eden_ec::Entity* e) {
	std::unordered_map<std::string, InfoAudioWorld*>::iterator it = _audioScenes.find(e->GetSceneID());
	if (it != _audioScenes.end()) {
		if (e != nullptr) it->second->_entities.insert(e);
	}
	else eden_error::ErrorHandler::Instance()->Warning("AudioManager ERROR in line 44 could not find scene: " + e->GetSceneID() + "\n");
}

void eden_audio::AudioManager::RemoveAudioEntity(eden_ec::Entity* e) {
	std::unordered_map<std::string, InfoAudioWorld*>::iterator it = _audioScenes.find(e->GetSceneID());
	if (it != _audioScenes.end()) {
		if (e != nullptr) it->second->_entities.erase(e);
	}
	else eden_error::ErrorHandler::Instance()->Warning("AudioManager ERROR in line 52 could not find scene: " + e->GetSceneID() + "\n");
}

void eden_audio::AudioManager::SetGlobalVolume(float volume) {
	if (volume > 1.0f) volume = 1.0f;
	if (volume < 0.0f) volume = 0.0f;
	_globalVolume = volume;
	for (auto it = _audioScenes.begin(); it != _audioScenes.end(); ++it) {
		for (auto ent : it->second->_entities) ent->GetComponent<eden_ec::CAudioEmitter>()->MixWithGlobalVolume(_globalVolume);
	}
}

float eden_audio::AudioManager::GetGlobalVolume() const {
	return _globalVolume;
}

void eden_audio::AudioManager::CreateAudioScene(std::string id) {
	auto sceneIt = _audioScenes.find(id);
	if (_currentAudioScene) {
		for (auto e : _currentAudioScene->_entities) {
			eden_ec::CAudioEmitter* emitter = e->GetComponent<eden_ec::CAudioEmitter>();
			switch (emitter->GetCurrentState()) {
				case eden_ec::CAudioEmitter::SoundState::PAUSED: case eden_ec::CAudioEmitter::SoundState::PLAYING: {
					// Vuelvo a pausar el sonido en los pausados para que su previousState se ponga en paused tambien
					emitter->Pause();
				} break;
				case eden_ec::CAudioEmitter::SoundState::STOPPED: {
					// Vuelvo a parar el sonido en los parados para que su previousState se ponga en stopped tambien
					emitter->Stop();
				} break;
			}
		}
	}

	if (sceneIt == _audioScenes.end()) {
		InfoAudioWorld* info = new InfoAudioWorld();
		if (id == eden::SceneManager::Instance()->GetDontDestroyOnLoadID()) _dontDestroyOnLoad = info;
		else _currentAudioScene = info;
		_audioScenes[id] = info;
	}
	else {
		_currentAudioScene = sceneIt->second;
		for (auto e : _currentAudioScene->_entities) {
			eden_ec::CAudioEmitter* emitter = e->GetComponent<eden_ec::CAudioEmitter>();
			switch (emitter->GetPreviousState()) {
				case eden_ec::CAudioEmitter::SoundState::PLAYING: {
					emitter->Resume();
				} break;
			}
		}
	}
}

void eden_audio::AudioManager::RemoveAudioScene(std::string id1, std::string id2) {
	auto sceneIt = _audioScenes.find(id1);
	if (sceneIt != _audioScenes.end()) {
		delete sceneIt->second;
		_audioScenes.erase(sceneIt);
		_currentAudioScene = nullptr;
	}
	CreateAudioScene(id2);
}