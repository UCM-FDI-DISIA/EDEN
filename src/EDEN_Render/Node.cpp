#include <iostream>
#include <OgreSceneNode.h>
#include <OgreRoot.h>
#include "Node.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "RenderManager.h"
#include "RenderObject.h"

render_wrapper::Node::Node() {
	_sceneObjectsMap = std::unordered_map<std::string, Ogre::SceneNode*>();
	Ogre::SceneManager* mSM = eden_render::RenderManager::Instance()->_sceneMngr;
	_rootNode = mSM->getRootSceneNode();
}

render_wrapper::Node::~Node() {
	_sceneObjectsMap.clear();
}

eden_utils::Vector3 render_wrapper::Node::convertToEdenVector(const Ogre::Vector3 ogreVector) {
	eden_utils::Vector3 edenVector = eden_utils::Vector3(ogreVector.x, ogreVector.y, ogreVector.z);
	return edenVector;
}
Ogre::Vector3 render_wrapper::Node::convertToOgreVector(const eden_utils::Vector3 edenVector) {
	Ogre::Vector3 ogreVector = Ogre::Vector3(edenVector.GetX(), edenVector.GetY(), edenVector.GetZ());
	return ogreVector;
}

eden_utils::Quaternion render_wrapper::Node::convertToEdenQuaternion(const Ogre::Quaternion ogreVector) {
	eden_utils::Quaternion edenQuaternion = eden_utils::Quaternion(ogreVector.w, ogreVector.x, ogreVector.y, ogreVector.z);
	return edenQuaternion;
}

Ogre::Quaternion render_wrapper::Node::convertToOgreQuaternion(const eden_utils::Quaternion edenQuaternion) {
	Ogre::Quaternion ogreQuaternion = Ogre::Quaternion(edenQuaternion.Real(), edenQuaternion.Complex().GetX(),
		edenQuaternion.Complex().GetY(), edenQuaternion.Complex().GetZ());
	return ogreQuaternion;
}

Ogre::SceneNode* render_wrapper::Node::FindNode(const std::string id) {
	auto aux = _sceneObjectsMap.find(id);
	if (aux == _sceneObjectsMap.end()) {
		std::cerr << "RenderWrapper::Node ERROR in line 25: scene node with id: " + id + " not found in _sceneObjectsMap" << std::endl;
		return nullptr;
	}
	else {
		return aux->second;
	}
}
void render_wrapper::Node::CreateSceneObject(const std::string id) {
	Ogre::SceneNode* auxNode = _rootNode->createChildSceneNode(id);
	_sceneObjectsMap.insert({ id, auxNode });
}

void render_wrapper::Node::AddChildToObject(const std::string idChild, const std::string idParent) {
	Ogre::SceneNode* parent = FindNode(idParent);
	Ogre::SceneNode* auxNode = parent->createChildSceneNode(idChild);
	_sceneObjectsMap.insert({ idChild, auxNode });
}

eden_utils::Vector3 render_wrapper::Node::GetPosition(const std::string id) {
	Ogre::Vector3 ogreVector = FindNode(id)->getPosition();
	return convertToEdenVector(ogreVector);
}

eden_utils::Vector3 render_wrapper::Node::GetScale(const std::string id) {
	Ogre::Vector3 ogreVector = FindNode(id)->getScale();
	return convertToEdenVector(ogreVector);
}

void render_wrapper::Node::RemoveSceneObject(const std::string id) {
	auto aux = _sceneObjectsMap.find(id);
	if (aux == _sceneObjectsMap.end()) {
		std::cerr << "RenderWrapper::Node ERROR in line 25: scene node with id: " + id + " not found in _sceneObjectsMap" << std::endl;
	}
	else {
		aux->second->removeAndDestroyAllChildren();
		eden_render::RenderManager::Instance()->_sceneMngr->destroySceneNode(aux->second);
		_sceneObjectsMap.erase(aux);
	}
}

void render_wrapper::Node::Attach(Ogre::MovableObject* obj, const std::string id) {
	FindNode(id)->attachObject(obj);
}

void render_wrapper::Node::SetPosition(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->setPosition(convertToOgreVector(pos));
}

void render_wrapper::Node::SetOrientation(const eden_utils::Quaternion quat, const std::string id) {
	FindNode(id)->setOrientation(convertToOgreQuaternion(quat));
}

void render_wrapper::Node::ShowBoundingBox(bool active, const std::string id) {
	FindNode(id)->showBoundingBox(active);
}

void render_wrapper::Node::Rotate(const eden_utils::Vector3 rotation, const std::string id) {
	Ogre::SceneNode* aux = FindNode(id);
	aux->pitch(Ogre::Degree(rotation.GetX()));
	aux->yaw(Ogre::Degree(rotation.GetY()));
	aux->roll(Ogre::Degree(rotation.GetZ()));

}

void render_wrapper::Node::RotateLocal(const eden_utils::Vector3 rotation, const std::string id) {
	Ogre::SceneNode* aux = FindNode(id);
	aux->pitch(Ogre::Degree(rotation.GetX()), Ogre::Node::TS_LOCAL);
	aux->yaw(Ogre::Degree(rotation.GetY()), Ogre::Node::TS_LOCAL);
	aux->roll(Ogre::Degree(rotation.GetZ()), Ogre::Node::TS_LOCAL);
}

void render_wrapper::Node::Scale(const eden_utils::Vector3 scale, const std::string id) {
	FindNode(id)->scale(convertToOgreVector(scale));
}

void render_wrapper::Node::Translate(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->translate(convertToOgreVector(pos), Ogre::Node::TS_LOCAL);
}

void render_wrapper::Node::LookAt(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->lookAt(convertToOgreVector(pos), Ogre::Node::TS_WORLD);
}
