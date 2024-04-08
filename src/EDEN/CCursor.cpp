#define _CRTDBG_MAP_ALLOC
#include "CCursor.h"
#include <InputManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "CImage.h"
#include "Entity.h"

const std::string eden_ec::CCursor::_id = "CURSOR";

eden_ec::CCursor::CCursor(float width, float height, std::string texture,int depth) {
	
	 _input = eden_input::InputManager::Instance();
	_image = new CImage("cursor", float(_input->GetMousePos().first), float(_input->GetMousePos().second),
		width, height, texture, depth);

}

eden_ec::CCursor::~CCursor() {
	delete _image;
}

void eden_ec::CCursor::Update(float t) {
	_image->SetPosition(float(_input->GetMousePos().first), float(_input->GetMousePos().second));
}

void eden_ec::CCursor::Init(eden_script::ComponentArguments* args) {
	
	_input = eden_input::InputManager::Instance();
	_image = new CImage("cursor", float(_input->GetMousePos().first), float(_input->GetMousePos().second),
		float(args->GetValueToInt("Width")), float(args->GetValueToInt("Height")),
		args->GetValueToString("Texture"), args->GetValueToInt("Depth"));
	_image->Register(_ent->GetSceneID());

}