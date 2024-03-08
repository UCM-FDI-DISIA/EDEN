#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <array>
#include <unordered_map>

#include "Singleton.h"

class InputWrapper;
namespace eden_input 
{
	/// @brief Clase que gestiona la entrada de datos del usuario.
	class InputManager : public Singleton<InputManager>
	{
	public:

		friend Singleton<InputManager>;

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

		/// @brief True si se est� pulsando
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
		/// la tecla est� pulsada
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
		/// la tecla est� pulsada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyHeld(SPECIALKEY key);

		/// @brief True en el primer frame
		/// en el que la tecla es liberada
		/// @param key Tecla Normal (macros SPECIALKEY)
		bool IsKeyUp(SPECIALKEY key);

		/// @brief mouse
		/// @brief True si el rat�n
		/// ha cambiado de posici�n
		bool MouseMotionEvent();

		/// @brief True si al menos un bot�n
		/// del rat�n ha cambiado de estado
		bool MouseButtonEvent();

		/// @brief True en el primer frame
		/// en el que el bot�n del rat�n es pulsado
		/// @param b Bot�n del rat�n (macros MOUSEBUTTON)
		bool IsMouseButtonDown(int b);

		/// @brief True mientras
		/// el bot�n del rat�n est� pulsado
		/// @param b Bot�n del rat�n (macros MOUSEBUTTON)
		bool IsMouseButtonHeld(int b);

		/// @brief True en el primer frame
		/// en el que el bot�n del rat�n es liberado
		/// @param b Bot�n del rat�n (macros MOUSEBUTTON)
		bool IsMouseButtonUp(int b);

		/// @brief Par (X, Y) de
		/// la posici�n del rat�n en la pantalla.
		const std::pair<int, int>& GetMousePos();

		//window events

		/// @brief Devuelve true cuando el usuario ha pulsado la X de la ventana
		bool CloseWindowEvent();

		/// @brief Se llama para cerrar la ventana de sdl (en el boto de quit del menu
		/// por ejemplo)
		void SetCloseWindow();

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
		
		/// @brief Booleano de si se ha pulsado alg�n bot�n del raton
		bool _isMouseButtonEvent;

		/// @brief Posicion del raton
		std::pair<int, int> _mousePos;

		/// @brief Estado del raton
		std::array<uint8_t, 3> _mbState;

		/// @brief Booleano de si se cierra la ventana
		bool _isCloseWindowEvent;

		/// @brief Estados de botones
		enum STATE : uint8_t {
			RELEASED = 0,
			DOWN = 1,
			HELD = 2,
			UP = 3,
		};

		/// @brief Gestiona el cambio de estados de los botones de teclado, mando y
		/// rat�n (DOWN -> HELD y UP -> RELEASE). Resetea las flags de los
		/// eventos
		void ClearState();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyDown();

		/// @brief Actualiza el estado de las teclas del teclado
		void OnKeyUp();

		/// @brief Actualiza la posici�n del rat�n
		void OnMouseMotion();

		/// @brief Actualiza el estado de los botones del rat�n
		void OnMouseButtonChange(STATE state);

		/// @brief Gestiona los eventos de ventana
		void HandleWindowEvent();
		

		/// @brief Constructora de la clase
		InputManager();
	};
}

#endif __INPUT_MANAGER_H__