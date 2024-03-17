#include <iostream>
#include <OgreSceneNode.h>
#include <OgreRoot.h>
#include <OgreVector3.h>

#include "NodeManager.h"
#include "Vector3.h"
#include <Quaternion.h>
#include "RenderManager.h"
#include "RenderObject.h"

render_wrapper::NodeManager::NodeManager() {
	//Inicializamos el unordered_map de nodos e ID de entidades 
	_sceneObjectsMap = std::unordered_map<std::string, Ogre::SceneNode*>();

	//Hacemos referencia al nodo raiz de Ogre mediante el RenderManager
	Ogre::SceneManager* mSM = eden_render::RenderManager::Instance()->_sceneMngr;
	_rootNode = mSM->getRootSceneNode();
}

render_wrapper::NodeManager::~NodeManager() {
	//?????????????????????????????????????????????
	//Borramos todo lo que haya en el unordered_map
	_sceneObjectsMap.clear();
}

eden_utils::Vector3 render_wrapper::NodeManager::convertToEdenVector(const Ogre::Vector3 ogreVector) {
	eden_utils::Vector3 edenVector = eden_utils::Vector3(ogreVector.x, ogreVector.y, ogreVector.z);
	return edenVector;
}
Ogre::Vector3 render_wrapper::NodeManager::convertToOgreVector(const eden_utils::Vector3 edenVector) {
	Ogre::Vector3 ogreVector = Ogre::Vector3(edenVector.GetX(), edenVector.GetY(), edenVector.GetZ());
	return ogreVector;
}

eden_utils::Quaternion render_wrapper::NodeManager::convertToEdenQuaternion(const Ogre::Quaternion ogreVector) {
	eden_utils::Quaternion edenQuaternion = eden_utils::Quaternion(ogreVector.w, ogreVector.x, ogreVector.y, ogreVector.z);
	return edenQuaternion;
}

Ogre::Quaternion render_wrapper::NodeManager::convertToOgreQuaternion(const eden_utils::Quaternion edenQuaternion) {
	Ogre::Quaternion ogreQuaternion = Ogre::Quaternion(edenQuaternion.Real(), edenQuaternion.Complex().GetX(),
		edenQuaternion.Complex().GetY(), edenQuaternion.Complex().GetZ());
	return ogreQuaternion;
}

Ogre::SceneNode* render_wrapper::NodeManager::FindNode(const std::string id) {
	auto aux = _sceneObjectsMap.find(id);
	if (aux == _sceneObjectsMap.end()) {
		std::cerr << ERROR_DEFINITION << " " << "WARNING: scene node with id: " + id + " not found in  the scene objects map'\n'";
		
		// TRATAMIENTO DE ERRORES DE LUA AQUÍ --------
		// Se devuelve nullptr para que el wrapper que necesite el nodo sepa que no existe 
		// y por tanto debera crear uno propio y lo asocie a la entidad
		return nullptr;
	}
	return aux->second;
}

void render_wrapper::NodeManager::CreateSceneObject(const std::string id) {
	Ogre::SceneNode* auxNode = _rootNode->createChildSceneNode(id);
	_sceneObjectsMap.insert({ id, auxNode });
}

void render_wrapper::NodeManager::AddChildToObject(const std::string idChild, const std::string idParent) {
	Ogre::SceneNode* parent = FindNode(idParent);
	Ogre::SceneNode* auxNode = parent->createChildSceneNode(idChild);
	_sceneObjectsMap.insert({ idChild, auxNode });
}

eden_utils::Vector3 render_wrapper::NodeManager::GetPosition(const std::string id) {
	Ogre::Vector3 ogreVector = FindNode(id)->getPosition();
	return convertToEdenVector(ogreVector);
}

eden_utils::Vector3 render_wrapper::NodeManager::GetScale(const std::string id) {
	Ogre::Vector3 ogreVector = FindNode(id)->getScale();
	return convertToEdenVector(ogreVector);
}

void render_wrapper::NodeManager::RemoveSceneObject(const std::string id) {
	auto aux = _sceneObjectsMap.find(id);
	if (aux == _sceneObjectsMap.end()) {
		std::cerr << ERROR_DEFINITION << " " << "WARNING: scene node with id: " + id + " not found in  the scene objects map'\n'";
	}
	else {
		aux->second->removeAndDestroyAllChildren();
		eden_render::RenderManager::Instance()->_sceneMngr->destroySceneNode(aux->second);
		_sceneObjectsMap.erase(aux);
	}
}

void render_wrapper::NodeManager::Attach(Ogre::MovableObject* obj, const std::string id) {
	FindNode(id)->attachObject(obj);
}

void render_wrapper::NodeManager::SetPosition(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->setPosition(convertToOgreVector(pos));
}

void render_wrapper::NodeManager::SetOrientation(const eden_utils::Quaternion quat, const std::string id) {
	FindNode(id)->setOrientation(convertToOgreQuaternion(quat));
}

void render_wrapper::NodeManager::ShowBoundingBox(bool active, const std::string id) {
	FindNode(id)->showBoundingBox(active);
}

void render_wrapper::NodeManager::Rotate(const eden_utils::Vector3 rotation, const std::string id) {
	Ogre::SceneNode* aux = FindNode(id);
	aux->pitch(Ogre::Degree(rotation.GetX()));
	aux->yaw(Ogre::Degree(rotation.GetY()));
	aux->roll(Ogre::Degree(rotation.GetZ()));

}

void render_wrapper::NodeManager::RotateLocal(const eden_utils::Vector3 rotation, const std::string id) {
	Ogre::SceneNode* aux = FindNode(id);
	aux->pitch(Ogre::Degree(rotation.GetX()), Ogre::Node::TS_LOCAL);
	aux->yaw(Ogre::Degree(rotation.GetY()), Ogre::Node::TS_LOCAL);
	aux->roll(Ogre::Degree(rotation.GetZ()), Ogre::Node::TS_LOCAL);
}

void render_wrapper::NodeManager::Scale(const eden_utils::Vector3 scale, const std::string id) {
	FindNode(id)->setScale(convertToOgreVector(scale));
}

void render_wrapper::NodeManager::Translate(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->translate(convertToOgreVector(pos), Ogre::Node::TS_LOCAL);
}

void render_wrapper::NodeManager::LookAt(const eden_utils::Vector3 pos, const std::string id) {
	FindNode(id)->lookAt(convertToOgreVector(pos), Ogre::Node::TS_WORLD);
}
