#ifndef EDEN_MESH_RENDERER_H
#define EDEN_MESH_RENDERER_H

// Libreria de C++
#include <string>

// Archivos del proyecto
#include "RenderObject.h"

namespace Ogre {
	class Entity;
	class MovableObject;
}

namespace render_wrapper {

	class Animator;
	class RenderObject;
	class MeshRenderer : public RenderObject
	{
		friend Animator;

	public:
		/// @brief Constructora del Wrapper de libreria de renderizado de mallas
		/// @param enetityID Nombre de la entidad asociada al componente MeshRenderer
		/// @param meshName Nombre del archivo de la malla
		MeshRenderer(const std::string entityID, const std::string sceneID, const std::string meshName);

		~MeshRenderer() override;

		/// @brief Setea el material a la malla 
		/// @param material Nombre del archivo del material 
		void SetMaterial(const std::string material);

		/// @brief Setea la la visibilidad de la malla
		/// @param visibility True -> Visible, False -> No visible
		void SetInvisible(bool visibility);

	private:
		/// @brief Puntero a la entidad asociada al componente
		Ogre::Entity* _ent = nullptr;

		/// @brief Devuelve la entidad asociada a la malla
		Ogre::MovableObject* GetRenderObject() override;

	};
}
#endif // MESH_RENDERER_H