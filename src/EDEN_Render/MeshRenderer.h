#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <string>
#include "RenderObject.h"

namespace render_wrapper {

	class MeshRenderer : public render_wrapper::RenderObject
	{
	public:
		MeshRenderer(const std::string entityID, const std::string meshName); // _ent = new(), NodeManager():Instance->attach(_ent, id)
		~MeshRenderer() {};

		void SetMaterial(const std::string material);
		void SetInvisible(bool visibility);

	private:
		virtual Ogre::MovableObject* GetRenderObject();

		Ogre::Entity* _ent = nullptr;
	};
}
#endif // MESH_RENDERER_H