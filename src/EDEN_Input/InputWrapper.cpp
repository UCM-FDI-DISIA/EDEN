#define _CRTDBG_MAP_ALLOC
#include "InputWrapper.h"

InputWrapper::InputWrapper() {
	_event = new SDL_Event();
}

InputWrapper::~InputWrapper() {
	delete _event;
}

SDL_Event* InputWrapper::getEvent() {
	return _event;
}