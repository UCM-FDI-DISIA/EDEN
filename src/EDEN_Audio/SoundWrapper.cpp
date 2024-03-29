#define _CRTDBG_MAP_ALLOC
#include <irrKlang.h>

#include "SoundWrapper.h"
#include <ErrorHandler.h>
#include "AudioWrapper.h"
#include "Vector3.h"

audio_wrapper::SoundWrapper::SoundWrapper(std::string file): _fileName(file), _threeDimensional(false) {
    _soundSource = audio_wrapper::AudioWrapper::Instance()->CreateSoundSource(file);
}

audio_wrapper::SoundWrapper::~SoundWrapper() {
    _soundSource->drop();
    _sound->drop();
    _soundSource = nullptr;
    _sound = nullptr;
}

void audio_wrapper::SoundWrapper::Play(bool loop) {
    eden_error::ErrorHandler::Instance()->Assert(_soundSource, "No se encuentra la fuente de sonido con nombre " + _fileName);
    eden_error::ErrorHandler::Instance()->Assert(!_sound, "Ya hay un sonido reproduciendose derivado de la fuente de sonido con nombre " + _fileName);
    _sound = audio_wrapper::AudioWrapper::Instance()->Play(_soundSource, loop);
}

void audio_wrapper::SoundWrapper::Play(eden_utils::Vector3 pos, bool loop) {
    eden_error::ErrorHandler::Instance()->Assert(_soundSource, "No se encuentra la fuente de sonido con nombre " + _fileName);
    _threeDimensional = true;
    _sound = audio_wrapper::AudioWrapper::Instance()->Play(_soundSource, pos, loop);
}

void audio_wrapper::SoundWrapper::Pause() {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    _sound->setIsPaused(true);
}

void audio_wrapper::SoundWrapper::Resume() {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    _sound->setIsPaused(false);
}

bool audio_wrapper::SoundWrapper::IsPaused() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return _sound->getIsPaused();
}

void audio_wrapper::SoundWrapper::Stop() {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    _sound->stop();
    // Dropeamos el sonido puesto que ya no sera necesario y cuando volvamos a reproducirlo se generera
    // otra instancia de un ISound de Irrklang
    _sound->drop();
    _sound = nullptr;
}

void audio_wrapper::SoundWrapper::Restart() {
    bool loop = IsLooped();
    eden_utils::Vector3 pos = GetPlayingPosition();
    Stop();
    _threeDimensional ? Play(pos, loop) : Play(loop);
}

bool audio_wrapper::SoundWrapper::HasEnded() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return _sound->isFinished();
}

void audio_wrapper::SoundWrapper::SetLoop(bool loop) {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    _sound->setIsLooped(loop);
}

bool audio_wrapper::SoundWrapper::IsLooped() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return _sound->isLooped();
}

void audio_wrapper::SoundWrapper::SetPan(float pan) {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    if(pan > 1.0) pan = 1.0;
    if(pan < -1.0) pan = -1.0;
    _sound->setPan(pan);
}

float audio_wrapper::SoundWrapper::GetPan() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return _sound->getPan();
}

void audio_wrapper::SoundWrapper::SetPosition(eden_utils::Vector3 position) {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    _sound->setPosition({position.GetX(), position.GetY(), position.GetZ()});
}

eden_utils::Vector3 audio_wrapper::SoundWrapper::GetPlayingPosition() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return {_sound->getPosition().X, _sound->getPosition().Y, _sound->getPosition().Z};
}

void audio_wrapper::SoundWrapper::ChangeVolume(float volume) {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    if(volume > 1.0f) volume = 1.0f;
    if(volume < 0.0f) volume = 0.0f;
    _sound->setVolume(volume);
}

float audio_wrapper::SoundWrapper::GetVolume() const {
    eden_error::ErrorHandler::Instance()->Assert(_sound, "No se encuentra el sonido con nombre " + _fileName);
    return _sound->getVolume();
}