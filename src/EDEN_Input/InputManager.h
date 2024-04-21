#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_INPUT_MANAGER_H
#define EDEN_INPUT_MANAGER_H

#include <array>
#include <unordered_map>

#include "Singleton.h"

class InputWrapper;
namespace eden_input 
{
	/// @brief Clase que gestiona la entrada de datos del usuario.
	class InputManager : public Singleton<InputManager>
	{
		friend Singleton<InputManager>;
	public:

		/// @brief enumerado de los botones del raton
		enum MOUSEBUTTON : uint8_t { LEFT, MIDDLE, RIGHT };

		/// @brief enumerado de las teclas especiales
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
			SUPR,
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

		/// @brief Limpieza del mapa de teclas
		void Clean();

		/// @brief True si se esta pulsando
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
		/// la tecla esta pulsada
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
		/// la tecla esta pulsada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyHeld(SPECIALKEY key);

		/// @brief True en el primer frame
		/// en el que la tecla es liberada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyUp(SPECIALKEY key);

		/// @brief mouse
		/// @brief True si el raton
		/// ha cambiado de posicion
		bool MouseMotionEvent();

		/// @brief True si al menos un boton
		/// del raton ha cambiado de estado
		bool MouseButtonEvent();

		/// @brief True en el primer frame
		/// en el que el boton del raton es pulsado
		/// @param b Boton del raton (macros MOUSEBUTTON)
		bool IsMouseButtonDown(int b);

		/// @brief True mientras
		/// el boton del raton esta pulsado
		/// @param b Boton del raton (macros MOUSEBUTTON)
		bool IsMouseButtonHeld(int b);

		/// @brief True en el primer frame
		/// en el que el boton del raton es liberado
		/// @param b Boton del raton (macros MOUSEBUTTON)
		bool IsMouseButtonUp(int b);

		/// @brief Par (X, Y) de
		/// la posicion del raton en la pantalla.
		const std::pair<int, int>& GetMousePos();

		//window events

		/// @brief Devuelve true cuando el usuario ha pulsado la X de la ventana
		bool CloseWindowEvent();

		/// @brief Se llama para cerrar la ventana de sdl (en el boto de quit del menu
		/// por ejemplo)
		void SetCloseWindow();

		/// @brief Devuelve true cuando el usuario ha cambiado el tamaño de la ventana
		bool ResizedWindowEvent();

		/// @brief Update
		void Update();

		/// @brief Destructora de la clase
		~InputManager() override;

	private:

		/// @brief Puntero del wrapper (SDL)
		InputWrapper* _wrapper;

		/// @brief Booleano de si se ha dejado de pulsar una tecla
		bool _isKeyUpEvent;

		/// @brief Booleano de si se ha pulsado una tecla
		bool _isKeyDownEvent;

		/// @brief Mapa de teclas y su estado
		std::unordered_map<uint8_t, uint8_t> _kbState;

		/// @brief Booleano de si se ha movido el raton
		bool _isMouseMotionEvent;
		
		/// @brief Booleano de si se ha pulsado algun boton del raton
		bool _isMouseButtonEvent;

		/// @brief Posicion del raton
		std::pair<int, int> _mousePos;

		/// @brief Estado del raton
		std::array<uint8_t, 3> _mbState;

		/// @brief Booleano de si se cierra la ventana
		bool _isCloseWindowEvent;

		/// @brief Booleano de si se cambia el tamanio la ventana
		bool _isResizedWindowEvent;

		/// @brief Estados de botones
		enum STATE : uint8_t {
			RELEASED = 0,
			DOWN = 1,
			HELD = 2,
			UP = 3,
		};

		/// @brief Gestiona el cambio de estados de los botones de teclado, mando y
		/// raton (DOWN -> HELD y UP -> RELEASE). Resetea las flags de los
		/// eventos
		void ClearState();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyDown();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyUp();

		/// @brief Actualiza la posici�n del rat�n
		void OnMouseMotion();

		/// @brief Actualiza el estado de los botones del raton
		void OnMouseButtonChange(STATE state);

		/// @brief Gestiona los eventos de ventana
		void HandleWindowEvent();
		
		/// @brief Constructora de la clase
		InputManager();
	};
}

#endif // __INPUT_MANAGER_H__