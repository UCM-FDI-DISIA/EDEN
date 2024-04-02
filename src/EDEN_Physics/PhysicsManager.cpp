#define _CRTDBG_MAP_ALLOC
#include <btBulletDynamicsCommon.h>

#include <ErrorHandler.h>

#include "PhysicsManager.h"
#include <Entity.h>
#include <CRigidBody.h>
#include <Transform.h>
#include "RayCast.h"
#include "RigidBody.h"
#include "CollisionCallback.h"
#include "CollisionLayer.h"
#include "DebugDrawer.h"
#include "ErrorHandler.h"
#include <iostream>

//const eden_ec::Entity* physics_manager::PhysicsManager::getEntity(const btRigidBody* RBRef) const
//{
//	if (_entitiesMap.find(RBRef) != _entitiesMap.end()) {
//		return _entitiesMap.at(RBRef);
//	}
//	return nullptr;
//}

void physics_manager::PhysicsManager::updateSimulation(float deltaTime)
{
	_dynamicWorldRef->stepSimulation(deltaTime);
	physics_wrapper::RigidBody* _rb;
	for (auto ent : _entitiesSet) {
		_rb = ent->GetComponent<eden_ec::CRigidBody>()->_rb;
		_dynamicWorldRef->contactTest(_rb->getBulletRigidBody(), *_rb->_collisionCallback);
	}
}

void physics_manager::PhysicsManager::CreateCollisionLayer(std::string name, std::string sceneID)
{
	LayerInfo layerPair(name, sceneID);
	auto layerIt = _layers.find(layerPair);
	if (layerIt == _layers.end()) {
		physics_wrapper::CollisionLayer* layer = new physics_wrapper::CollisionLayer(name, sceneID);
		_layers[{name, sceneID}] = layer;
	}
}

void physics_manager::PhysicsManager::RemoveCollisionToLayer(std::string layerName, std::string collisionToAdd, std::string sceneID)
{
	if(collisionToAdd != COLLISIONMASK_NULL)
	{
		LayerInfo layerPair(layerName, sceneID);
		LayerInfo otherLayerPair(collisionToAdd, sceneID);
		auto layer = _layers.find(layerPair);
		auto collisionLayer = _layers.find(otherLayerPair);
		if (layer != _layers.end() && collisionLayer != _layers.end()) {
			layer->second->RemoveCollisionToLayer(collisionLayer->second);
			collisionLayer->second->RemoveCollisionToLayer(layer->second);
		}
		else
		{
			std::string message = " ";
			if (layer != _layers.end())
			{
				message = "PhysicsManager ERROR in line 37, could not find collision layer: " + layerName + 
					" trying to remove collision with layer: " + collisionToAdd + "\n";
			}
			else
			{
				message = "PhysicsManager ERROR in line 37, could not find collision layer: " + collisionToAdd + 
					" trying to remove collision to layer: " + layerName+ "\n";
			}
			eden_error::ErrorHandler::Instance()->Warning(message.c_str());
		}
	}
}


physics_manager::PhysicsManager::PhysicsManager()
{
	_worldCollisionConfiguration = new btDefaultCollisionConfiguration();
	_worldDispatcher = new btCollisionDispatcher(_worldCollisionConfiguration);
	_worldBroadPhaseInterface = new btDbvtBroadphase();
	_worldConstraintSolver = new btSequentialImpulseConstraintSolver();
	_dynamicWorldRef = new btDiscreteDynamicsWorld(_worldDispatcher, _worldBroadPhaseInterface, _worldConstraintSolver, _worldCollisionConfiguration);
	//Inicializacion de debug drawer
	//_debugDrawer = new eden_debug::DebugDrawer("Debug1");
	//_dynamicWorldRef->setDebugDrawer(_debugDrawer);
	physics_wrapper::RayCast::Instance(_dynamicWorldRef, _debugDrawer);
	_dynamicWorldRef->setGravity({ 0,-10,0 });
}

btDynamicsWorld* physics_manager::PhysicsManager::GetWorld()
{
	return _dynamicWorldRef;
}

inline eden_utils::Vector3 physics_manager::PhysicsManager::GetGravity()
{
	return eden_utils::Vector3(_dynamicWorldRef->getGravity().x(), _dynamicWorldRef->getGravity().y(),
		_dynamicWorldRef->getGravity().z());
}

physics_manager::PhysicsManager::~PhysicsManager()
{
	for(auto it : _layers)
	{
		delete it.second;
	}
	// Toda la memoria din�mica que hemos generado en la constructora, al intentar llamar a su delete aqu�,  hace que el programa explote. 
	// Hay que revisarlo

	if (_debugDrawer) delete _debugDrawer;
	delete _dynamicWorldRef;
	delete _worldConstraintSolver;
	delete _worldBroadPhaseInterface;
	delete _worldDispatcher;
	delete _worldCollisionConfiguration;
	//delete _debugDrawer;
	//if (_physicsDebugDrawer) delete _physicsDebugDrawer;

}

void physics_manager::PhysicsManager::AddPhysicsEntity(eden_ec::Entity* e) {
	_entitiesSet.insert(e);
}

void physics_manager::PhysicsManager::RemovePhysicsEntity(eden_ec::Entity* e) {
	if (!_entitiesSet.erase(e)) {
		eden_error::ErrorHandler::Instance()->Warning("Entity that you were trying to erase from Physics World was not in Physics World at first\n");
	}
}

void physics_manager::PhysicsManager::UpdatePositions() {
	eden_ec::CRigidBody* _rb;
	for (auto ent : _entitiesSet) {
		_rb = ent->GetComponent<eden_ec::CRigidBody>();
		_rb->EdenTransformToPhysicsTransform();
	}
}

void physics_manager::PhysicsManager::ResolvePositions() {
	eden_ec::CRigidBody* _rb;
	for (auto ent : _entitiesSet) {
		_rb = ent->GetComponent<eden_ec::CRigidBody>();
		_rb->PhysicsTransformToEdenTransform();
	}
}

physics_wrapper::CollisionLayer* physics_manager::PhysicsManager::GetLayerByName(std::string name, std::string sceneID) {
	LayerInfo layerPair(name, sceneID);
	auto it = _layers.find(layerPair);
	if (it != _layers.end())
		return it->second;
	else 
		return nullptr;
}

void physics_manager::PhysicsManager::RemoveAllSceneLayers(std::string sceneID) {
	for (auto it = _layers.begin(); it != _layers.end();) {
		if (it->first.GetSceneID() == sceneID) {
			auto eraseIt = it;
			++it;
			delete eraseIt->second;
			_layers.erase(eraseIt);
		}
		else
			++it;
	}
}

physics_manager::LayerInfo::LayerInfo(std::string name, std::string sceneID) : _sceneID(sceneID), _name(name) {}

bool physics_manager::LayerInfo::operator==(const LayerInfo& other) const {
	return _sceneID == other._sceneID && _name == other._name;
}