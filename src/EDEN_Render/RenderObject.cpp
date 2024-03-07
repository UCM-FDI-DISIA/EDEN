#include "RenderObject.h"
#include "RenderManager.h"
#include <OgreMovableObject.h>
#include "OgreSceneManager.h"

Ogre::SceneManager* render_wrapper::RenderObject::getSceneManager(){
	return eden_render::RenderManager::Instance()->_sceneMngr;
}