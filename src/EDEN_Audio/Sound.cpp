#include "Sound.h"
#include "SoundWrapper.h"
#include "Vector3.h"

eden_audio::Sound::Sound(std::string file) {
	_sound = new audio_wrapper::SoundWrapper(file);
}

eden_audio::Sound::~Sound() {
	delete _sound;
	_sound = nullptr;
}

void eden_audio::Sound::Play(bool loop) {
	_sound->Play(loop);
}

void eden_audio::Sound::Play(eden_utils::Vector3 pos, bool loop) {
	_sound->Play(pos, loop);
}