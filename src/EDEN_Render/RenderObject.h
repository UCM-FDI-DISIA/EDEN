#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_RENDER_OBJECT_H
#define EDEN_RENDER_OBJECT_H

namespace Ogre {
	class SceneManager;
	class MovableObject;
}

namespace render_wrapper {
	class RenderObject {
	public:
		RenderObject(std::string sceneID);
		virtual ~RenderObject() = default;
		virtual Ogre::MovableObject* GetRenderObject() = 0;

	protected:
		std::string _sceneID;
		Ogre::SceneManager* GetSceneManager();
	};
}

#endif //_RENDER_OBJECT_H_