#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

namespace Ogre {
	class SceneManager;
	class MovableObject;
}

namespace render_wrapper {
	class RenderObject {
	public:
		virtual ~RenderObject() = default;
		virtual Ogre::MovableObject* GetRenderObject() = 0;

	protected:
		Ogre::SceneManager* getSceneManager();
	};
}

#endif //_RENDER_OBJECT_H_