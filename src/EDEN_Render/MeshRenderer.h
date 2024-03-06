#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <string>
#include "RenderObject.h"
#include "OgreEntity.h"
namespace render_wrapper {

	class Animator;
	class RenderObject;
	class MeshRenderer : public render_wrapper::RenderObject
	{
		friend render_wrapper::Animator;

	public:
		MeshRenderer(const std::string entityID, const std::string meshName); // _ent = new(), NodeManager():Instance->attach(_ent, id)
		~MeshRenderer() {};

		void SetMaterial(const std::string material);
		void SetInvisible(bool visibility);
		void ActivateAnim(float dt);

	private:
		virtual Ogre::MovableObject* GetRenderObject();

		Ogre::Entity* _ent = nullptr;
		Ogre::AnimationState* _anim;
	};
}
#endif // MESH_RENDERER_H