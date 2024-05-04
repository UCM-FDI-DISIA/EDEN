#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_UI_COMPONENT_H
#define EDEN_UI_COMPONENT_H

#include <utility>
#include <string>

#include "Component.h"
#include "Vector3.h"

#include "defs.h"

namespace Ogre {
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
	enum GuiMetricsMode : unsigned int;
	enum GuiHorizontalAlignment : unsigned int;
	enum GuiVerticalAlignment : unsigned int;

	class TextAreaOverlayElement;
}  // namespace Ogre

namespace eden_input {
	class InputManager;
}
namespace eden_ec {
	/// @brief Clase base de la que heredan todos los elementos de la UI
	class EDEN_API UIComponent : public Component
	{
	public:
		/// @brief Constructora de la clase
		UIComponent();

		/// @brief Destructora de la clase
		virtual ~UIComponent();

		/// @brief Mostrar el elemento de la ui
		void Show(bool changedFromCanvas = false);

		/// @brief Ocultar el elemento de la ui
		void Hide(bool changedFromCanvas = false);

		/// @brief Determina que elementos estan por encima de otros
		/// @param pos Valores desde -32 hasta 32
		void SetDepth(float pos);

		/// @brief Cambia el color del componente
		void SetColor(eden_utils::Vector3 const& color);

		/// @brief Cambia el tamanno del componente
		/// @param width Anchura del componente
		/// @param height Altura del componente
		void SetDimensions(float width, float height);

		/// @brief Cambia la posicion del componente
		/// @param xPos Posicion del eje x
		/// @param yPos Posicion del eje y
		void SetPosition(float xPos, float yPos);

		/// @brief Cambia el material del componente
		/// @param matName Nombre del material
		void SetMaterial(std::string const& matName);

		/// @brief Poner visible el overlay
		/// @param visible Booleano para ponerlo visible
		void SetOverlayVisible(bool visible);

		/// @brief Devuelve la visibilidad del componente
		bool IsVisible();

		/// @brief Devuelve la profundidad del componente
		float GetDepth();

		/// @brief Devuelve color del componente
		eden_utils::Vector3 const GetColor() const;

		/// @brief Devuelve las dimensiones del componente
		std::pair<float, float> const GetDimensions() const;

		/// @brief Devuelve las dimensiones del componente
		std::pair<float, float> const GetRelativeDimensions() const;

		/// @brief Devuelve la posicion del componente
		std::pair <float, float> const GetPosition() const;

		/// @brief Devuelve la posicion del componente
		std::pair <float, float> const GetRelativePosition() const;

		/// @brief Devuelve el material del componente
		std::string const& GetMaterialName();

		/// @brief Escala el tamanio y posicion 
		void Resize();

		/// @brief Establece los valores base
		void SetParameters();

		/// @brief Establece las dimensiones base 
		void SetSizeParams();

		/// @brief Establece las posiciones base 
		void SetPosParams();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		inline static std::string GetID() { return "UICOMPONENT"; }

		inline std::string GetSceneID() { return _sceneID; };

		void Register(std::string sceneID);

	protected:

		std::string _sceneID;

		bool canvasVisible = true;
		
		/// @brief Control de los elementos de la UI		
		static int _numUIElements;

		/// @brief Input para los eventos de los botones
		eden_input::InputManager* _inputManager = nullptr;

		/// @brief ancho relativo
		float _rWidth = 0;

		/// @brief ancho objeto
		float _oWidth = 0;

		/// @brief alto relativo
		float _rHeight = 0;

		/// @brief alto objeto
		float _oHeight = 0;

		/// @brief pos relativa
		std::pair <float, float>_rPos;

		/// @brief pos objeto
		std::pair <float, float>_oPos;

		/// @brief screen size
		std::pair <int, int> _screenSize;

		/// @brief Textura de la imagen 
		std::string _texture;

		/// @brief Metodo encargado de crear una Imagen
		void CreateImage(std::string overlayName, float xPos, float yPos,
			float width, float height, std::string texture,
			int depth);

		/// @brief Metodo encargado de crear un Texto
		void CreateText(std::string overlayName, float xPos, float yPos,
			float tam, std::string text, std::string font, float rColor, float gColor, float bColor,
			int depth);

		/// @brief Devuelve el texto actual
		std::string GetText();

		/// @brief Cambia el texto actual
		void SetText(const std::string& text, bool resize = true);

	private:
		/// @brief Managers y elementos de Ogre necesarios para el control y uso de la UI
		Ogre::OverlayManager* _overlayManager = nullptr;
		/// @brief Tipo elemento de UI (imagen, texto...)
		Ogre::Overlay* _overlayElement = nullptr;
		/// @brief Elemento como tal de UI con todos sus paramentros
		Ogre::OverlayContainer* _overlayContainer = nullptr;
		///@ brief Area de texto 
		Ogre::TextAreaOverlayElement* _text = nullptr;

		/// @brief Metodo encargado de crear el overlayContainer
		void SetOverlayContainer(std::string overlayName, float xPos, float yPos,float width, float height);
		
		/// @brief Metodo encargado de crear el overlayElement
		void SetOverlayElement(int depth);

		/// @brief Metodo encargado de cargar la fuente
		void LoadFont(std::string font);

		/// @brief Cambia el tamanno del componente
		/// @param width Anchura del componente
		/// @param height Altura del componente
		void SetRelativeDimensions(float width, float height);

		/// @brief Cambia la posicion del componente
		/// @param xPos Posicion del eje x
		/// @param yPos Posicion del eje y
		void SetRelativePosition(float xPos, float yPos);
	};
}  
#endif  