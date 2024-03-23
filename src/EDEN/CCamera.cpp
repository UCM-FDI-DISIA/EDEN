#include "CCamera.h"
#include <CameraWrapper.h>
#include <RenderManager.h>
#include "Entity.h"
#include "Transform.h"
#include "Vector3.h"

const std::string eden_ec::CCamera::_id = "CAMERA";


eden_ec::CCamera::~CCamera() {
	eden_render::RenderManager::Instance()->removeRenderEntity(_ent);
	delete _cameraWrapper;
	_cameraWrapper = nullptr;
	_transform = nullptr;
}

void eden_ec::CCamera::Start() {
	_transform = _ent->GetComponent<eden_ec::CTransform>();
	_cameraWrapper = new render_wrapper::CameraWrapper(_ent->GetEntityID());
	eden_render::RenderManager::Instance()->addRenderEntity(_ent);
}

void eden_ec::CCamera::Update(float dt) {
	SetCameraPosition(_transform->GetPosition());
	SetCameraRotation(_transform->GetRotation());
}

void eden_ec::CCamera::SetNearClipDistance(float distance) {
	_cameraWrapper->SetNearClipDistance(distance);
}

void eden_ec::CCamera::SetFarClipDistance(float distance) {
	_cameraWrapper->SetFarClipDistance(distance);
}

void eden_ec::CCamera::SetBackgroundColor(float r, float g, float b, float a) {
	_cameraWrapper->SetBackgroundColor(r, g, b, a);
}

void eden_ec::CCamera::SetAutoAspectRatio(bool set) {
	_cameraWrapper->SetAutoAspectRatio(set);
}

void eden_ec::CCamera::SetCameraPosition(eden_utils::Vector3 pos) {
	_cameraWrapper->SetCameraPosition(pos);
}

void eden_ec::CCamera::SetCameraRotation(eden_utils::Quaternion rot) {
	_cameraWrapper->SetCameraRotation(rot);
}

void eden_ec::CCamera::LookAt(eden_utils::Vector3 lookat) {
	_cameraWrapper->LookAt(lookat);
}

eden_utils::Vector3 eden_ec::CCamera::GetCameraPosition() const {
	return _cameraWrapper->GetCameraPosition();
}
