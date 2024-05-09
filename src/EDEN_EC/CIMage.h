#ifndef EDEN_C_IMAGE_H
#define EDEN_C_IMAGE_H

#include <string>

#include <UIComponent.h>

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa una im�gen en la UI
	class CImage : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Image
		EDEN_API CImage() = default;

		/// @brief Constructora de la clase Image
		EDEN_API CImage(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Image
		EDEN_API ~CImage();

		/// @brief Metodo que crea la Imagen
		EDEN_API void Create(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		EDEN_API void Start() override {}

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		EDEN_API static std::string GetID() { return "IMAGE"; }
	};
} 

#endif 