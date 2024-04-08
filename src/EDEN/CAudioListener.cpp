#include "CAudioListener.h"
#include "AudioEngine.h"
#include "Transform.h"
#include "Entity.h"

const std::string eden_ec::CAudioListener::_id = "AUDIO_LISTENER";

void eden_ec::CAudioListener::Start() {
	_transform = _ent->GetComponent<CTransform>();
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_transform->GetPosition(), _transform->GetForward(), {0,0,0}, _transform->GetUp());
}

void eden_ec::CAudioListener::Update(float t) {
	audio_wrapper::AudioEngine::Instance()->SetListenerParameters(_transform->GetPosition(), _transform->GetForward(), { 0,0,0 }, _transform->GetUp());
}