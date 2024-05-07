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

void eden_ec::CAudioEmitter::Awake() {
	eden_audio::AudioManager::Instance()->AddAudioEntity(_ent);
}

void eden_ec::CAudioEmitter::Start() {
	if(_3D) _transform = _ent->GetComponent<eden_ec::CTransform>();
}

void eden_ec::CAudioEmitter::Update(float t) {
	if (_3D && _sound) _sound->SetPosition(_transform->GetPosition());
}

void eden_ec::CAudioEmitter::Play() {
	if (_sound) {
		if (eden_audio::AudioManager::Instance()->GetGlobalVolume() > 0.1f) {
			_3D ? _sound->Play(_transform->GetPosition(), _loop) : _sound->Play(_loop);
		
			_previousState = _currentState;
			_currentState = SoundState::PLAYING;
		}
	}
}

void eden_ec::CAudioEmitter::ChangeClip(std::string name) {
	_soundClip = eden_audio::AudioManager::Instance()->GetSoundClip(name);

	if (_sound) {
		if (!_sound->HasEnded()) {
			if (_sound->GetFilename() == _soundClip->GetFilename()) {
				Restart();
				return;
			}
		}
		Stop();
	}
	_sound = new audio_wrapper::Sound(_soundClip);
}

void eden_ec::CAudioEmitter::Pause() {
	if(_sound) _sound->Pause();
	_previousState = _currentState;
	_currentState = SoundState::PAUSED;
}

void eden_ec::CAudioEmitter::Resume() {
	if(_sound) _sound->Resume();
	_previousState = _currentState;
	_currentState = SoundState::PLAYING;
}

void eden_ec::CAudioEmitter::Restart() {
	if(_sound && eden_audio::AudioManager::Instance()->GetGlobalVolume() > 0.1f) _sound->Restart();
}

void eden_ec::CAudioEmitter::Stop() {
	if (_sound) {
		_sound->Stop();
		delete _sound;
		_sound = nullptr;
	}
	_previousState = _currentState;
	_currentState = SoundState::STOPPED;
}

bool eden_ec::CAudioEmitter::IsPaused() const {
	if (!_sound) return false;
	else return _sound->IsPaused();
}

bool eden_ec::CAudioEmitter::HasEnded() const {
	if (!_sound) return true;
	else return _sound->HasEnded();
}

void eden_ec::CAudioEmitter::SetLoop(bool loop) {
	if(_sound) _sound->SetLoop(loop);
}

bool eden_ec::CAudioEmitter::IsLooped() const {
	if (!_sound) return false;
	else return _sound->IsLooped();
}

void eden_ec::CAudioEmitter::SetPan(float pan) {
	if(_sound) _sound->SetPan(pan);
}

float eden_ec::CAudioEmitter::GetPan() const {
	if (!_sound) return std::numeric_limits<float>::min();
	else return _sound->GetPan();
}

void eden_ec::CAudioEmitter::SetPosition(eden_utils::Vector3 position) {
	if(_sound) _sound->SetPosition(position);
}

eden_utils::Vector3 eden_ec::CAudioEmitter::GetPlayingPosition() const {
	if(!_sound) return { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
	else return _sound->GetPlayingPosition();
}

void eden_ec::CAudioEmitter::SetVolume(float volume) {
	if(_sound) _sound->SetVolume(volume);
}

float eden_ec::CAudioEmitter::GetVolume() const {
	if (!_sound) return std::numeric_limits<float>::min();
	else return _sound->GetVolume();
}

void eden_ec::CAudioEmitter::SetPitch(float pitch) {
	if(_sound) _sound->SetPitch(pitch);
}

float eden_ec::CAudioEmitter::GetPitch() const {
	if (!_sound) return std::numeric_limits<float>::min();
	else return _sound->GetPitch();
}

std::string eden_ec::CAudioEmitter::GetFilename() const {
	if (!_sound) return "";
	else return _sound->GetFilename();
}

audio_wrapper::Sound* eden_ec::CAudioEmitter::GetSound() const {
	return _sound;
}

void eden_ec::CAudioEmitter::MixWithGlobalVolume(float volume) {
	if(_sound) _sound->MixVolumeWithGeneralVolume(volume);
}