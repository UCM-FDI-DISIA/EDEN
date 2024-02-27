#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__
#include "Singleton.h"

class InputWrapper;

namespace eden_input 
{
	/// <summary>
	/// Clase que gestiona la entrada de datos del usuario.
	/// </summary>
	class InputManager : public Singleton<InputManager>
	{
	public:

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

		friend Singleton<InputManager>;
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
		bool IsMouseButtonDown(MOUSEBUTTON b);

		/// <returns>
		/// True mientras
		/// el botón del ratón esté pulsado
		/// </returns>
		/// <param name="b">: Botón del ratón (macros MOUSEBUTTON)</param>
		bool IsMouseButtonHeld(MOUSEBUTTON b);

		/// <returns>
		/// True en el primer frame
		/// en el que el botón del ratón es liberado
		/// </returns>
		/// <param name="b">: Botón del ratón (macros MOUSEBUTTON)</param>
		bool IsMouseButtonUp(MOUSEBUTTON b);

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

		// singleton/manager functions

		/// <summary>
		/// Actualiza el manager
		/// </summary>
		virtual void Update();

		/// <summary>
		/// Inicializa el manager
		/// </summary>
		void Start();

		/// <summary>
		/// Limpia el manager
		/// </summary>
		void Clean();

		///<summary>
		/// Destructora de la clase
		/// </summary>
		~InputManager();

	protected:
		/// <summary>
		/// Constructora de la clase
		/// </summary>
		InputManager();

	private:

		InputWrapper* _inputWrapper;
	};
}

#endif __INPUT_MANAGER_H__