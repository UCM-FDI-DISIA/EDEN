#define _CRTDBG_MAP_ALLOC
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>

#include "RenderObject.h"
#include "RenderManager.h"

Ogre::SceneManager* render_wrapper::RenderObject::getSceneManager(){
	return eden_render::RenderManager::Instance()->_sceneMngr;
}