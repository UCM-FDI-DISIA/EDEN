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
	CreateButton(overlayName, xPos, yPos, width, height, iniTex, hoverTex,clickedTex,depth);
}

void eden_ec::CButton::CreateButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth) {

	

	auto renderManager = eden_render::RenderManager::Instance();
	int w = renderManager->GetWindowWidth();
	int h = renderManager->GetWindowHeight();


	if (width > 100)width = 100;
	else if (width < 0)width = 0;
	width = w * (width / 100);

	if (height > 100)height = 100;
	else if (height < 0)height = 0;
	height = h * (height / 100);

	if (xPos > 100)xPos = 100;
	else if (xPos < 0)xPos = 0;
	int xx = w * (xPos / 100);

	if (yPos > 100)yPos = 100;
	else if (yPos < 0)yPos = 0;
	int yy = h * (yPos / 100);

	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	_iniTex = iniTex;
	_hoverTex = hoverTex;
	_clickedTex = clickedTex;

	CreateImage(overlayName, xPos, yPos,
		width, height, iniTex, depth);
	// Posiciones necesarias para el input de rat�n
	// top + height
	_topPosition = (int)yPos;
	_bottomPosition = _topPosition + (int)height;
	// left + width
	_leftPosition = (int)xPos;
	_rightPosition = _leftPosition + (int)width;

	_oldScale.first = width;
	_oldScale.second = height;
}

void eden_ec::CButton::Start() {
	_callback = _ent->GetComponent<CLuaBehaviour>();
}

void eden_ec::CButton::Init(eden_script::ComponentArguments* args) {

	float xPos = args->GetValueToInt("XPos");
	float yPos = args->GetValueToInt("YPos");

	float width = args->GetValueToInt("Width");
	float height = args->GetValueToInt("Height");

	std::string iniTex = args->GetValueToString("Texture1");
	std::string hoverTex = args->GetValueToString("Texture2");
	std::string clickedTex = args->GetValueToString("Texture3");

	std::string overlayName = args->GetValueToString("OverlayName");
	int depth = args->GetValueToInt("Depth");

	CreateButton(overlayName, xPos,  yPos,  width,  height,  iniTex,  hoverTex,  clickedTex,  depth);
	Register(_ent->GetSceneID());
}

void eden_ec::CButton::SetCallBack()
{
	_callback = static_cast<CLuaBehaviour*>(_ent->GetComponent("BEHAVIOUR"));
}

void eden_ec::CButton::Update(float deltaTime) {
	if (_oPos.second!=0 && (_oldScale.first != _oWidth || _oldScale.second != _oHeight))
		ButtonRectUpdate();
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