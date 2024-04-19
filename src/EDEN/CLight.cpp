#include "CLight.h"
#include <ComponentArguments.h>
#include <RenderManager.h>
#include "Entity.h"
#include "Transform.h"
#include "Quaternion.h"
#include "Light.h"

const std::string eden_ec::CLight::_id = "LIGHT";

eden_ec::CLight::~CLight() {
	eden_render::RenderManager::Instance()->RemoveRenderEntity(_ent);
	delete _lightWrapper;
}

void eden_ec::CLight::Init(eden_script::ComponentArguments* args) {
	_lType = args->GetValueToString("LightType");
	_diffuseColor = args->GetValueToVector3("DiffuseColor");
	_specularColor = args->GetValueToVector3("SpecularColor");
	eden_render::RenderManager::Instance()->AddRenderEntity(_ent);
}

void eden_ec::CLight::Update(float dt) {
	SetPosition(_transform->GetPosition());
	SetOrientation(_transform->GetRotation());
}

void eden_ec::CLight::Start() {
	_transform = _ent->GetComponent<eden_ec::CTransform>();
	_lightWrapper = new render_wrapper::Light(_ent->GetEntityID(), _ent->GetSceneID(), _lType, _diffuseColor, _specularColor);
}

void eden_ec::CLight::SetVisibility(bool visibility, bool sceneChanged) {
	if (visibility)
	{
		if (!sceneChanged || (sceneChanged && _lightVisibility)) _lightWrapper->SetVisible(visibility);
	}
	else
	{
		_lightWrapper->SetVisible(visibility);
	}
	if (!sceneChanged) _lightVisibility = visibility;
}

bool eden_ec::CLight::getVisibility() {
	return _lightWrapper->isVisible();
}

void eden_ec::CLight::SetDiffuse(eden_utils::Vector3 color) {
	_lightWrapper->SetDiffuse(color);
}

void eden_ec::CLight::SetSpecular(eden_utils::Vector3 color) {
	_lightWrapper->SetSpecular(color);
}

void eden_ec::CLight::SetDirection(eden_utils::Vector3 dir) {
	_lightWrapper->SetDirection(dir);
}

void eden_ec::CLight::SetOrientation(eden_utils::Quaternion ori) {
	_lightWrapper->SetOrientation(ori);
}

inline void eden_ec::CLight::SetPosition(eden_utils::Vector3 dir) {
	_lightWrapper->SetPosition(dir);
}