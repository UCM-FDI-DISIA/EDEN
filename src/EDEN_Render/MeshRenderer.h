#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <string> // si??

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_render {
	class RenderManager;
}
namespace render_wrapper {

	class RenderObject;
	class MeshRenderer : public render_wrapper::RenderObject
	{
	public:
		MeshRenderer(/*id de la entidad*/ /*mesh*/); // _ent = new(), NodeManager():Instance->attach(_ent, id)
		~MeshRenderer();

		//void setPositon(const eden_utils::Vector3 pos, const std::string id);
		//void setOrientation(const eden_utils::Quaternion qua, const std::string id);

		void setMaterial();
		// getMaterial
		// setInvisible

	private:
		//render_wrapper::Node* node_manager = nullptr;
		// instancia de node manager 

		// Ogre::Enitty* ent entidad de ogre (attach en la constructora)
		// string id 
	};
}
#endif // MESH_RENDERER_H