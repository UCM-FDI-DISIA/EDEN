#include "AudioEmitter.h"
#include "AudioManager.h"
#include "Sound.h"

eden_audio::AudioEmitter::AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos, eden_utils::Vector3 emittingDir) : _3D(is3D), _position(pos), _emittingDirection(emittingDir) {
	//_soundClip = eden_audio::AudioManager::Instance()->GetSound(name);
}

void eden_audio::AudioEmitter::Play() {
	_3D ? _soundClip->Play(_position, _loop) : _soundClip->Play(_loop);
}