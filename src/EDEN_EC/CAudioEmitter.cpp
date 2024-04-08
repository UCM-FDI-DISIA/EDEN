#include "CAudioEmitter.h"
#include "AudioManager.h"
#include "Sound.h"
#include "SoundClip.h"
#include "Transform.h"
#include "Entity.h"
#include "ComponentArguments.h"

eden_ec::CAudioEmitter::CAudioEmitter(std::string name, bool is3D) : _3D(is3D) {
	ChangeClip(name);
}

eden_ec::CAudioEmitter::~CAudioEmitter() {
	Stop();
	_transform = nullptr;
}

void eden_ec::CAudioEmitter::Init(eden_script::ComponentArguments* args) {
	 ChangeClip(args->GetValueToString("SongName"));
	 _3D = args->GetValueToBool("Is3D");
}

void eden_ec::CAudioEmitter::Start() {
	_transform = _ent->GetComponent<eden_ec::CTransform>();
}

void eden_ec::CAudioEmitter::Update(float t) {
	if (_sound) _sound->SetPosition(_transform->GetPosition());
}

void eden_ec::CAudioEmitter::Play() {
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

void eden_ec::CAudioEmitter::ChangeClip(std::string name) {
	_soundClip = eden_audio::AudioManager::Instance()->GetSoundClip(name);
}

void eden_ec::CAudioEmitter::Pause() {
	_sound->Pause();
}

void eden_ec::CAudioEmitter::Resume() {
	_sound->Resume();
}

void eden_ec::CAudioEmitter::Restart() {
	_sound->Restart();
}

void eden_ec::CAudioEmitter::Stop() {
	if (_sound) {
		_sound->Stop();
		delete _sound;
	}
	_sound = nullptr;
}

audio_wrapper::Sound* eden_ec::CAudioEmitter::GetSound() const {
	return _sound;
}