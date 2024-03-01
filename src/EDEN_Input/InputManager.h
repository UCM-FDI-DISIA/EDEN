#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__
#include "Singleton.h"
#include <SDL.h>
#include <array>
#include <unordered_map>

#undef main
namespace eden_input 
{
	/// <summary>
	/// Clase que gestiona la entrada de datos del usuario.
	/// </summary>
	class InputManager : public Singleton<InputManager>
	{
	public:

		friend Singleton<InputManager>;

		enum MOUSEBUTTON : uint8_t { LEFT = 0, MIDDLE = 1, RIGHT = 2 };
		enum SPECIALKEY : uint8_t {
			RETURN = 40,
			ESCAPE,
			BACKSPACE,
			TAB,
			SPACE,
			MINUS,
			EQUALS,
			LEFTBRACKET,
			RIGHTBRACKET,
			BACKSLASH,
			NONUSHASH,
			SEMICOLON,
			APOSTROPHE,
			GRAVE,
			COMMA,
			PERIOD,
			SLASH,
			CAPSLOCK,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			PRINTSCREEN,
			SCROLLLOCK,
			PAUSE,
			INSERT,
			HOME,
			PAGEUP,
			DELETE,
			END,
			PAGEDOWN,
			ARROW_RIGHT,
			ARROW_LEFT,
			ARROW_DOWN,
			ARROW_UP,
			NUMLOCKCLEAR,
			KP_DIVIDE,
			KP_MULTIPLY,
			KP_MINUS,
			KP_PLUS,

			LCTRL = 224,
			LSHIFT = 225,
			LALT = 226,
			RCTRL = 228,
			RSHIFT = 229,
			RALT = 230
		};
		/// <summary>
		/// Constructora de la clase
		/// </summary>
		InputManager();

		/// <summary>
		/// Destructora de la clase
		///	</summary>
		~InputManager();


		void Clean();

		// keyboard

		/// <returns>
		/// True si se está pulsando
		/// al menos una tecla del teclado
		/// </returns>
		bool KeyDownEvent();

		/// <returns>
		/// True si se ha soltado
		/// al menos una tecla del teclado
		/// </returns>
		bool KeyUpEvent();

		/// <returns>
		/// True en el primer frame
		/// en el que la tecla es pulsada
		/// </returns>
		/// <param name="key">: Tecla Normal (0-9 y a-z)</param>
		bool IsKeyDown(char key);

		/// <returns>
		/// True mientras
		/// la tecla esté pulsada
		/// </returns>
		/// <param name="key">: Tecla Normal (0-9 y a-z)</param>
		bool IsKeyHeld(char key);

		/// <returns>
		/// True en el primer frame
		/// en el que la tecla es liberada
		/// </returns>
		/// <param name="key">: Tecla Normal (0-9 y a-z)</param>
		bool IsKeyUp(char key);

		/// <returns>
		/// True en el primer frame
		/// en el que la tecla es pulsada
		/// </returns>
		/// <param name="key">: Tecla Especial (macros SPECIALKEY)</param>
		bool IsKeyDown(SPECIALKEY key);

		/// <returns>
		/// True mientras
		/// la tecla esté pulsada
		/// </returns>
		/// <param name="key">: Tecla Normal (macros SPECIALKEY)</param>
		bool IsKeyHeld(SPECIALKEY key);

		/// <returns>
		/// True en el primer frame
		/// en el que la tecla es liberada
		/// </returns>
		/// <param name="key">: Tecla Normal (macros SPECIALKEY)</param>
		bool IsKeyUp(SPECIALKEY key);

		// mouse

		/// <returns>
		/// True si el ratón
		/// ha cambiado de posición
		/// </returns>
		bool MouseMotionEvent();

		/// <returns>
		/// True si al menos un botón
		/// del ratón ha cambiado de estado
		/// </returns>
		bool MouseButtonEvent();

		/// <returns>
		/// True en el primer frame
		/// en el que el botón del ratón es pulsado
		/// </returns>
		/// <param name="b">: Botón del ratón (macros MOUSEBUTTON)</param>
		bool IsMouseButtonDown(int b);

		/// <returns>
		/// True mientras
		/// el botón del ratón esté pulsado
		/// </returns>
		/// <param name="b">: Botón del ratón (macros MOUSEBUTTON)</param>
		bool IsMouseButtonHeld(int b);

		/// <returns>
		/// True en el primer frame
		/// en el que el botón del ratón es liberado
		/// </returns>
		/// <param name="b">: Botón del ratón (macros MOUSEBUTTON)</param>
		bool IsMouseButtonUp(int b);

		/// <returns>
		/// Par (X, Y) de
		/// la posición del ratón en la pantalla.
		/// </returns>
		/// <summary>
		/// (0, 0) está en la esquina superior izquierda.
		/// X es positivo hacia abajo e Y, hacia la derecha
		/// </summary>
		const std::pair<int, int>& GetMousePos();

		// window events

		/// <summary>
		/// Devuelve true cuando el usuario ha pulsado la X de la ventana
		/// </summary>
		bool CloseWindowEvent();
		/// <summary>
		/// Se llama para cerrar la ventana de sdl (en el boto de quit del menu
		/// por ejemplo)
		/// </summary>
		void SetCloseWindow();

		// singleton/manager functions

		/// <summary>
		/// 
		/// </summary>
		virtual void Update();


	private:

		SDL_Event* _event;

		// keyboard
		bool _isKeyUpEvent;
		bool _isKeyDownEvent;
		std::unordered_map<uint8_t, uint8_t> _kbState;

		// mouse
		bool _isMouseMotionEvent;
		bool _isMouseButtonEvent;
		std::pair<int, int> _mousePos;
		std::array<uint8_t, 3> _mbState;

		// window
		bool _isCloseWindowEvent;

		SDL_Window* _window;

		enum STATE : uint8_t {
			RELEASED = 0,
			DOWN = 1,
			HELD = 2,
			UP = 3,
		};

		/// <summary>
		/// Gestiona el cambio de estados de los botones de teclado, mando y
		/// ratón (DOWN -> HELD y UP -> RELEASE). Resetea las flags de los
		/// eventos
		/// </summary>
		void ClearState();

		/// <summary>
		/// Actualiza el estado de las teclas del teclado
		/// </summary>
		void OnKeyDown();

		/// <summary>
		/// Actualiza el estado de las teclas del teclado
		/// </summary>
		void OnKeyUp();

		/// <summary>
		/// Actualiza la posición del ratón
		/// </summary>
		void OnMouseMotion();

		/// <summary>
		/// Actualiza el estado de los botones del ratón
		/// </summary>
		void OnMouseButtonChange(STATE state);


		/// <summary>
		/// Gestiona los eventos de ventana
		/// </summary>
		void HandleWindowEvent();

	};
}

#endif __INPUT_MANAGER_H__