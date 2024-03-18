#include <irrKlang.h>

#include "SoundWrapper.h"
#include <ErrorHandler.h>
#include "IrrklangWrapper.h"
#include "Vector3.h"

audio_wrapper::SoundWrapper::SoundWrapper(std::string file): _fileName(file) {
    _soundSource = audio_wrapper::IrrklangWrapper::Instance()->CreateSoundSource(file);
}

audio_wrapper::SoundWrapper::~SoundWrapper() {
    _soundSource->drop();
    _sound->drop();
    _soundSource = nullptr;
    _sound = nullptr;
}

void audio_wrapper::SoundWrapper::Play(bool loop) {
    _sound = audio_wrapper::IrrklangWrapper::Instance()->Play(_soundSource, loop);
}

void audio_wrapper::SoundWrapper::Play(eden_utils::Vector3 pos, bool loop) {
    _sound = audio_wrapper::IrrklangWrapper::Instance()->Play(_soundSource, pos, loop);
}

void audio_wrapper::SoundWrapper::ChangeVolume(float volume) {
    _sound->setVolume(volume);
}
float audio_wrapper::SoundWrapper::GetVolume() const {
    return _sound->getVolume();
}