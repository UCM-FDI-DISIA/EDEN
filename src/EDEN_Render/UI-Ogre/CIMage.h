#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UIComponent.h"
#include <string>

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// <summary>
	/// Clase que representa una imágen en la UI
	/// </summary>
	class  CImage : public eden_ec::UIComponent {
	public:

		CImage()= default;
		/// <summary>
		/// Constructora de la clase Image
		/// </summary>
		CImage(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// <summary>
		/// Inicializa el componente
		/// </summary>
		void InitComponent() override;

		///<summary>
		/// Destructora de la clase Image
		/// </summary>
		~CImage();


		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:
		std::string _texture;
	};
} 

#endif 