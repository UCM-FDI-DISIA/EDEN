#include "CCursor.h"
#include "CImage.h"

#include "..\EDEN_Input\InputManager.h"
#include "..\EDEN_Script\ScriptManager.h"
#include "..\EDEN_Script\ComponentArguments.h"

const std::string eden_ec::CCursor::_id = "CURSOR";

eden_ec::CCursor::CCursor(float width, float height, std::string texture,int depth) {
	
	 _input = eden_input::InputManager::Instance();
	_image = new CImage("cursor", _input->GetMousePos().first, _input->GetMousePos().second,
		width, height, texture, depth);

}

void eden_ec::CCursor::InitComponent() {}

eden_ec::CCursor::~CCursor() {
	delete _image;
}

void eden_ec::CCursor::Update(float t) {
	_image->SetPosition(_input->GetMousePos().first, _input->GetMousePos().second);
}

void eden_ec::CCursor::Init(eden_script::ComponentArguments* args) {
	
	_input = eden_input::InputManager::Instance();
	_image = new CImage("cursor", _input->GetMousePos().first, _input->GetMousePos().second,
		args->GetValueToInt("Width"), args->GetValueToInt("Height"),
		args->GetValueToString("Texture"), args->GetValueToInt("Depth"));

}