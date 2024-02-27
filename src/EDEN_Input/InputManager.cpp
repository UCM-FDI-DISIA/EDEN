#include "InputManager.h"
#include "InputWrapper.h"

void eden_input::InputManager::Start() {
	//Manager::start();

	/*lua_State* L = LuaManager::getInstance()->getLuaState();
	luabridge::getGlobalNamespace(L)
		.beginClass<InputManager>("InputManager")
		.addFunction("setCloseWindow", &InputManager::setCloseWindow)
		.endClass();

	luabridge::setGlobal(L, this, "InputManager");*/
}

void eden_input::InputManager::Clean() {
	//Separity::Manager::clean();
	_inputWrapper->CleanWrapper();
}

eden_input::InputManager::~InputManager() {
	delete _inputWrapper;
}

eden_input::InputManager::InputManager() {
	_inputWrapper = new InputWrapper();

	//getInstance()->addManager(_INPUT, this);
	//mustStart_ = true;
}

void eden_input::InputManager::Update() { _inputWrapper->UpdateWrapper();}

bool eden_input::InputManager::KeyDownEvent() { return _inputWrapper->KeyDownEventWrapper(); }

bool eden_input::InputManager::KeyUpEvent() { return _inputWrapper->KeyUpEventWrapper(); }

bool eden_input::InputManager::IsKeyDown(char key) { return _inputWrapper->IsKeyDownWrapper(key);}

bool eden_input::InputManager::IsKeyHeld(char key) { return _inputWrapper->IsKeyHeldWrapper(key);}

bool eden_input::InputManager::IsKeyUp(char key) { return _inputWrapper->IsKeyHeldWrapper(key);}

bool eden_input::InputManager::IsKeyDown(SPECIALKEY key) { return _inputWrapper->IsKeyDownWrapper(key);}

bool eden_input::InputManager::IsKeyHeld(SPECIALKEY key) { return _inputWrapper->IsKeyHeldWrapper(key);}

bool eden_input::InputManager::IsKeyUp(SPECIALKEY key) { return _inputWrapper->IsKeyUpWrapper(key);}

bool eden_input::InputManager::MouseMotionEvent() { return _inputWrapper->MouseMotionEventWrapper(); }

bool eden_input::InputManager::MouseButtonEvent() { return _inputWrapper->MouseButtonEventWrapper(); }

bool eden_input::InputManager::IsMouseButtonDown(MOUSEBUTTON b) { return _inputWrapper->IsMouseButtonDownWrapper(b); }

bool eden_input::InputManager::IsMouseButtonHeld(MOUSEBUTTON b) { return _inputWrapper->IsMouseButtonHeldWrapper(b);}

bool eden_input::InputManager::IsMouseButtonUp(MOUSEBUTTON b) {	return _inputWrapper->IsMouseButtonUpWrapper(b);}

const std::pair<int, int>& eden_input::InputManager::GetMousePos() { return _inputWrapper->GetMousePosWrapper();}

bool eden_input::InputManager::CloseWindowEvent() { return _inputWrapper->CloseWindowEventWrapper(); }