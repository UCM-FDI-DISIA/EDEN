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
	/// <summary>
	/// Clase base de la que heredan todos los elementos de la UI
	/// </summary>
	class UIComponent : public Component 
	{
	public:
		/// <summary>
		/// Constructora de la clase
		/// </summary>
		UIComponent();

		/// <summary>
		/// Destructora de la clase
		/// </summary>
		virtual ~UIComponent();

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// <summary>
		/// Mostrar el elemento de la ui
		/// </summary>
		void Show();

		/// <summary>
		/// Ocultar el elemento de la ui
		/// </summary>
		void Hide();

		/// <summary>
		/// determina que elementos estan por encima de otros
		/// (valores desde -32 hasta 32)
		/// </summary>
		void SetDepth(float pos);

		/// <summary>
		/// Cambia el caption del componente
		/// </summary>
		void SetCaption(std::string const& caption);
		/// <summary>
		/// Cambia el color del componente
		/// </summary>
		void SetColor(eden_utils::Vector3 const& color);
		/// <summary>
		/// Cambia el tamaño del componente
		/// </summary>
		void SetDimensions(float width, float height);
		/// <summary>
		/// Cambia el ancho del componente
		/// </summary>
		void SetWidth(float width);
		/// <summary>
		/// Cambia la altura del componente
		/// </summary>
		void SetHeigth(float heigth);

		/// <summary>
		/// Alineamiento horizontal del componente, puede ser
		/// GHA_LEFT, GHA_CENTER, GHA_RIGHT
		/// </summary>
		void
			SetHorizontalAligment(Ogre::GuiHorizontalAlignment const& hAligment);
		/// <summary>
		/// Alineamiento vertical del componente, puede ser
		/// GVA_TOP, GVA_CENTER, GVA_BOTTOM
		/// </summary>
		void SetVerticalAligment(Ogre::GuiVerticalAlignment const& vAligment);

		/// <summary>
		/// Cambia la posición del componente
		/// </summary>
		void SetPosition(float xPos, float yPos);

		/// <summary>
		/// Cambia el material del componente
		/// </summary>
		void SetMaterial(std::string const& matName);

		/// <summary>
		/// Cambiar el tipo de métricas, puede ser
		/// GMM_PIXELS(posiciones absolutas)
		/// GMM_RELATIVE,(posiciones de 0.0 a 1.0)
		/// </summary>
		void SetMetrics(Ogre::GuiMetricsMode const& mode);

		/// <summary>
		/// Poner visible el overlay
		/// </summary>
		/// <param name="visible">booleano para ponerlo visible</param>
		void SetVisible();

		/// <summary>
		/// Cambia la visibilidad del componente
		/// </summary>
		bool IsVisible();

		/// <returns>zorder del componente</returns>
		float GetDepth();

		/// <returns>caption del componente</returns>
		std::string const& GetCaption();

		/// <returns>color del componente</returns>
		eden_utils::Vector3 const& GetColor();

		/// <returns>dimensiones del componente</returns>
		std::pair<float, float> const& GetDimensions();

		/// <returns>ancho del componente</returns>
		float GetWidth();

		/// <returns>altura del componente</returns>
		float GetHeight();

		/// <returns>alineación horizontal del componente</returns>
		Ogre::GuiHorizontalAlignment const& GetHorizontalAligment();

		/// <returns>alineación vertical del componente</returns>
		Ogre::GuiVerticalAlignment const& GetVerticalAligment();

		/// <returns>posición del componente</returns>
		std::pair <float, float> const& GetPosition();

		/// <returns>material del componente</returns>
		std::string const& GetMaterialName();

		/// <returns>tipo de métricas del componente</returns>
		Ogre::GuiMetricsMode const& GetMetrics();

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }
	protected:
		const static std::string _id;
		// Managers y elementos de Ogre necesarios para el control y uso de la
		// UI
		Ogre::OverlayManager* _overlayManager;
		Ogre::Overlay* _overlayElement;
		Ogre::OverlayContainer* _overlayContainer;

		// Control de los elementos de la UI
		
		static int _numUIElements;

		//Input para los eventos de los botones
		eden_input::InputManager* _inputManager;
	};
}  
#endif  