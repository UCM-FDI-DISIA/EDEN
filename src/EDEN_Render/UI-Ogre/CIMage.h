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
	/// Clase que representa una im�gen en la UI
	/// </summary>
	class  CImage : public eden_ec::UIComponent {
	public:

		CImage() {};
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


		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:
		std::string _texture;
	};
} 

#endif 