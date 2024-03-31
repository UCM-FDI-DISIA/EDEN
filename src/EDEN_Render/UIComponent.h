#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_UI_COMPONENT_H
#define EDEN_UI_COMPONENT_H

#include <utility>
#include <string>

#include "Component.h"
#include "Vector3.h"

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
	class UIComponent : public Component 
	{
	public:
		/// @brief Constructora de la clase
		UIComponent();

		/// @brief Destructora de la clase
		virtual ~UIComponent();

		/// @brief Mostrar el elemento de la ui
		void Show();

		/// @brief Ocultar el elemento de la ui
		void Hide();

		/// @brief Determina que elementos estan por encima de otros
		/// @param pos Valores desde -32 hasta 32
		void SetDepth(float pos);

		/// @brief Cambia el caption del componente
		void SetCaption(std::string const& caption);

		/// @brief Cambia el color del componente
		void SetColor(eden_utils::Vector3 const& color);

		/// @brief Cambia el tamanno del componente
		/// @param width Anchura del componente
		/// @param height Altura del componente
		void SetDimensions(float width, float height);

		/// @brief Cambia el tamanno del componente
		/// @param width Anchura del componente
		/// @param height Altura del componente
		void SetRelativeDimensions(float width, float height);

		/// @brief Cambia la posicion del componente
		/// @param xPos Posicion del eje x
		/// @param yPos Posicion del eje y
		void SetPosition(float xPos, float yPos);

		/// @brief Cambia la posicion del componente
		/// @param xPos Posicion del eje x
		/// @param yPos Posicion del eje y
		void SetRelativePosition(float xPos, float yPos);

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

		/// @brief Devuelve el caption del componente
		std::string const GetCaption() const;

		/// @brief Decuelve color del componente
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

		/// @brief Escala el tama�o y posicion 
		void Resize();

		/// @brief Establece los valores base
		void SetParameters();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		inline static std::string GetID() { return _id; }
	protected:

		const static std::string _id;
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

		/// @brief Textura de la imagen 
		std::string _texture;

		/// @brief Método encargado de crear una Imagen
		void CreateImage(std::string overlayName, float xPos, float yPos,
			float width, float height, std::string texture,
			int depth);

		/// @brief Método encargado de crear un Texto
		void CreateText(std::string overlayName, float xPos, float yPos,
			float tam, std::string text, std::string font, float rColor, float gColor, float bColor,
			int depth);
	private:
		/// @brief Managers y elementos de Ogre necesarios para el control y uso de la UI
		Ogre::OverlayManager* _overlayManager = nullptr;
		Ogre::Overlay* _overlayElement = nullptr;
		Ogre::OverlayContainer* _overlayContainer = nullptr;
		Ogre::TextAreaOverlayElement* _text;

		/// @brief Ruta de la carpeta de los materiales 
		std::string _rute = "assets/mesh/";

		/// @Método que comprueba si existe un archivo concreto
		/// @param name Nombre del archivo (ruta)
		bool FileExists(std::string const& name);

		/// @brief Método encargado de crear el overlayContainer
		void SetOverlayContainer(std::string overlayName, float xPos, float yPos,float width, float height);
		
		/// @brief Método encargado de crear el overlayElement
		void SetOverlayElement(int depth);

		/// @brief Método encargado de cargar la fuente
		void LoadFont(std::string font);
	};
}  
#endif  