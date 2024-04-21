#define _CRTDBG_MAP_ALLOC
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
	class EDEN_API CText : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Texto
		CText() = default;

		/// @brief Constructora de la clase Texto
		CText(std::string overlayName, float xPos, float yPos, float tam,
			std::string text, std::string font, float rColor,float gColor, float bColor, int depth = 0);

		/// @brief Destructora de la clase Texto
		~CText();

		/// @brief Metodo que crea Texto
		void Create(std::string overlayName, float xPos, float yPos, float tam,
			std::string text, std::string font, float rColor, float gColor, float bColor, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Devuelve el texto actual
		std::string GetCurrentText();

		/// @brief Cambia el texto actual
		void SetNewText(const std::string& text);

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;
	};
} 

#endif 