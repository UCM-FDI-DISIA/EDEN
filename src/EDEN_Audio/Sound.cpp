#define _CRTDBG_MAP_ALLOC
#include "Sound.h"
#include "SoundWrapper.h"
#include "Vector3.h"
#include "ErrorHandler.h"

eden_audio::Sound::Sound(std::string file) {
	_sound = new audio_wrapper::SoundWrapper(file);
}

eden_audio::Sound::~Sound() {
	delete _sound;
	_sound = nullptr;
}

void eden_audio::Sound::Play(bool loop) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Play(loop);
}

void eden_audio::Sound::Play(eden_utils::Vector3 pos, bool loop) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Play(pos, loop);
}

void eden_audio::Sound::Pause() {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Pause();
}

void eden_audio::Sound::Resume() {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Resume();
}

bool eden_audio::Sound::IsPaused() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->IsPaused();
}

void eden_audio::Sound::Stop() {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Stop();
}

void eden_audio::Sound::Restart() {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->Restart();
}

bool eden_audio::Sound::HasEnded() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->HasEnded();
}

void eden_audio::Sound::SetLoop(bool loop) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->SetLoop(loop);
}

bool eden_audio::Sound::IsLooped() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->IsLooped();
}

void eden_audio::Sound::SetPan(float pan) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->SetPan(pan);
}

float eden_audio::Sound::GetPan() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->GetPan();
}

void eden_audio::Sound::SetPosition(eden_utils::Vector3 position) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->SetPosition(position);
}

eden_utils::Vector3 eden_audio::Sound::GetPlayingPosition() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->GetPlayingPosition();
}

void eden_audio::Sound::ChangeVolume(float volume) {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	_sound->ChangeVolume(volume);
}

float eden_audio::Sound::GetVolume() const {
	eden_error::ErrorHandler::Instance()->Assert(_sound, "El sonido " + _filename + " no se ha creado correctamente.");
	return _sound->GetVolume();
}
