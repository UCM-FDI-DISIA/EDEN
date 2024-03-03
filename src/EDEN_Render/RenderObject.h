#pragma once
#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

#include <OgreMovableObject.h>

namespace render_wrapper {
	class RenderObject {
	public:
		virtual ~RenderObject() = default;
		virtual Ogre::MovableObject* GetRenderObject() = 0;
	};
}

#endif //_RENDER_OBJECT_H_