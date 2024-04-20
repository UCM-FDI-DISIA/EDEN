#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_IMAGE_H
#define EDEN_C_IMAGE_H

#include <string>

#include <UIComponent.h>

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa una imágen en la UI
	class EDEN_API CImage : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Image
		CImage() = default;

		/// @brief Constructora de la clase Image
		CImage(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Image
		~CImage();

		/// @brief Método que crea la Imagen
		void Create(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return "IMAGE"; }
	};
} 

#endif 