#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#pragma warning(pop)

#include "CameraWrapper.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "RenderManager.h"
#include "NodeManager.h"

Ogre::Viewport* render_wrapper::CameraWrapper::_viewport = nullptr;

render_wrapper::CameraWrapper::CameraWrapper(std::string entityID, const std::string sceneID) : RenderObject(sceneID), _entityID(entityID), _sceneID(sceneID) {
	_camera = GetSceneManager()->createCamera(entityID + "_camera_" + sceneID);
	SetNearClipDistance(1.0f);
	SetFarClipDistance(10000.0f);
	SetAutoAspectRatio(true);
	if (!render_wrapper::NodeManager::Instance()->HasNode(entityID, sceneID))
		render_wrapper::NodeManager::Instance()->CreateSceneObject(entityID, sceneID);

	if (_viewport == nullptr) _viewport = eden_render::RenderManager::Instance()->_window.render->addViewport(_camera);
	else {
		_viewport = eden_render::RenderManager::Instance()->_window.render->getViewport(0);
		SetActiveCamera();
	}
	SetBackgroundColor(DEFAULT_BG_COLOR, 1.0f);
	render_wrapper::NodeManager::Instance()->Attach(GetRenderObject(), entityID, sceneID);
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

void render_wrapper::CameraWrapper::SetBackgroundColor(eden_utils::Vector3 rgb, float a) {
	SetBackgroundColor(rgb.GetX(), rgb.GetY(), rgb.GetZ(), a);
}

void render_wrapper::CameraWrapper::SetAutoAspectRatio(bool set) {
	_camera->setAutoAspectRatio(set);
}

void render_wrapper::CameraWrapper::SetCameraPosition(eden_utils::Vector3 pos) {
	render_wrapper::NodeManager::Instance()->SetPosition(pos, _entityID, _sceneID);
}

void render_wrapper::CameraWrapper::SetCameraRotation(eden_utils::Quaternion rot) {
	render_wrapper::NodeManager::Instance()->SetOrientation(rot, _entityID, _sceneID);
}

void render_wrapper::CameraWrapper::LookAt(eden_utils::Vector3 lookat) {
	render_wrapper::NodeManager::Instance()->LookAt(lookat, _entityID, _sceneID);
}

eden_utils::Vector3 render_wrapper::CameraWrapper::GetCameraPosition() const {
	return render_wrapper::NodeManager::Instance()->GetPosition(_entityID, _sceneID);
}

Ogre::MovableObject* render_wrapper::CameraWrapper::GetRenderObject() {
	return _camera;
}

void render_wrapper::CameraWrapper::SetActiveCamera() const
{
	_viewport->setCamera(_camera);
}
