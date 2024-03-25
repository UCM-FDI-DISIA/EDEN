#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_CURSOR_H
#define EDEN_C_CURSOR_H

#include "Component.h"

namespace Ogre {
	class Overlay;
}

namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CImage;
	/// @brief Clase que representa el cursor
	class  CCursor: public Component {
	public:
		/// @brief Constructora de la clase Cursor
		CCursor() = default;

		/// @brief Constructora de la clase Cursor
		CCursor(float width,float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Cursor
		~CCursor();

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Método update heredado de component 
		void Update(float deltaTime) override;

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:
		/// @brief Puntero a la imagen que representa el cursor
		eden_ec::CImage* _image;

		/// @brief Puntero al InputManager
		eden_input::InputManager* _input;
	};
}

#endif 