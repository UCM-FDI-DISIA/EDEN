#include "Image.h"
#include "Entity.h"

const std::string eden_ec::Image::_id = "IMAGE";

eden_ec::Image::Image(Texture* tx) : Component() {
	_transform = nullptr;
	_texture = tx;
	_allowRender = true;
	_rect.x = 0;
}

void eden_ec::Image::Update(float t) {
	Render();
}
void eden_ec::Image::Render() {
	if (_allowRender) {
		_rect.x = _transform->GetPosition().GetX();
		_rect.y = _transform->GetPosition().GetY();
		_rect.w = _transform->GetScale().GetX();
		_rect.h = _transform->GetScale().GetY();
		_texture->render(_rect, 0);
	}
}

void eden_ec::Image::InitComponent() {
	_transform = static_cast<eden_ec::CTransform*>(_ent->GetComponent("TRANSFORM"));
}