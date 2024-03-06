#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>

#include "CameraWrapper.h"
#include "RenderManager.h"
#include "Node.h"
#include "Vector3.h"
#include "Quaternion.h"

render_wrapper::CameraWrapper::CameraWrapper(std::string entityID) : _entityID(entityID) {
	_camera = eden_render::RenderManager::Instance()->_sceneMngr->createCamera(entityID + "_camera");
	SetNearClipDistance(1.0f);
	SetFarClipDistance(10000.0f);
	SetAutoAspectRatio(true);
	render_wrapper::Node::Instance()->Attach(GetRenderObject(), entityID);
	_viewport = eden_render::RenderManager::Instance()->_window.render->addViewport(_camera);
	SetBackgroundColor(0.9f, 0.7f, 0.7f, 1.0f);
}

void render_wrapper::CameraWrapper::SetFarClipDistance(float distance) {
	_camera->setFarClipDistance((Ogre::Real)(distance));
}

void render_wrapper::CameraWrapper::SetNearClipDistance(float distance) {
	_camera->setNearClipDistance((Ogre::Real)(distance));
}

void render_wrapper::CameraWrapper::SetBackgroundColor(float r, float g, float b, float a) {
	_viewport->setBackgroundColour(Ogre::ColourValue(r, g, b, a));
}

void render_wrapper::CameraWrapper::SetAutoAspectRatio(bool set) {
	_camera->setAutoAspectRatio(set);
}

void render_wrapper::CameraWrapper::SetCameraPosition(eden_utils::Vector3 pos) {
	render_wrapper::Node::Instance()->SetPosition(pos, _entityID);
}

void render_wrapper::CameraWrapper::SetCameraRotation(eden_utils::Quaternion rot) {
	render_wrapper::Node::Instance()->SetOrientation(rot, _entityID);
}

void render_wrapper::CameraWrapper::LookAt(eden_utils::Vector3 lookat) {
	render_wrapper::Node::Instance()->LookAt(lookat, _entityID);
}

eden_utils::Vector3 render_wrapper::CameraWrapper::GetCameraPosition() const {
	return render_wrapper::Node::Instance()->GetPosition(_entityID);
}

Ogre::MovableObject* render_wrapper::CameraWrapper::GetRenderObject() {
	return _camera;
}