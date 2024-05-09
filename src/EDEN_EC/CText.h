#ifndef EDEN_C_TEXT_H
#define EDEN_C_TEXT_H

#include <string>

#include <UIComponent.h>

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa un texto en la UI
	class CText : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Texto
		EDEN_API CText() = default;

		/// @brief Constructora de la clase Texto
		EDEN_API CText(std::string overlayName, float xPos, float yPos, float tam,
			std::string text, std::string font, float rColor,float gColor, float bColor, int depth = 0);

		/// @brief Destructora de la clase Texto
		EDEN_API ~CText();

		/// @brief Metodo que crea Texto
		EDEN_API void Create(std::string overlayName, float xPos, float yPos, float tam,
			std::string text, std::string font, float rColor, float gColor, float bColor, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		EDEN_API void Start() override {}

		/// @brief Devuelve el texto actual
		EDEN_API std::string GetCurrentText();

		/// @brief Cambia el texto actual
		EDEN_API void SetNewText(const std::string& text, bool resize = true);

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		EDEN_API static std::string GetID() { return "TEXT"; }
	};
} 

#endif 