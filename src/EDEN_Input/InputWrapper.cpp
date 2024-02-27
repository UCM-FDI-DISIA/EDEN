#include "InputWrapper.h"


	
InputWrapper::InputWrapper(){
	//Inicialiación de SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_event = new SDL_Event();
	_kbState = std::unordered_map<uint8_t, uint8_t>();
	ClearStateWrapper();

	//Creación de ventana temporal para testing
	_window = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
}

InputWrapper::~InputWrapper() {
	SDL_Quit();
	delete _event;
	SDL_DestroyWindow(_window);
}

void InputWrapper::CleanWrapper() {
	_kbState = std::unordered_map<uint8_t, uint8_t>();
}

void InputWrapper::UpdateWrapper() {
	ClearStateWrapper();
	while (SDL_PollEvent(_event))
	{
		switch (_event->type)
		{
		case 4352:
			if (true);
			break;
		case SDL_KEYDOWN:
			OnKeyDownWrapper();
			break;
		case SDL_KEYUP:
			OnKeyUpWrapper();
			break;
		case SDL_MOUSEMOTION:
			OnMouseMotionWrapper();
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonChangeWrapper(DOWN);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonChangeWrapper(UP);
			break;
		case SDL_WINDOWEVENT:
			HandleWindowEventWrapper();
			break;
		default:
			break;
		}
	}
}

bool InputWrapper::KeyDownEventWrapper() { return _isKeyDownEvent; }

bool InputWrapper::KeyUpEventWrapper() { return _isKeyUpEvent; }

bool InputWrapper::IsKeyDownWrapper(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == DOWN;
}

bool InputWrapper::IsKeyHeldWrapper(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == DOWN ||
		_kbState[SDL_GetScancodeFromKey(key)] == HELD;
}

bool InputWrapper::IsKeyUpWrapper(char key) {
	return _kbState[SDL_GetScancodeFromKey(key)] == UP;
}

bool InputWrapper::IsKeyDownWrapper(int key) {
	return _kbState[(SDL_Scancode)key] == DOWN;
}

bool InputWrapper::IsKeyHeldWrapper(int key) {
	return _kbState[(SDL_Scancode)key] == DOWN ||
		_kbState[(SDL_Scancode)key] == HELD;
}

bool InputWrapper::IsKeyUpWrapper(int key) {
	return _kbState[(SDL_Scancode)key] == UP;
}

bool InputWrapper::MouseMotionEventWrapper() { return _isMouseMotionEvent; }

bool InputWrapper::MouseButtonEventWrapper() { return _isMouseButtonEvent; }

bool InputWrapper::IsMouseButtonDownWrapper(int b) {
	return _mbState[b] == DOWN;
}

bool InputWrapper::IsMouseButtonHeldWrapper(int b) {
	return _mbState[b] == DOWN || _mbState[b] == HELD;
}

bool InputWrapper::IsMouseButtonUpWrapper(int b) {
	return _mbState[b] == UP;
}

const std::pair<int, int>& InputWrapper::GetMousePosWrapper() {
	return _mousePos;
}

void InputWrapper::ClearStateWrapper() {
	_isKeyDownEvent = false;
	_isKeyUpEvent = false;
	_isMouseButtonEvent = false;
	_isMouseMotionEvent = false;
	_isCloseWindowEvent = false;

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
}

void InputWrapper::OnKeyDownWrapper() {
	SDL_Scancode key = _event->key.keysym.scancode;
	if (!_kbState.count(key) || _kbState[key] != HELD)
		_kbState[key] = DOWN;

	_isKeyDownEvent = true;
}

void InputWrapper::OnKeyUpWrapper() {
	_kbState[_event->key.keysym.scancode] = UP;

	_isKeyUpEvent = true;
}

void InputWrapper::OnMouseMotionWrapper() {
	_isMouseMotionEvent = true;
	_mousePos.first = _event->motion.x;
	_mousePos.second = _event->motion.y;
}

void InputWrapper::OnMouseButtonChangeWrapper(STATE state) {
	_isMouseButtonEvent = true;
	switch (_event->button.button) {
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

void InputWrapper::HandleWindowEventWrapper() {
	switch (_event->window.event) {
	case SDL_WINDOWEVENT_CLOSE:
		_isCloseWindowEvent = true;
		break;
	default:
		break;
	}
}

bool InputWrapper::CloseWindowEventWrapper() { return _isCloseWindowEvent; }

void InputWrapper::SetCloseWindowWrapper() { _isCloseWindowEvent = true; }