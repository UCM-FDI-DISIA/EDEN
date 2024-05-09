#include "InputManager.h"
#include "InputWrapper.h"

eden_input::InputManager* eden_input::InputManager::getInstance() {
	return static_cast<InputManager*>(Instance());
}

eden_input::InputManager::InputManager() {

	_wrapper = new InputWrapper();
	_kbState = std::unordered_map<uint8_t, uint8_t>();
	ClearState();
}

eden_input::InputManager::~InputManager() {
	delete _wrapper;
}

void eden_input::InputManager::Clean() {
	_kbState = std::unordered_map<uint8_t, uint8_t>();
}

void eden_input::InputManager::Update() {
	ClearState();
	if (_isActive) {
		while (SDL_PollEvent(_wrapper->getEvent()))
		{
			switch (_wrapper->getEvent()->type)
			{
			case SDL_KEYDOWN:
				OnKeyDown();
				break;
			case SDL_KEYUP:
				OnKeyUp();
				break;
			case SDL_MOUSEMOTION:
				OnMouseMotion();
				break;
			case SDL_MOUSEBUTTONDOWN:
				OnMouseButtonChange(DOWN);
				break;
			case SDL_MOUSEBUTTONUP:
				OnMouseButtonChange(UP);
				break;
			case SDL_WINDOWEVENT:
				HandleWindowEvent();
				break;
			default:
				break;
			}
		}
	}
}

void eden_input::InputManager::SetActive(bool bActive)
{
	_isActive = bActive;
}

bool eden_input::InputManager::KeyDownEvent() { return _isKeyDownEvent; }

bool eden_input::InputManager::KeyUpEvent() { return _isKeyUpEvent; }

bool eden_input::InputManager::IsKeyDown(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == DOWN;
}

bool eden_input::InputManager::IsKeyHeld(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == DOWN ||
		_kbState[SDL_GetScancodeFromKey(key)] == HELD;
}

bool eden_input::InputManager::IsKeyUp(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == UP;
}

bool eden_input::InputManager::IsKeyDown(SPECIALKEY key) {
	return _kbState[(SDL_Scancode)key] == DOWN;
}

bool eden_input::InputManager::IsKeyHeld(SPECIALKEY key) {
	return _kbState[(SDL_Scancode)key] == DOWN ||
		_kbState[(SDL_Scancode)key] == HELD;
}

bool eden_input::InputManager::IsKeyUp(SPECIALKEY key) {
	return _kbState[(SDL_Scancode)key] == UP;
}

bool eden_input::InputManager::MouseMotionEvent() { return _isMouseMotionEvent; }

bool eden_input::InputManager::MouseButtonEvent() { return _isMouseButtonEvent; }

bool eden_input::InputManager::IsMouseButtonDown(int b) {
	return _mbState[b] == DOWN;
}

bool eden_input::InputManager::IsMouseButtonHeld(int b) {
	return _mbState[b] == DOWN || _mbState[b] == HELD;
}

bool eden_input::InputManager::IsMouseButtonUp(int b) {
	return _mbState[b] == UP;
}

const std::pair<int, int>& eden_input::InputManager::GetMousePos() {
	return _mousePos;
}

void eden_input::InputManager::ClearState() {
	_isKeyDownEvent = false;
	_isKeyUpEvent = false;
	_isMouseButtonEvent = false;
	_isMouseMotionEvent = false;
	_isCloseWindowEvent = false;
	_isResizedWindowEvent = false;

	for (auto i = 0u; i < 3; i++) {
		if (_mbState[i] == DOWN)
			_mbState[i] = HELD;
		else if (_mbState[i] == UP)
			_mbState[i] = RELEASED;
	}

	for (auto i = 0u; i < _kbState.size(); i++) {
		if (_kbState[i] == DOWN)
			_kbState[i] = HELD;
		else if (_kbState[i] == UP)
			_kbState[i] = RELEASED;
	}

	_mouseDir = { 0, 0 };
}

void eden_input::InputManager::OnKeyDown() {
	SDL_Scancode key = _wrapper->getEvent()->key.keysym.scancode;
	if (!_kbState.count(key) || _kbState[key] != HELD)
		_kbState[key] = DOWN;

	_isKeyDownEvent = true;
}

void eden_input::InputManager::OnKeyUp() {
	_kbState[_wrapper->getEvent()->key.keysym.scancode] = UP;

	_isKeyUpEvent = true;
}

void eden_input::InputManager::OnMouseMotion() {
	_isMouseMotionEvent = true;

	SDL_Event* event = _wrapper->getEvent();

	_mousePos.first = event->motion.x;
	_mousePos.second = event->motion.y;

	_mouseDir.first = event->motion.xrel;
	_mouseDir.second = event->motion.yrel;
}

void eden_input::InputManager::OnMouseButtonChange(STATE state) {
	_isMouseButtonEvent = true;
	switch (_wrapper->getEvent()->button.button) {
	case SDL_BUTTON_LEFT:
		_mbState[LEFT] = state;
		break;
	case SDL_BUTTON_MIDDLE:
		_mbState[MIDDLE] = state;
		break;
	case SDL_BUTTON_RIGHT:
		_mbState[RIGHT] = state;
		break;
	default:
		break;
	}
}

void eden_input::InputManager::HandleWindowEvent() {
	switch (_wrapper->getEvent()->window.event) {
	case SDL_WINDOWEVENT_CLOSE:
		_isCloseWindowEvent = true;
		break;
	case SDL_WINDOWEVENT_RESIZED:
		_isResizedWindowEvent = true;
		break;
	default:
		break;
	}
}

bool eden_input::InputManager::CloseWindowEvent() { return _isCloseWindowEvent; }

void eden_input::InputManager::SetCloseWindow() { _isCloseWindowEvent = true; }

bool eden_input::InputManager::ResizedWindowEvent() { return _isResizedWindowEvent; }