#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "CButton.h"
#include <InputManager.h>
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"
#include "CLuaBehaviour.h"

const std::string eden_ec::CButton::_id = "BUTTON";

eden_ec::CButton::CButton(ButtonParams& params) : UIComponent() {

	auto renderManager = eden_render::RenderManager::Instance();
	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();

	int xx = (int) (w * params.xPos / 100);
	int yy = (int) (h * params.yPos / 100);

	params.xPos = xx - (params.width / 2);
	params.yPos = yy - (params.height / 2);


	_iniTex = params.iniTex;
	_hoverTex = params.hoverTex;
	_clickedTex = params.clickedTex;

	CreateImage(params.overlayName, params.xPos, params.yPos,
		params.width, params.height, params.iniTex, params.depth);
	// Posiciones necesarias para el input de rat�n
	// top + height
	_topPosition = (int)params.yPos;
	_bottomPosition = _topPosition + (int)params.height;
	// left + width
	_leftPosition = (int)params.xPos;
	_rightPosition = _leftPosition + (int)params.width;

	_oldScale.first = params.width;
	_oldScale.second = params.height;
}

void eden_ec::CButton::Start() {
	_callback = static_cast<CLuaBehaviour*>(_ent->GetComponent("BEHAVIOUR"));
}

void eden_ec::CButton::Init(eden_script::ComponentArguments* args) {
	auto renderManager = eden_render::RenderManager::Instance();

	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");

	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;

	int width = args->GetValueToInt("Width");
	int height = args->GetValueToInt("Height");

	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	_iniTex = args->GetValueToString("Texture1");
	_hoverTex = args->GetValueToString("Texture2");
	_clickedTex = args->GetValueToString("Texture3");

	CreateImage(args->GetValueToString("OverlayName"),(float)xPos, (float)yPos,
		(float)width, (float)height, _iniTex, args->GetValueToInt("Depth"));

	// Posiciones necesarias para el input de rat�n
	// top + height
	_topPosition = yPos;
	_bottomPosition = _topPosition + height;
	// left + width
	_leftPosition = xPos;
	_rightPosition = _leftPosition + width;

	_oldScale.first = (float)width;
	_oldScale.second = (float)height;

}

void eden_ec::CButton::Update(float deltaTime) {
	if (_oPos.second!=0 && (_oldScale.first != _oWidth || _oldScale.second != _oHeight))ButtonRectUpdate();
	CheckMousePos();
}

void eden_ec::CButton::ButtonRectUpdate() {
	// Posiciones necesarias para el input de rat�n
   // top + height
	_topPosition = (int)_oPos.second;
	_bottomPosition = _topPosition + (int)_oHeight;
	// left + width
	_leftPosition = (int)_oPos.first;
	_rightPosition = _leftPosition + (int)_oWidth;
}

void eden_ec::CButton::OnButtonClick() {

	if (!_hovering)
		return;
	if (!_clicked && _inputManager->IsMouseButtonDown(eden_input::InputManager::LEFT)) {
		_clicked = true;
		if(_currentTex!=_clickedTex)ChangeButtonTexture(_clickedTex);
		_currentTex = _clickedTex;
		if (_callback != nullptr) _callback->OnButtonClick();
	}
}

void eden_ec::CButton::OnButtonReleased() {

	if (!_hovering)
		return;
	if (_clicked) {
		if (_inputManager->IsMouseButtonUp(eden_input::InputManager::LEFT)) {
			_clicked = false;
			if(_currentTex!=_iniTex)ChangeButtonTexture(_iniTex);
			_currentTex = _iniTex;
			if (_callback != nullptr) _callback->OnButtonReleased();
		}
	}
}

void eden_ec::CButton::OnButtonHover() {

	if (!_clicked && _currentTex!=_hoverTex) {
		ChangeButtonTexture(_hoverTex);
		_currentTex = _hoverTex;
	}
}

void eden_ec::CButton::OnButtonUnhover() {

	if (_currentTex != _iniTex) {
		ChangeButtonTexture(_iniTex);
		_currentTex = _iniTex;
	}
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