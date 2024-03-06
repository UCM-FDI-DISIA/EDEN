#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__
#include "Singleton.h"
#include <SDL.h>
#include <array>
#include <unordered_map>

#undef main
namespace eden_input 
{
	/// @brief Clase que gestiona la entrada de datos del usuario.
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

		/// @brief Constructora de la clase
		InputManager();

		/// @brief Destructora de la clase
		~InputManager();


		void Clean();

		/// @brief keyboard

		/// @brief True si se está pulsando
		/// al menos una tecla del teclado
		bool KeyDownEvent();

		/// @brief True si se ha soltado
		/// al menos una tecla del teclado
		bool KeyUpEvent();

		/// @brief True en el primer frame
		/// en el que la tecla es pulsada
		/// @param key Tecla Normal (0-9 y a-z)
		bool IsKeyDown(char key);

		/// @brief True mientras
		/// la tecla esté pulsada
		/// @param key Tecla Normal (0-9 y a-z)
		bool IsKeyHeld(char key);

		/// @brief True en el primer frame
		/// en el que la tecla es liberada
		/// @param key Tecla Normal (0-9 y a-z)
		bool IsKeyUp(char key);

		/// @brief True en el primer frame
		/// en el que la tecla es pulsada
		/// @param key Tecla Especial (macros SPECIALKEY)
		bool IsKeyDown(SPECIALKEY key);

		/// @brief True mientras
		/// la tecla esté pulsada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyHeld(SPECIALKEY key);

		/// @brief True en el primer frame
		/// en el que la tecla es liberada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyUp(SPECIALKEY key);

		/// @brief mouse

		/// @brief True si el ratón
		/// ha cambiado de posición
		bool MouseMotionEvent();

		/// @brief True si al menos un botón
		/// del ratón ha cambiado de estado
		bool MouseButtonEvent();

		/// @brief True en el primer frame
		/// en el que el botón del ratón es pulsado
		/// @param b Botón del ratón (macros MOUSEBUTTON)
		bool IsMouseButtonDown(int b);

		/// @brief True mientras
		/// el botón del ratón esté pulsado
		/// @param b Botón del ratón (macros MOUSEBUTTON)
		bool IsMouseButtonHeld(int b);

		/// @brief True en el primer frame
		/// en el que el botón del ratón es liberado
		/// @param b Botón del ratón (macros MOUSEBUTTON)
		bool IsMouseButtonUp(int b);

		/// @brief Par (X, Y) de
		/// la posición del ratón en la pantalla.

		/// @brief (0, 0) está en la esquina superior izquierda.
		/// X es positivo hacia abajo e Y, hacia la derecha

		const std::pair<int, int>& GetMousePos();

		/// @brief window events

		/// @brief Devuelve true cuando el usuario ha pulsado la X de la ventana
		bool CloseWindowEvent();

		/// @brief Se llama para cerrar la ventana de sdl (en el boto de quit del menu
		/// por ejemplo)
		void SetCloseWindow();

		/// @brief Update
		virtual void Update();


	private:

		SDL_Event* _event;

		/// @brief keyboard
		bool _isKeyUpEvent;
		bool _isKeyDownEvent;
		std::unordered_map<uint8_t, uint8_t> _kbState;

		/// @brief mouse
		bool _isMouseMotionEvent;
		bool _isMouseButtonEvent;
		std::pair<int, int> _mousePos;
		std::array<uint8_t, 3> _mbState;

		/// @brief window
		bool _isCloseWindowEvent;

		enum STATE : uint8_t {
			RELEASED = 0,
			DOWN = 1,
			HELD = 2,
			UP = 3,
		};

		/// @brief Gestiona el cambio de estados de los botones de teclado, mando y
		/// ratón (DOWN -> HELD y UP -> RELEASE). Resetea las flags de los
		/// eventos
		void ClearState();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyDown();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyUp();

		/// @brief Actualiza la posición del ratón
		void OnMouseMotion();

		/// @brief Actualiza el estado de los botones del ratón
		void OnMouseButtonChange(STATE state);

		/// @brief Gestiona los eventos de ventana
		void HandleWindowEvent();

	};
}

#endif __INPUT_MANAGER_H__