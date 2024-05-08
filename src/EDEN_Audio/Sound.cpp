#define _CRTDBG_MAP_ALLOC
#include <irrKlang.h>

#include "Sound.h"
#include "ErrorHandler.h"
#include "AudioEngine.h"
#include "Vector3.h"
#include "SoundClip.h"

audio_wrapper::Sound::Sound(SoundClip* clip): _clip(clip), _threeDimensional(false), _filename(clip->GetFilename()) {
    _volumeWithoutGeneralMixing = 1.0f;
    _volumeWithGeneralMixing = 1.0f;
    if (eden_audio::AudioManager::Instance()->GetGlobalVolume() < 1.0f) {
        _isBeingMixed = true;
        _volumeWithGeneralMixing = _volumeWithoutGeneralMixing * eden_audio::AudioManager::Instance()->GetGlobalVolume();
    }
    else _isBeingMixed = false;
}

audio_wrapper::Sound::~Sound() {
    if(_sound) _sound->drop();
    _clip = nullptr;
    _sound = nullptr;
}

void audio_wrapper::Sound::Play(bool loop) {
    if(!_clip) eden_error::ErrorHandler::Instance()->Warning("No se encuentra la fuente de sonido con nombre " + _filename);
    else {
        if (_sound) Restart();
        else {
            _sound = audio_wrapper::AudioEngine::Instance()->Play(_clip->GetSource(), loop);
            if (_isBeingMixed) MixVolumeWithGeneralVolume(eden_audio::AudioManager::Instance()->GetGlobalVolume());
            else SetVolume(_volumeWithoutGeneralMixing);
        }
    }
}

void audio_wrapper::Sound::Play(eden_utils::Vector3 pos, bool loop) {
    if (!_clip) eden_error::ErrorHandler::Instance()->Warning("No se encuentra la fuente de sonido con nombre " + _filename);
    else {
        if(_sound) Restart();
        else {
            _threeDimensional = true;
            _sound = audio_wrapper::AudioEngine::Instance()->Play(_clip->GetSource(), pos, loop);
            if (_isBeingMixed) MixVolumeWithGeneralVolume(eden_audio::AudioManager::Instance()->GetGlobalVolume());
            else SetVolume(_volumeWithoutGeneralMixing);
        }
    }
}

void audio_wrapper::Sound::Pause() {
    if(!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else _sound->setIsPaused(true);
}

void audio_wrapper::Sound::Resume() {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else _sound->setIsPaused(false);
}

bool audio_wrapper::Sound::IsPaused() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return false;
    }
    else return _sound->getIsPaused();
}

void audio_wrapper::Sound::Stop() {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else {
        _sound->stop();
        // Dropeamos el sonido puesto que ya no sera necesario y cuando volvamos a reproducirlo se generera
        // otra instancia de un ISound de Irrklang
        _sound->drop();
        _sound = nullptr;
    }
}

void audio_wrapper::Sound::Restart() {
    bool loop = IsLooped();
    eden_utils::Vector3 pos = GetPlayingPosition();
    Stop();
    _threeDimensional ? Play(pos, loop) : Play(loop);
}

bool audio_wrapper::Sound::HasEnded() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return true;
    }
    else return _sound->isFinished();
}

void audio_wrapper::Sound::SetLoop(bool loop) {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else _sound->setIsLooped(loop);
}

bool audio_wrapper::Sound::IsLooped() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return false;
    }
    else return _sound->isLooped();
}

void audio_wrapper::Sound::SetPan(float pan) {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else {
        if(pan > 1.0) pan = 1.0;
        if(pan < -1.0) pan = -1.0;
        _sound->setPan(pan);
    }
}

float audio_wrapper::Sound::GetPan() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return std::numeric_limits<float>::min();
    }
    else return _sound->getPan();
}

void audio_wrapper::Sound::SetPosition(eden_utils::Vector3 position) {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else {
        _sound->setPosition(audio_wrapper::AudioEngine::EdenVecToIrrklangVec(position));
        _threeDimensional = true;
    }
}

eden_utils::Vector3 audio_wrapper::Sound::GetPlayingPosition() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
    }
    else return audio_wrapper::AudioEngine::IrrklangVecToEdenVec(_sound->getPosition());
}

void audio_wrapper::Sound::SetVolume(float volume) {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    if(volume > 1.0f) volume = 1.0f;
    if(volume < 0.0f) volume = 0.0f;
    _volumeWithoutGeneralMixing = volume;
    if (_isBeingMixed) {
        volume *= eden_audio::AudioManager::Instance()->GetGlobalVolume();
    }
    if(_sound) _sound->setVolume(volume);
} 

float audio_wrapper::Sound::GetVolume() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return std::numeric_limits<float>::min();
    }
    else return _sound->getVolume();
}

void audio_wrapper::Sound::MixVolumeWithGeneralVolume(float generalVolume) {
    if (generalVolume == 1.0f) _isBeingMixed = false;
    else _isBeingMixed = true;
    _volumeWithGeneralMixing = _volumeWithoutGeneralMixing * generalVolume;
    if (_volumeWithGeneralMixing > 1.0f) _volumeWithGeneralMixing = 1.0f;
    if (_volumeWithGeneralMixing < 0.0f) _volumeWithGeneralMixing = 0.0f;
    if(_sound) _sound->setVolume(_volumeWithGeneralMixing);
}

float audio_wrapper::Sound::GetRawVolume() const {
    return _volumeWithoutGeneralMixing;
}

float audio_wrapper::Sound::GetMixedVolume() const {
    return _volumeWithGeneralMixing;
}

void audio_wrapper::Sound::SetPitch(float pitch) {
    if (!_sound) eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
    else {
        if (pitch < 0.0f) pitch = 0.0f;
        _sound->setPlaybackSpeed(pitch);
    }
}

float audio_wrapper::Sound::GetPitch() const {
    if (!_sound) {
        eden_error::ErrorHandler::Instance()->Warning("No se ha creado un sonido con ruta de clip " + _filename);
        return std::numeric_limits<float>::min();
    }
    else return _sound->getPlaybackSpeed();
}

std::string audio_wrapper::Sound::GetFilename() const {
    return _filename;
}

bool audio_wrapper::Sound::HasBeingCreated() const {
    return _sound;
}