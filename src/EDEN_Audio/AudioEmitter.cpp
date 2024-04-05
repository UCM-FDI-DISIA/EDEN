#include "AudioEmitter.h"
#include "AudioManager.h"
#include "Sound.h"
#include "SoundClip.h"
#include "Transform.h"
#include "Entity.h"

const std::string eden_ec::AudioEmitter::_id = "AUDIO_EMITTER";

eden_ec::AudioEmitter::AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos, eden_utils::Vector3 emittingDir) : _3D(is3D) {
	ChangeClip(name);
}

eden_ec::AudioEmitter::~AudioEmitter() {
	Stop();
	_transform = nullptr;
}

void eden_ec::AudioEmitter::Start() {
	_transform = _ent->GetComponent<eden_ec::CTransform>();
}

void eden_ec::AudioEmitter::Update(float t) {

}

void eden_ec::AudioEmitter::Play() {
	if (_sound) {
		if (_sound->GetFilename() == _soundClip->GetFilename()) {
			Restart();
		}
		else {
			Stop();
		}
	}

	if (!_sound) {
		_sound = new audio_wrapper::Sound(_soundClip);
		_3D ? _sound->Play(_transform->GetPosition(), _loop) : _sound->Play(_loop);
	}
}

void eden_ec::AudioEmitter::ChangeClip(std::string name) {
	_soundClip = eden_audio::AudioManager::Instance()->GetSoundClip(name);
}

void eden_ec::AudioEmitter::Pause() {
	_sound->Pause();
}

void eden_ec::AudioEmitter::Resume() {
	_sound->Resume();
}

void eden_ec::AudioEmitter::Restart() {
	_sound->Restart();
}

void eden_ec::AudioEmitter::Stop() {
	_sound->Stop();
	delete _sound;
	_sound = nullptr;
}

audio_wrapper::Sound* eden_ec::AudioEmitter::GetSound() const {
	return _sound;
}