#include "AudioListener.h"
#include "AudioEngine.h"

audio_wrapper::AudioListener::AudioListener(eden_utils::Vector3 position, eden_utils::Vector3 hearingDirection, eden_utils::Vector3 movingSpeed, eden_utils::Vector3 normal) : _listenerPosition(position), _hearingDirection(hearingDirection), _movingSpeed(movingSpeed), _normal(normal) {
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_listenerPosition, _hearingDirection, _movingSpeed, _normal);
}

void audio_wrapper::AudioListener::SetPosition(eden_utils::Vector3 pos) {
	_listenerPosition = pos;
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(pos, _hearingDirection, _movingSpeed, _normal);
}

void audio_wrapper::AudioListener::SetHearingDirection(eden_utils::Vector3 dir) {
	_hearingDirection = dir;
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_listenerPosition, dir, _movingSpeed, _normal);
}

void audio_wrapper::AudioListener::SetMovingSpeed(eden_utils::Vector3 speed) {
	_movingSpeed = speed;
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_listenerPosition, _hearingDirection, speed, _normal);
}

void audio_wrapper::AudioListener::SetNormal(eden_utils::Vector3 normal) {
	_normal = normal;
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_listenerPosition, _hearingDirection, _movingSpeed, normal);
}