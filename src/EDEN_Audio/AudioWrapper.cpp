#include <irrKlang.h>

#include "AudioWrapper.h"

audio_wrapper::AudioWrapper::AudioWrapper() {
    _soundEngine = irrklang::createIrrKlangDevice();
}

audio_wrapper::AudioWrapper::~AudioWrapper() {
    _soundEngine->drop();
}