#define _CRTDBG_MAP_ALLOC
#include <irrKlang.h>

#include "AudioEngine.h"
#include <ErrorHandler.h>
#include <Vector3.h>

audio_wrapper::AudioEngine::AudioEngine() {
	_soundEngine = irrklang::createIrrKlangDevice();
	if (!_soundEngine) eden_error::ErrorHandler::Instance()->Exception("Sound Engine Failed", "No se ha podido inicializar el sistema de sonido de IrrKlang.");
}

audio_wrapper::AudioEngine::~AudioEngine() {
	_soundEngine->drop();
	_soundEngine = nullptr;
}

irrklang::ISoundSource* audio_wrapper::AudioEngine::CreateSoundSource(std::string file) {
	irrklang::ISoundSource* src = _soundEngine->addSoundSourceFromFile(file.c_str(), irrklang::ESM_AUTO_DETECT, true);
	if (!src) eden_error::ErrorHandler::Instance()->Warning("No se ha podido crear la fuente de audio con nombre: " + file + ".");
	return src;
}

irrklang::ISound* audio_wrapper::AudioEngine::Play(irrklang::ISoundSource* soundSource, bool loop) {
	return _soundEngine->play2D(soundSource, loop, false, true);
}

irrklang::ISound* audio_wrapper::AudioEngine::Play(irrklang::ISoundSource* soundSource, eden_utils::Vector3 pos, bool loop) {
	return _soundEngine->play3D(soundSource, EdenVecToIrrklangVec(pos), loop, false, true);
}

void audio_wrapper::AudioEngine::SetListenerParameters(eden_utils::Vector3 position, eden_utils::Vector3 hearingDirection, eden_utils::Vector3 movingSpeed, eden_utils::Vector3 normal) {
	_soundEngine->setListenerPosition(EdenVecToIrrklangVec(position), EdenVecToIrrklangVec(hearingDirection), EdenVecToIrrklangVec(movingSpeed), EdenVecToIrrklangVec(normal));
}

eden_utils::Vector3 audio_wrapper::AudioEngine::IrrklangVecToEdenVec(irrklang::vec3df vector) {
	return { vector.X, vector.Y, vector.Z };
}

irrklang::vec3df audio_wrapper::AudioEngine::EdenVecToIrrklangVec(eden_utils::Vector3 vector) {
	return { vector.GetX(), vector.GetY(), vector.GetZ() };
}