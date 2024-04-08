#include <irrKlang.h>

#include "SoundClip.h"
#include "AudioEngine.h"

audio_wrapper::SoundClip::SoundClip(std::string filename) : _filename(filename) {
	_soundSource = audio_wrapper::AudioEngine::Instance()->CreateSoundSource(filename);
}

audio_wrapper::SoundClip::~SoundClip() {
	audio_wrapper::AudioEngine::Instance()->RemoveSoundSource(_soundSource);
	_soundSource = nullptr;
}

