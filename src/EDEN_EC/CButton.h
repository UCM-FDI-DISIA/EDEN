#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_BUTTON_H
#define EDEN_C_BUTTON_H

#include <string>

#include <UIComponent.h>

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	
	class CLuaBehaviour;

	/// @brief Clase que representa un bot�n en la UI
	class EDEN_API CButton : public eden_ec::UIComponent {
	public:

		/// @brief Constructora vacia
		CButton() = default;

		/// @brief Constructora de la clase 
		CButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth);

		/// @brief M�todo update heredado de component
		void Update(float deltaTime) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override;

		/// @brief Método que crea el botón
		void CreateButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth);

		/// @brief Destructora
		~CButton() = default;

		/// @brief Cambia la textura principal del bot�n
		void ChangeButtonTexture(const std::string& textureName);

		/// @brief Cambia todas las texturas del bot�n
		void ChangeTextures(const std::string& iniTex,
			const std::string& hoverTex,
			const std::string& clickedTex);

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return "BUTTON"; }

		void SetCallBack();

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
		std::string _iniTex = " ";

		/// @brief textura cuando el cursor est� encima
		std::string _hoverTex = " ";

		/// @brief textura cuando pulsamos el boton
		std::string _clickedTex = " ";

		std::string _currentTex = " ";

		/// @brief limite superior del boton
		int _topPosition = 0;

		/// @brief limite inferior del boton
		int _bottomPosition = 0;

		/// @brief limite izquierdo del boton
		int _leftPosition = 0;

		/// @brief limite derecho del boton
		int _rightPosition = 0;

		/// @brief Flag de si estamos encima del boton
		bool _hovering = 0;

		/// @brief Flag de si hemos pulsado
		bool _clicked = 0;

		/// @brief Tama�o anterior
		std::pair<float, float>_oldScale = std::make_pair(0.0f, 0.0f);


		/// @brief Puntero al script de lua
		CLuaBehaviour* _callback = nullptr;

	};
}

#endif  