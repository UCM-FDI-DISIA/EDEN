#include "CCamera.h"
#include "CameraWrapper.h"
#include "Entity.h"
#include "Transform.h"
#include "Vector3.h"
#include "RenderManager.h"

const std::string eden_render::CCamera::_id = "CAMERA";


eden_render::CCamera::~CCamera() {
	RenderManager::Instance()->removeRenderEntity(_ent);
	delete _cameraWrapper;
	_cameraWrapper = nullptr;
	_transform = nullptr;
}

void eden_render::CCamera::Init(eden_script::ComponentArguments* args) {
	_cameraWrapper = new render_wrapper::CameraWrapper(_ent->GetEntityID());
	_transform = _ent->GetComponent<eden_ec::CTransform>();
	eden_render::RenderManager::Instance()->addRenderEntity(_ent);
}

void eden_render::CCamera::Update(float dt) {
	SetCameraPosition(_transform->GetPosition());
	SetCameraRotation(_transform->GetRotation());
}

void eden_render::CCamera::SetNearClipDistance(float distance) {
	_cameraWrapper->SetNearClipDistance(distance);
}

void eden_render::CCamera::SetFarClipDistance(float distance) {
	_cameraWrapper->SetFarClipDistance(distance);
}

void eden_render::CCamera::SetBackgroundColor(float r, float g, float b, float a) {
	_cameraWrapper->SetBackgroundColor(r, g, b, a);
}

void eden_render::CCamera::SetAutoAspectRatio(bool set) {
	_cameraWrapper->SetAutoAspectRatio(set);
}

void eden_render::CCamera::SetCameraPosition(eden_utils::Vector3 pos) {
	_cameraWrapper->SetCameraPosition(pos);
}

void eden_render::CCamera::SetCameraRotation(eden_utils::Quaternion rot) {
	_cameraWrapper->SetCameraRotation(rot);
}

void eden_render::CCamera::LookAt(eden_utils::Vector3 lookat) {
	_cameraWrapper->LookAt(lookat);
}

eden_utils::Vector3 eden_render::CCamera::GetCameraPosition() const {
	return _cameraWrapper->GetCameraPosition();
}
