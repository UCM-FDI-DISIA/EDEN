#include <btBulletDynamicsCommon.h>

#include <ErrorHandler.h>

#include "PhysicsManager.h"
#include <Entity.h>
#include <CRigidBody.h>
#include <Transform.h>
#include "RayCast.h"
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
}

void physics_manager::PhysicsManager::CreateCollisionLayer(std::string name)
{
	auto layerIt = _layers.find(name);
	if (layerIt == _layers.end()) {
		physics_wrapper::CollisionLayer* layer = new physics_wrapper::CollisionLayer(name);
		_layers[name] = layer;
	}
}

void physics_manager::PhysicsManager::AddCollisionToLayer(std::string layerName, std::string collisionToAdd)
{
	auto layer = _layers.find(layerName);
	auto collisionLayer = _layers.find(collisionToAdd);
	if (layer != _layers.end() && collisionLayer != _layers.end()) {
		layer->second->AddCollisionToLayer(collisionLayer->second);
	}
	else
	{
		std::string message = " ";
		if (layer != _layers.end())
		{
			message = "PhysicsManager ERROR in line 37, could not find collision layer: " + layerName + 
				" trying to add collision with layer: " + collisionToAdd + "\n";
		}
		else
		{
			message = "PhysicsManager ERROR in line 37, could not find collision layer: " + collisionToAdd + 
				" trying to add collision to layer: " + layerName+ "\n";
		}
		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
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
	_debugDrawer = new eden_physics::DebugDrawer();
	_dynamicWorldRef->setDebugDrawer(_debugDrawer);
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

	delete _dynamicWorldRef;
	if (_debugDrawer) delete _debugDrawer;

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

physics_wrapper::CollisionLayer* physics_manager::PhysicsManager::GetLayerByName(std::string name) {
	auto it = _layers.find(name);
	if (it != _layers.end())
		return it->second;
	else 
		return nullptr;
}
