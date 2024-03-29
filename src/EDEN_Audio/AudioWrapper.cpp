#define _CRTDBG_MAP_ALLOC
#include <irrKlang.h>

#include "AudioWrapper.h"
#include <ErrorHandler.h>
#include <Vector3.h>

audio_wrapper::AudioWrapper::AudioWrapper() {
	_soundEngine = irrklang::createIrrKlangDevice();
	if (!_soundEngine) eden_error::ErrorHandler::Instance()->Exception("Sound Engine Failed", "No se ha podido inicializar el sistema de sonido de IrrKlang.");
}

audio_wrapper::AudioWrapper::~AudioWrapper() {
	_soundEngine->drop();
	_soundEngine = nullptr;
}

irrklang::ISoundSource* audio_wrapper::AudioWrapper::CreateSoundSource(std::string file) {
	irrklang::ISoundSource* src = _soundEngine->addSoundSourceFromFile(file.c_str(), irrklang::ESM_AUTO_DETECT, true);
	if (!src) eden_error::ErrorHandler::Instance()->Warning("No se ha podido crear la fuente de audio con nombre: " + file + ".");
	return src;
}

irrklang::ISound* audio_wrapper::AudioWrapper::Play(irrklang::ISoundSource* soundSource, bool loop) {
	return _soundEngine->play2D(soundSource, loop, false, true);
}

irrklang::ISound* audio_wrapper::AudioWrapper::Play(irrklang::ISoundSource* soundSource, eden_utils::Vector3 pos, bool loop) {
	return _soundEngine->play3D(soundSource, irrklang::vec3df(pos.GetX(), pos.GetY(), pos.GetZ()), loop, false, true);
}