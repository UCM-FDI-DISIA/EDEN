#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <string>
#include "RenderObject.h"

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace render_wrapper {

	class Animator;
	class RenderObject;
	class MeshRenderer : public render_wrapper::RenderObject
	{
		friend render_wrapper::Animator;

	public:
		MeshRenderer(const std::string entityID, const std::string meshName); // _ent = new(), NodeManager():Instance->attach(_ent, id)
		~MeshRenderer();

		void SetMaterial();
		// getMaterial
		// setInvisible

	private:
		Ogre::Entity* _ent = nullptr;
		// string id 
	};
}
#endif // MESH_RENDERER_H