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

	/// @brief Clase que representa un boton en la UI
	class CButton : public eden_ec::UIComponent {
	public:

		/// @brief Constructora vacia
		EDEN_API CButton() = default;

		/// @brief Constructora de la clase 
		EDEN_API CButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth);

		/// @brief Metodo update heredado de component
		EDEN_API void Update(float deltaTime) override;
		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		EDEN_API void Start() override;

		/// @brief Metodo que crea el boton
		EDEN_API void CreateButton(std::string overlayName, float xPos, float yPos, float width, float height, std::string iniTex, std::string hoverTex, std::string clickedTex, int depth);

		/// @brief Destructora
		EDEN_API ~CButton() = default;

		/// @brief Cambia la textura principal del boton
		EDEN_API void ChangeButtonTexture(const std::string& textureName);

		/// @brief Cambia todas las texturas del boton
		EDEN_API void ChangeTextures(const std::string& iniTex,
			const std::string& hoverTex,
			const std::string& clickedTex);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		EDEN_API static std::string GetID() { return "BUTTON"; }

		EDEN_API void SetCallBack();

	private:

		/// @brief Comprueba si el raton esta en los limites del boton
		void CheckMousePos();

		/// @brief Metodo que se llama cuando se hace click en el boton
		void OnButtonClick();

		/// @brief Metodo que se llama cuando se termina click en el boton
		void OnButtonReleased();

		/// @brief Metodo que se llama la primera vez que se pone el raton sobre el boton
		void OnButtonHover();

		/// @brief Metodo que se llama cuando el raton sale del boton
		void OnButtonUnhover();

		void ButtonRectUpdate();

		/// @brief textura base
		std::string _iniTex = " ";

		/// @brief textura cuando el cursor esta encima
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

		/// @brief Tamanio anterior
		std::pair<float, float>_oldScale = std::make_pair(0.0f, 0.0f);

		std::pair<float,float>_oldPos = std::make_pair(0.0f, 0.0f);


		/// @brief Puntero al script de lua
		CLuaBehaviour* _callback = nullptr;

	};
}

#endif  