#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "CButton.h"
#include <InputManager.h>
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"
#include "CLuaBehaviour.h"

eden_ec::CButton::CButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth) : UIComponent() {
	if (_ent != nullptr)Register(_ent->GetSceneID());
	ButtonParams params;
	params.overlayName = overlayName;
	params.xPos = xPos;
	params.yPos = yPos;
	params.width = width;
	params.height = height;
	params.iniTex = iniTex;
	params.hoverTex = hoverTex;
	params.clickedTex = clickedTex;
	params.depth = depth;
	CreateButton(params);
}

void eden_ec::CButton::CreateButton(ButtonParams& params) {

	

	auto renderManager = eden_render::RenderManager::Instance();
	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();


	if (params.width > 100)params.width = 100;
	else if (params.width < 0)params.width = 0;
	params.width = w * (params.width / 100);

	if (params.height > 100)params.height = 100;
	else if (params.height < 0)params.height = 0;
	params.height = h * (params.height / 100);

	if (params.xPos > 100)params.xPos = 100;
	else if (params.xPos < 0)params.xPos = 0;
	int xx = w * (params.xPos / 100);

	if (params.yPos > 100)params.yPos = 100;
	else if (params.yPos < 0)params.yPos = 0;
	int yy = h * (params.yPos / 100);

	params.xPos = xx - (params.width / 2);
	params.yPos = yy - (params.height / 2);

	_iniTex = params.iniTex;
	_hoverTex = params.hoverTex;
	_clickedTex = params.clickedTex;

	CreateImage(params.overlayName, params.xPos, params.yPos,
		params.width, params.height, params.iniTex, params.depth);
	// Posiciones necesarias para el input de raton
	// top + height
	_topPosition = (int)params.yPos;
	_bottomPosition = _topPosition + (int)params.height;
	// left + width
	_leftPosition = (int)params.xPos;
	_rightPosition = _leftPosition + (int)params.width;

	_oldScale.first = params.width;
	_oldScale.second = params.height;

	_oldPos.first = params.xPos;
	_oldPos.second = params.yPos;
}

void eden_ec::CButton::Start() {
	_callback = _ent->GetComponent<CLuaBehaviour>();
}

void eden_ec::CButton::Init(eden_script::ComponentArguments* args) {

	ButtonParams params;

	params.xPos = args->GetValueToInt("XPos");
	params.yPos = args->GetValueToInt("YPos");

	params.width = args->GetValueToInt("Width");
	params.height = args->GetValueToInt("Height");

	params.iniTex = args->GetValueToString("Texture1");
	params.hoverTex = args->GetValueToString("Texture2");
	params.clickedTex = args->GetValueToString("Texture3");

	params.overlayName = args->GetValueToString("OverlayName");
	params.depth = args->GetValueToInt("Depth");

	CreateButton(params);
	Register(_ent->GetSceneID());
}

void eden_ec::CButton::SetCallBack()
{
	_callback = static_cast<CLuaBehaviour*>(_ent->GetComponent("BEHAVIOUR"));
}

void eden_ec::CButton::Update(float deltaTime) {
	if (_oPos.second != 0 && (_oldScale.first != _oWidth || _oldScale.second != _oHeight || _oldPos.first != _oPos.first || _oldPos.second != _oPos.second)) {

		ButtonRectUpdate();
	}
	CheckMousePos();
}

void eden_ec::CButton::ButtonRectUpdate() {
	// Posiciones necesarias para el input de raton
   // top + height
	_topPosition = (int)_oPos.second;
	_bottomPosition = _topPosition + (int)_oHeight;
	// left + width
	_leftPosition = (int)_oPos.first;
	_rightPosition = _leftPosition + (int)_oWidth;

	_oldScale.first = _oWidth;
	_oldScale.second = _oHeight;
}

void eden_ec::CButton::OnButtonClick() {

	if (!_hovering)
		return;
	if (!_clicked && _inputManager->IsMouseButtonDown(eden_input::InputManager::LEFT)) {
		_clicked = true;
		if(_currentTex!=_clickedTex)ChangeButtonTexture(_clickedTex);
		_currentTex = _clickedTex;
		if (_callback != nullptr) _callback->OnButtonClick(_ent);
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
			if (_callback != nullptr) _callback->OnButtonReleased(_ent);
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