
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "UIComponent.h"
#include <string>

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	
	class CButtonBehaviour;

	/// @brief Par�metros del bot�n
	struct ButtonParams {
		std::string overlayName = std::string();
		float xPos = 0, yPos = 0;
		int depth = 0;
		float width = 0, height = 0;
		std::string iniTex = std::string();
		std::string hoverTex = std::string();
		std::string clickedTex = std::string();
	};

	/// @brief Clase que representa un bot�n en la UI
	class CButton : public eden_ec::UIComponent {
	public:

		/// @brief Constructora vacia
		CButton() = default;

		/// @brief Constructora de la clase 
		CButton(ButtonParams& params);

		/// @brief M�todo update heredado de component
		void Update(float deltaTime) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override;

		/// @brief Destructora
		~CButton();

		/// @brief Cambia la textura principal del bot�n
		void ChangeButtonTexture(const std::string& textureName);

		/// @brief Cambia todas las texturas del bot�n
		void ChangeTextures(const std::string& iniTex,
			const std::string& hoverTex,
			const std::string& clickedTex);

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;

	private:

		/// @brief Comprueba si el rat�n est� en los l�mites del bot�n
		void CheckMousePos();

		/// @brief Metodo que se llama cuando se hace click en el bot�n
		void OnButtonClick();

		/// @brief Metodo que se llama cuando se termina click en el bot�n
		void OnButtonReleased();

		/// @brief Metodo que se llama la primera vez que se pone el raton sobre el bot�n
		void OnButtonHover();

		/// @brief Metodo que se llama cuando el raton sale del bot�n
		void OnButtonUnhover();

		void ButtonRectUpdate();

		/// @brief textura base
		std::string _iniTex;

		/// @brief textura cuando el cursor est� encima
		std::string _hoverTex;

		/// @brief textura cuando pulsamos el boton
		std::string _clickedTex;

		/// @brief limite superior del boton
		int _topPosition;

		/// @brief limite inferior del boton
		int _bottomPosition;

		/// @brief limite izquierdo del boton
		int _leftPosition;

		/// @brief limite derecho del boton
		int _rightPosition;

		/// @brief Flag de si estamos encima del boton
		bool _hovering;

		/// @brief Flag de si hemos pulsado
		bool _clicked;

		/// @brief Tama�o anterior
		std::pair<float, float>_oldScale;


		/// @brief Puntero al script de lua
		CButtonBehaviour* _callback;

	};
}

#endif  