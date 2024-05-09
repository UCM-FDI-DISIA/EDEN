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
	class CCursor: public Component {
	public:
		/// @brief Constructora de la clase Cursor
		EDEN_API CCursor() = default;

		/// @brief Constructora de la clase Cursor
		EDEN_API CCursor(float width,float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Cursor
		EDEN_API ~CCursor();

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		EDEN_API void Start() override;

		/// @brief Metodo update heredado de component 
		EDEN_API void Update(float deltaTime) override;

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		EDEN_API static std::string GetID() { return "CURSOR"; }

	private:
		/// @brief Puntero a la imagen que representa el cursor
		eden_ec::CImage* _image = nullptr;

		/// @brief Puntero al InputManager
		eden_input::InputManager* _input = nullptr;
	};
}

#endif 