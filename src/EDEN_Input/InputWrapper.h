#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_INPUT_WRAPPER_H
#define EDEN_INPUT_WRAPPER_H

#define SDL_MAIN_HANDLED
#pragma warning(push)
#pragma warning(disable : 26819)
#include <SDL.h>
#pragma warning(pop)

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

#endif //EDEN_INPUT_WRAPPER_H