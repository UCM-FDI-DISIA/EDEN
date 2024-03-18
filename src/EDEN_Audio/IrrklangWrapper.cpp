#include <irrKlang.h>

#include "IrrklangWrapper.h"
#include <ErrorHandler.h>
#include <Vector3.h>

audio_wrapper::IrrklangWrapper::IrrklangWrapper() {
	_soundEngine = irrklang::createIrrKlangDevice();
	if (!_soundEngine) EDEN_EXCEPTION("No se ha podido inicializar el sistema de sonido de IrrKlang.");
}

audio_wrapper::IrrklangWrapper::~IrrklangWrapper() {
	_soundEngine->drop();
	_soundEngine = nullptr;
}

irrklang::ISoundSource* audio_wrapper::IrrklangWrapper::CreateSoundSource(std::string file) {
	irrklang::ISoundSource* src = _soundEngine->addSoundSourceFromFile(file.c_str(), irrklang::ESM_AUTO_DETECT, true);
	if (!src) EDEN_WARNING("No se ha podido crear la fuente de audio con nombre: " + file + ".");
	return src;
}

irrklang::ISound* audio_wrapper::IrrklangWrapper::Play(irrklang::ISoundSource* soundSource, bool loop) {
	irrklang::ISound* sound = _soundEngine->play2D(soundSource, loop, false, true);
	if (!sound) {
		std::string atmp = soundSource->getName();
		std::string err = "No se ha podido reproducir el sonido con nombre: " + atmp + ".";
		EDEN_WARNING(err.c_str());
	}
	return sound;
}

irrklang::ISound* audio_wrapper::IrrklangWrapper::Play(irrklang::ISoundSource* soundSource, eden_utils::Vector3 pos, bool loop) {
	irrklang::ISound* sound = _soundEngine->play3D(soundSource, irrklang::vec3df(pos.GetX(), pos.GetY(), pos.GetZ()), loop, false, true);
	if (!sound) {
		std::string atmp = soundSource->getName();
		std::string err = "No se ha podido reproducir el sonido con nombre: " + atmp + ".";
		EDEN_WARNING(err.c_str());
	}
	return sound;
}