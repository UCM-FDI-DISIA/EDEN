#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_CURSOR_H
#define EDEN_C_CURSOR_H

#include "Component.h"

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CImage;
	/// @brief Clase que representa el cursor
	class EDEN_API CCursor: public Component {
	public:
		/// @brief Constructora de la clase Cursor
		CCursor() = default;

		/// @brief Constructora de la clase Cursor
		CCursor(float width,float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Cursor
		~CCursor();

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		void Start() override;

		/// @brief M�todo update heredado de component 
		void Update(float deltaTime) override;

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return "CURSOR"; }

	private:
		/// @brief Puntero a la imagen que representa el cursor
		eden_ec::CImage* _image = nullptr;

		/// @brief Puntero al InputManager
		eden_input::InputManager* _input = nullptr;
	};
}

#endif 