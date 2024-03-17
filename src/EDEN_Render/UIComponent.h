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

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		void Init(eden_script::ComponentArguments* args) override;

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

		// @brief Cambia la posicion del componente
		/// @param xPos Posicion del eje x
		/// @param yPos Posicion del eje y
		void SetRelativePosition(float xPos, float yPos);

		/// <summary>
		/// Cambia el material del componente
		/// </summary>
		void SetMaterial(std::string const& matName);

		/// @brief Poner visible el overlay
		/// @param visible Booleano para ponerlo visible
		void SetOverlayVisible(bool visible);

		/// @brief Devuelve la visibilidad del componente
		bool IsVisible();

		/// @brief Devuelve la profundidad del componente
		float GetDepth();

		/// @brief Devuelve el caption del componente
		std::string const& GetCaption();

		/// @brief Decuelve color del componente
		eden_utils::Vector3 const& GetColor();

		/// @brief Devuelve las dimensiones del componente
		std::pair<float, float> const& GetDimensions();

		/// @brief Devuelve las dimensiones del componente
		std::pair<float, float> const& GetRelativeDimensions();

		/// @brief Devuelve la posicion del componente
		std::pair <float, float> const& GetPosition();

		/// @brief Devuelve la posicion del componente
		std::pair <float, float> const& GetRelativePosition();

		/// @brief Devuelve el material del componente
		std::string const& GetMaterialName();

		/// @brief Escala el tama�o y posicion 
		void Resize();

		/// @brief Establece los valores base
		void SetParameters();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return _id; }
	protected:

		const static std::string _id;
		/// @brief Control de los elementos de la UI		
		static int _numUIElements;

		/// @brief Input para los eventos de los botones
		eden_input::InputManager* _inputManager = nullptr;

		/// @brief ancho relativo
		float _rWidth;

		/// @brief ancho objeto
		float _oWidth;

		/// @brief alto relativo
		float _rHeight;

		/// @brief alto objeto
		float _oHeight;

		/// @brief pos relativa
		std::pair <float, float>_rPos;

		/// @brief pos objeto
		std::pair <float, float>_oPos;

		/// @brief Textura de la imagen 
		std::string _texture;


		void CreateImage(std::string overlayName, float xPos, float yPos,
			float width, float height, std::string texture,
			int depth);
	private:
		/// @brief Managers y elementos de Ogre necesarios para el control y uso de la UI
		Ogre::OverlayManager* _overlayManager = nullptr;
		Ogre::Overlay* _overlayElement = nullptr;
		Ogre::OverlayContainer* _overlayContainer = nullptr;

	};
}  
#endif  