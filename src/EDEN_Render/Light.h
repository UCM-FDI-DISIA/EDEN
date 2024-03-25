#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_LIGHT_H
#define EDEN_LIGHT_H

#include "RenderObject.h"

enum LightType { LT_POINT, LT_DIRECTIONAL, LT_SPOTLIGHT};

namespace eden_utils {
	class Vector3;
}

namespace Ogre {
	class Light;
}

namespace render_wrapper
{
	class Light : public RenderObject
	{
	public:
		/// @brief Constructora del Wrapper de libreria de renderizado de luces
		/// @param enetityID Nombre de la entidad asociada 
		/// @param type Tipo de luz (LT_POINT, LT_DIRECTIONAL, LT_SPOTLIGHT)
		Light(const std::string entityID, LightType type);
		
		~Light() {};

		/// @brief Setea la visibilidad de la luz
		/// @param visibility True -> Visible, False -> No visible
		inline void SetVisible(bool visibility);

		/// @brief Devuelve si la luz es visible o no
		inline bool isVisible();

		/// @brief 
		/// @param color Variable de color
		inline void SetDiffuse(eden_utils::Vector3 color);

		/// @brief 
		/// @param color Variable de color
		inline void SetSpecular(eden_utils::Vector3 color);

		/// @brief Setea la direccion de la luz
		/// @param dir Vector de direccion de la luz
		inline void SetDirection(eden_utils::Vector3 dir);
	private:
		/// @brief Puntero a la luz de la libreria de renderizado
		Ogre::Light* _light = nullptr;
		/// @brief Variable de visibilidad
		bool _visibility = true;
		/// @brief Identificador de la entidad asociada
		std::string _entityID = "";

		/// @brief Devuelve el puntero de la luz
		Ogre::MovableObject* GetRenderObject() override;
	};
}
#endif // LIGHT_H