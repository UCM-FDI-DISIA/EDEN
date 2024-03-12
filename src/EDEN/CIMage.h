
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UIComponent.h"
#include <string>

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa una imágen en la UI
	class  CImage : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Image
		CImage()= default;

		/// @brief Constructora de la clase Image
		CImage(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);


		/// @brief Destructora de la clase Image
		~CImage();

		/// @brief Inicializa el componente
		void InitComponent() override;

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:
		/// @brief Textura de la imagen 
		std::string _texture;
	};
} 

#endif 