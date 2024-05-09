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
	class EDEN_API CImage : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Image
		CImage() = default;

		/// @brief Constructora de la clase Image
		CImage(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Image
		~CImage();

		/// @brief Metodo que crea la Imagen
		void Create(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return "IMAGE"; }
	};
} 

#endif 