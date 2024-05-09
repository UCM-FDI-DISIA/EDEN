#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#pragma warning(pop)

#include "RenderObject.h"
#include "RenderManager.h"

Ogre::SceneManager* render_wrapper::RenderObject::GetSceneManager(){
	std::unordered_map<std::string, eden_render::InfoRenderWorld*>::iterator it = eden_render::RenderManager::Instance()->_renderScenes.find(_sceneID);
	if (it != eden_render::RenderManager::Instance()->_renderScenes.end()) {
		return it->second->GetRenderScene();
	}
	else {
		return nullptr;
	}
}

render_wrapper::RenderObject::RenderObject(std::string sceneID) : _sceneID(sceneID) {}