
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "UIComponent.h"

#include <string>

namespace Ogre {
	class Overlay;
}

namespace eden_ec {

	/// @brief Parámetros del botón
	struct ButtonParams {
		std::string overlayName = std::string();
		float xPos = 0, yPos = 0;
		int depth = 0;
		float width = 0, height = 0;
		std::string iniTex = std::string();
		std::string hoverTex = std::string();
		std::string clickedTex = std::string();
	};

	/// @brief Clase que representa un botón en la UI
	class CButton : public eden_ec::UIComponent {
	public:

		/// @brief Constructora vacia
		CButton() = default;

		/// @brief Constructora de la clase 
		CButton(ButtonParams& params);

		/// @brief Método update heredado de component
		void Update(float deltaTime) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override{}

		/// @brief Destructora
		~CButton();

		/// @brief Cambia la textura principal del botón
		void ChangeButtonTexture(const std::string& textureName);

		/// @brief Cambia todas las texturas del botón
		void ChangeTextures(const std::string& iniTex,
			const std::string& hoverTex,
			const std::string& clickedTex);

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:

		/// @brief Comprueba si el ratón está en los límites del botón
		void CheckMousePos();

		/// @brief Metodo que se llama cuando se hace click en el botón
		void OnButtonClick();

		/// @brief Metodo que se llama cuando se termina click en el botón
		void OnButtonReleased();

		/// @brief Metodo que se llama la primera vez que se pone el raton sobre el botón
		void OnButtonHover();

		/// @brief Metodo que se llama cuando el raton sale del botón
		void OnButtonUnhover();

		std::string _iniTex;
		std::string _hoverTex;
		std::string _clickedTex;

		int _topPosition;
		int _bottomPosition;
		int _leftPosition;
		int _rightPosition;
		bool _hovering;
		bool _clicked;
		int _depth;
	};
}

#endif  