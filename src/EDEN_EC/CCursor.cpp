#define _CRTDBG_MAP_ALLOC
#include "CCursor.h"
#include <InputManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "CImage.h"
#include "Entity.h"

eden_ec::CCursor::CCursor(float width, float height, std::string texture,int depth) {
	
	 _input = eden_input::InputManager::Instance();
}

void eden_ec::CCursor::Start() {
	_image = _ent->GetComponent<CImage>();
}

eden_ec::CCursor::~CCursor() {
	_image = nullptr;
}

void eden_ec::CCursor::Update(float t) {
	_image->SetPosition(float(_input->GetMousePos().first), float(_input->GetMousePos().second));
}

void eden_ec::CCursor::Init(eden_script::ComponentArguments* args) {
	
	_input = eden_input::InputManager::Instance();
}