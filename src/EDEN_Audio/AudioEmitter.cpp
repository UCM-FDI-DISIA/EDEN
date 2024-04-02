#include "AudioEmitter.h"
#include "AudioManager.h"
#include "Sound.h"
#include "SoundClip.h"

eden_audio::AudioEmitter::AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos, eden_utils::Vector3 emittingDir) : _3D(is3D), _position(pos), _emittingDirection(emittingDir) {
	ChangeClip(name);
}

void eden_audio::AudioEmitter::Play() {
	_sounds.push_back(new audio_wrapper::Sound(_soundClip));
	//_3D ? _soundClip->Play(_position, _loop) : _soundClip->Play(_loop);
}

void eden_audio::AudioEmitter::ChangeClip(std::string name) {
	_soundClip = eden_audio::AudioManager::Instance()->GetSoundClip(name);
}