#include "CAudioEmitter.h"
#include "Sound.h"
#include "SoundClip.h"
#include "Transform.h"
#include "Entity.h"
#include "ComponentArguments.h"

eden_ec::CAudioEmitter::CAudioEmitter(std::string name, bool is3D) : _3D(is3D) {
	ChangeClip(name);
}

eden_ec::CAudioEmitter::~CAudioEmitter() {
	eden_audio::AudioManager::Instance()->RemoveAudioEntity(_ent);
	Stop();
	_transform = nullptr;
}

void eden_ec::CAudioEmitter::Init(eden_script::ComponentArguments* args) {
	 ChangeClip(args->GetValueToString("SongName"));
	 _3D = args->GetValueToBool("Is3D");
}

void eden_ec::CAudioEmitter::Start() {
	// Habria que cambiar esta línea cuando se cree el awake
	eden_audio::AudioManager::Instance()->AddAudioEntity(_ent);
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
	_previousState = _currentState;
	_currentState = SoundState::PLAYING;
}

void eden_ec::CAudioEmitter::ChangeClip(std::string name) {
	_soundClip = eden_audio::AudioManager::Instance()->GetSoundClip(name);
}

void eden_ec::CAudioEmitter::Pause() {
	_sound->Pause();
	_previousState = _currentState;
	_currentState = SoundState::PAUSED;
}

void eden_ec::CAudioEmitter::Resume() {
	_sound->Resume();
	_previousState = _currentState;
	_currentState = SoundState::PLAYING;
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
	_previousState = _currentState;
	_currentState = SoundState::STOPPED;
}

bool eden_ec::CAudioEmitter::IsPaused() const {
	return _sound->IsPaused();
}

bool eden_ec::CAudioEmitter::HasEnded() const {
	return _sound->HasEnded();
}

void eden_ec::CAudioEmitter::SetLoop(bool loop) {
	_sound->SetLoop(loop);
}

bool eden_ec::CAudioEmitter::IsLooped() const {
	return _sound->IsLooped();
}

void eden_ec::CAudioEmitter::SetPan(float pan) {
	_sound->SetPan(pan);
}

float eden_ec::CAudioEmitter::GetPan() const {
	return _sound->GetPan();
}

void eden_ec::CAudioEmitter::SetPosition(eden_utils::Vector3 position) {
	_sound->SetPosition(position);
}

eden_utils::Vector3 eden_ec::CAudioEmitter::GetPlayingPosition() const {
	return _sound->GetPlayingPosition();
}

void eden_ec::CAudioEmitter::SetVolume(float volume) {
	_sound->SetVolume(volume);
}

float eden_ec::CAudioEmitter::GetVolume() const {
	return _sound->GetVolume();
}

void eden_ec::CAudioEmitter::SetPitch(float pitch) {
	_sound->SetPitch(pitch);
}

float eden_ec::CAudioEmitter::GetPitch() const {
	return _sound->GetPitch();
}

std::string eden_ec::CAudioEmitter::GetFilename() const {
	return _sound->GetFilename();
}

audio_wrapper::Sound* eden_ec::CAudioEmitter::GetSound() const {
	return _sound;
}