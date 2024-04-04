#define _CRTDBG_MAP_ALLOC
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#pragma warning(pop)

#include "RenderObject.h"
#include "RenderManager.h"

Ogre::SceneManager* render_wrapper::RenderObject::getSceneManager(){
	return eden_render::RenderManager::Instance()->_sceneMngr;
}