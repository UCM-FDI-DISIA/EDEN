#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_TEXT_H
#define EDEN_C_TEXT_H

#include <string>

#include <UIComponent.h>

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa un texto en la UI
	class CText : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Texto
		CText() = default;

		/// @brief Constructora de la clase Texto
		CText(std::string overlayName, float xPos, float yPos, float tam,
			std::string text, std::string font, float rColor,float gColor, float bColor, int depth = 0);

		/// @brief Destructora de la clase Texto
		~CText();

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;
	};
} 

#endif 