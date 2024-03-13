#include "CButton.h"

#include "Entity.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ScriptManager.h"
#include "ComponentArguments.h"
#include <iostream>

const std::string eden_ec::CButton::_id = "BUTTON";

eden_ec::CButton::CButton(ButtonParams& params) : UIComponent() {

	auto renderManager = eden_render::RenderManager::Instance();
	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();

	int xx = w * params.xPos / 100;
	int yy = h * params.yPos / 100;

	params.xPos = xx - (params.width / 2);
	params.yPos = yy - (params.height / 2);

	_iniTex = params.iniTex;
	_hoverTex = params.hoverTex;
	_clickedTex = params.clickedTex;

	CreateImage(params.overlayName, params.xPos, params.yPos,
		params.width, params.height, params.iniTex, params.depth);
	// Posiciones necesarias para el input de rat�n
	// top + height
	_topPosition = params.yPos;
	_bottomPosition = _topPosition + params.height;
	// left + width
	_leftPosition = params.xPos;
	_rightPosition = _leftPosition + params.width;

	_oldScale.first = params.width;
	_oldScale.second = params.height;
}

eden_ec::CButton::~CButton() {
}

void eden_ec::CButton::Init(eden_script::ComponentArguments* args) {
	auto renderManager = eden_render::RenderManager::Instance();
	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int width = args->GetValueToInt("Width");
	int height = args->GetValueToInt("Height");

	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;

	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	_iniTex = args->GetValueToString("Texture1");
	_hoverTex = args->GetValueToString("Texture2");
	_clickedTex = args->GetValueToString("Texture3");

	CreateImage(args->GetValueToString("OverlayName"),xPos, yPos,
		width, height, _iniTex, args->GetValueToInt("Depth"));

	// Posiciones necesarias para el input de rat�n
	// top + height
	_topPosition = yPos;
	_bottomPosition = _topPosition + height;
	// left + width
	_leftPosition = xPos;
	_rightPosition = _leftPosition + width;

	_oldScale.first = width;
	_oldScale.second = height;

}

void eden_ec::CButton::Update(float deltaTime) {
	if (_oPos.second!=0 && (_oldScale.first != _oWidth || _oldScale.second != _oHeight))ButtonRectUpdate();
	CheckMousePos();
}

void eden_ec::CButton::ButtonRectUpdate() {
	// Posiciones necesarias para el input de rat�n
   // top + height
	_topPosition = _oPos.second;
	_bottomPosition = _topPosition + _oHeight;
	// left + width
	_leftPosition = _oPos.first;
	_rightPosition = _leftPosition + _oWidth;
}

void eden_ec::CButton::OnButtonClick() {

	if (!_hovering)
		return;
	if (!_clicked && _inputManager->IsMouseButtonDown(eden_input::InputManager::LEFT)) {
		_clicked = true;
		ChangeButtonTexture(_clickedTex);
	}
}

void eden_ec::CButton::OnButtonReleased() {

	if (!_hovering)
		return;
	if (_clicked) {
		if (_inputManager->IsMouseButtonUp(eden_input::InputManager::LEFT)) {
			_clicked = false;
			ChangeButtonTexture(_iniTex);
		}
	}
}

void eden_ec::CButton::OnButtonHover() {

	if (!_clicked)
		ChangeButtonTexture(_hoverTex);
}

void eden_ec::CButton::OnButtonUnhover() {

	ChangeButtonTexture(_iniTex);
}

void eden_ec::CButton::CheckMousePos()
{
	if (!IsVisible())
		return;

	std::pair<int, int> mousePosition = _inputManager->GetMousePos();

	if (mousePosition.first < _rightPosition &&
		mousePosition.first > _leftPosition &&
		mousePosition.second > _topPosition &&
		mousePosition.second < _bottomPosition) {
		_hovering = true;
		OnButtonHover();
		OnButtonClick();
		OnButtonReleased();

	}
	else {
		_hovering = false;
		_clicked = false;
		OnButtonUnhover();
	}
}

void eden_ec::CButton::ChangeButtonTexture(const std::string& textureName) {

	if (textureName == std::string())
		return;
	std::string newTex = "";
	if (textureName == _iniTex) {
		newTex = _iniTex;
	}
	else if (textureName == _hoverTex) {
		newTex = _hoverTex;

	}
	else {
		newTex = _clickedTex;
	}

	SetMaterial(newTex);
}

void eden_ec::CButton::ChangeTextures(const std::string& iniTex,
	const std::string& hoverTex,
	const std::string& clickedTex) {

	_iniTex = iniTex;
	_hoverTex = hoverTex;
	_clickedTex = clickedTex;
}