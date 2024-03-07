#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

// Libreria de C++
#include <string>

// Librerias adicionales
#include "OgreEntity.h"

// Archivos del proyecto
#include "RenderObject.h"

namespace render_wrapper {

	class Animator;
	class RenderObject;
	class MeshRenderer : public render_wrapper::RenderObject
	{
		friend render_wrapper::Animator;

	public:
		/// @brief Constructora del Wrapper de libreria de renderizado de mallas
		/// @param enetityID Nombre de la entidad asociada al componente MeshRenderer
		/// @param meshName Nombre del archivo de la malla
		MeshRenderer(const std::string entityID, const std::string meshName);

		~MeshRenderer() {};

		/// @brief Setea el material a la malla 
		/// @param material Nombre del archivo del material 
		void SetMaterial(const std::string material);

		/// @brief Setea la la visibilidad de la malla
		/// @param visibility True -> Visible, False -> No visible
		void SetInvisible(bool visibility);

		/// @brief 
		/// @param dt Variable delta time
		void ActivateAnim(float dt);

	private:
		/// @brief Puntero a la entidad asociada al componente
		Ogre::Entity* _ent = nullptr;
		
		/// @brief Devuelve la entidad asociada a la malla
		Ogre::MovableObject* GetRenderObject() override;

	};
}
#endif // MESH_RENDERER_H