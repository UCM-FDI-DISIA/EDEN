#ifndef CURSOR_H
#define CURSOR_H

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

		/// @brief Inicializa el componente
		void InitComponent() override;

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief M�todo update heredado de component 
		void Update(float deltaTime) override;

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }
	protected:
		/// @brief Identificador del cursor
		const static std::string _id;

	private:
		/// @brief Puntero a la imagen que representa el cursor
		eden_ec::CImage* _image;

		/// @brief Puntero al InputManager
		eden_input::InputManager* _input;
	};
}

#endif /*CURSOR_H*/