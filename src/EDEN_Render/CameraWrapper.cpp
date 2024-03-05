#include <OgreCamera.h>
#include <OgreSceneManager.h>

#include "CameraWrapper.h"
#include "RenderManager.h"

render_wrapper::CameraWrapper::CameraWrapper(std::string entityID) {
	_camera = eden_render::RenderManager::Instance()->_sceneMngr->createCamera(entityID + "_camera");

}

void render_wrapper::CameraWrapper::SetFarClipDistance(float distance) {
	_camera->setFarClipDistance((Ogre::Real)(distance));
}

void render_wrapper::CameraWrapper::SetNearClipDistance(float distance) {
	_camera->setNearClipDistance((Ogre::Real)(distance));
}

void render_wrapper::CameraWrapper::SetBackgroundColor(float r, float g, float b, float a) {

}