#pragma once
#ifndef __UI_COMPONENT_H__
#define __UI_COMPONENT_H__

#include "Component.h"
#include "Vector3.h"
#include <utility>
#include <string>

namespace Ogre {

	class OverlayManager;
	class Overlay;
	class OverlayContainer;
	enum GuiMetricsMode;
	enum GuiHorizontalAlignment;
	enum GuiVerticalAlignment;
}  // namespace Ogre

namespace eden_input {
	class  InputManager;
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

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

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

		/// @brief Cambia el tama�o del componente
		/// @param width Anchura del componente
		/// @param height Altura del componente
		void SetDimensions(float width, float height);

		/// @brief Cambia el ancho del componente
		/// @param width Anchura del componente
		void SetWidth(float width);

		/// @brief Cambia la altura del componente
		/// @param height Altura del componente
		void SetHeigth(float heigth);

		/// @brief Alineamiento horizontal del componente
		/// @param hAligment Puede ser GHA_LEFT, GHA_CENTER, GHA_RIGHT
		void SetHorizontalAligment(Ogre::GuiHorizontalAlignment const& hAligment);

		/// @brief Alineamiento vertical del componente
		/// @param vAligment Puede ser GVA_TOP, GVA_CENTER, GVA_BOTTOM
		void SetVerticalAligment(Ogre::GuiVerticalAlignment const& vAligment);

		/// @brief Cambia la posici�n del componente
		/// @param xPos Posici�n del eje x
		/// @param yPos Posici�n del eje y
		void SetPosition(float xPos, float yPos);

		/// <summary>
		/// Cambia el material del componente
		/// </summary>
		void SetMaterial(std::string const& matName);

		/// @brief Cambiar el tipo de m�tricas
		/// @param mode Puede ser GMM_PIXELS(posiciones absolutas) o GMM_RELATIVE (posiciones de 0.0 a 1.0)
		void SetMetrics(Ogre::GuiMetricsMode const& mode);

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

		/// @brief Devuelve el ancho del componente
		float GetWidth();

		/// @brief Devuelve la altura del componente
		float GetHeight();

		/// @brief Devuelve la alineaci�n horizontal del componente
		Ogre::GuiHorizontalAlignment const& GetHorizontalAligment();

		/// @brief Devuelve la alineaci�n vertical del componente
		Ogre::GuiVerticalAlignment const& GetVerticalAligment();

		/// @brief Devuelve la posici�n del componente
		std::pair <float, float> const& GetPosition();

		/// @brief Devuelve el material del componente
		std::string const& GetMaterialName();

		/// @brief Devuelve el tipo de m�tricas del componente
		Ogre::GuiMetricsMode const& GetMetrics();

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;
		/// @brief Managers y elementos de Ogre necesarios para el control y uso de la UI
		Ogre::OverlayManager* _overlayManager;
		Ogre::Overlay* _overlayElement;
		Ogre::OverlayContainer* _overlayContainer;

		/// @brief Control de los elementos de la UI		
		static int _numUIElements;

		/// @brief Input para los eventos de los botones
		eden_input::InputManager* _inputManager;
	};
}  
#endif  