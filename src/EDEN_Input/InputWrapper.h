#ifndef __INPUT_WRAPPER_H__
#define __INPUT_WRAPPER_H__

#include <SDL.h>
#undef main

	/// @brief Clase que gestiona los eventos de SDL
	class InputWrapper 
	{
	public:
		InputWrapper();
		~InputWrapper();
		SDL_Event* getEvent();
	private:
		SDL_Event* _event;
	};

#endif __INPUT_WRAPPER_H__