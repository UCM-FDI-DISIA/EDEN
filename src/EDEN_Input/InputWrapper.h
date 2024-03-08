#ifndef __INPUT_WRAPPER_H__
#define __INPUT_WRAPPER_H__

#include <SDL.h>
#undef main

	/// @brief Clase que gestiona los eventos de SDL
	class InputWrapper 
	{
	public:
		/// @brief Constructora por defecto de la clase InputWrapper
		InputWrapper();

		/// @brief Destructora por defecto de la clase InputWrapper
		~InputWrapper();

		/// @brief Metodo que devuelve el evento de SDL
		/// @return puntero a un evento de SDL
		SDL_Event* getEvent();
	private:
		/// @brief Evento de SDL que guarda el wrapper de input
		SDL_Event* _event;
	};

#endif __INPUT_WRAPPER_H__