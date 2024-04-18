#define _CRTDBG_MAP_ALLOC
#include <iostream>

#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

#include "PhysicsManager.h"
#include "Entity.h"
#include "CRigidBody.h"
#include "Transform.h"
#include "RayCast.h"
#include "RigidBody.h"
#include "CollisionCallback.h"
#include "CollisionLayer.h"
#include "Debug.h"
#include "ErrorHandler.h"

void physics_manager::PhysicsManager::updateSimulation(float deltaTime, std::string sceneID)
{
	_currentPhysicScene->stepSimulation(deltaTime);
	physics_wrapper::RigidBody* _rb;
	std::unordered_set<eden_ec::Entity*>* currentEnts = &_physicsScenes[sceneID]->_entitiesSet;
	for (auto ent : (*currentEnts)) {
//#ifdef _DEBUG
		info->GetDebug()->ClearLines();
		info->GetDebug()->DrawRigidBody(ent->GetComponent<eden_ec::CRigidBody>(), { 1,0,0 });
		//info->GetDebug()->DrawLine(_rb->GetPosition(), {100,0,100}, {1,1,1});
//#endif
		_rb = ent->GetComponent<eden_ec::CRigidBody>()->_rb;
		_currentPhysicScene->contactTest(_rb->getBulletRigidBody(), *_rb->_collisionCallback);
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
	_defaultGravity = eden_utils::Vector3(0,-10,0);

	_currentPhysicScene = nullptr;

	//Inicializacion de debug drawer
	//_dynamicWorldRef->setDebugDrawer(_debugDrawer);
	//physics_wrapper::RayCast::Instance(_dynamicWorldRef, _debugDrawer);
}

btDynamicsWorld* physics_manager::PhysicsManager::GetWorld(std::string sceneID)
{
	auto sceneIt = _physicsScenes.find(sceneID);
	if (sceneIt != _physicsScenes.end())
	{
		return sceneIt->second->GetWorld();
	}
	else
	{
		std::string message = "PhysicsManager error, the world you are trying to get does no exist";
		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
		return nullptr;
	}
}

inline eden_utils::Vector3 physics_manager::PhysicsManager::GetGravity(std::string sceneID)
{
	auto sceneIt = _physicsScenes.find(sceneID);
	if (sceneIt != _physicsScenes.end())
	{
		btDynamicsWorld* world = sceneIt->second->GetWorld();
		return eden_utils::Vector3(world->getGravity().x(), world->getGravity().y(),
			world->getGravity().z());
	}
	else
	{
		std::string message = "PhysicsManager ERROR in line 108 could not find scene: " + sceneID
			+ " \nUsing default gravity.";
		
		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
		return eden_utils::Vector3(0,0,0);
	}
}

physics_manager::PhysicsManager::~PhysicsManager()
{
	for(auto it : _layers)
	{
		delete it.second;
	}
	for (auto it : _physicsScenes)
	{
		delete it.second;
	}


}

void physics_manager::PhysicsManager::AddPhysicsEntity(eden_ec::Entity* e) {
	std::unordered_map<std::string, InfoPhysicWorld*>::iterator it = _physicsScenes.find(e->GetSceneID());
	if (it != _physicsScenes.end())
	{
		if(e != nullptr)
			it->second->_entitiesSet.insert(e);
	}
	else
	{
		std::string message = "PhysicsManager ERROR in line 147 could not find scene: " + e->GetSceneID()
			+ "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void physics_manager::PhysicsManager::RemovePhysicsEntity(eden_ec::Entity* e) {
	std::unordered_map<std::string, InfoPhysicWorld*>::iterator it = _physicsScenes.find(e->GetSceneID());
	if (it != _physicsScenes.end())
	{
		if(e != nullptr)
			it->second->_entitiesSet.erase(e);
	}
	else
	{
		std::string message = "PhysicsManager ERROR in line 147 could not find scene: " + e->GetSceneID()
			+ "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void physics_manager::PhysicsManager::UpdatePositions(std::string sceneID) {
	eden_ec::CRigidBody* _rb;
	std::unordered_set<eden_ec::Entity*>* currentEnts = &_physicsScenes[sceneID]->_entitiesSet;
	for (auto ent : (*currentEnts)) {
		_rb = ent->GetComponent<eden_ec::CRigidBody>();

		_rb->EdenTransformToPhysicsTransform();
	}
}

void physics_manager::PhysicsManager::ResolvePositions(std::string sceneID) {
	eden_ec::CRigidBody* _rb;
	std::unordered_set<eden_ec::Entity*>* currentEnts = &_physicsScenes[sceneID]->_entitiesSet;
	for (auto ent : (*currentEnts)) {
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

btDynamicsWorld* physics_manager::InfoPhysicWorld::GetWorld()
{
	return _dynamicWorld;
}

void physics_manager::PhysicsManager::CreatePhysicsScene(std::string sceneID)
{
	auto sceneIt = _physicsScenes.find(sceneID);
	if (sceneIt == _physicsScenes.end())
	{
		info = new InfoPhysicWorld(sceneID);
		_currentPhysicScene = info->GetWorld();
		_currentPhysicScene->setGravity(btVector3(_defaultGravity.GetX(), _defaultGravity.GetY(), _defaultGravity.GetZ()));
		_physicsScenes[sceneID] = info;
	}
	else
	{
		_currentPhysicScene = sceneIt->second->GetWorld();
	}
}

void physics_manager::PhysicsManager::RemovePhysicsScene(std::string sceneToRemoveID, std::string newCurrentSceneID)
{
	auto sceneIt = _physicsScenes.find(sceneToRemoveID);
	if (sceneIt != _physicsScenes.end())
	{
		delete sceneIt->second;
		_physicsScenes.erase(sceneIt);

	}
	else {
		std::string message = "Tried to delete scene: " + sceneToRemoveID + " But such scene does not exist\n";
		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
	CreatePhysicsScene(newCurrentSceneID);
}

physics_manager::LayerInfo::LayerInfo(std::string name, std::string sceneID) : _sceneID(sceneID), _name(name) {}

bool physics_manager::LayerInfo::operator==(const LayerInfo& other) const {
	return _sceneID == other._sceneID && _name == other._name;
}

physics_manager::InfoPhysicWorld::InfoPhysicWorld(std::string sceneID)
{
	_worldCollisionConfiguration = new btDefaultCollisionConfiguration();
	_worldDispatcher = new btCollisionDispatcher(_worldCollisionConfiguration);
	_worldBroadPhaseInterface = new btDbvtBroadphase();
	_worldConstraintSolver = new btSequentialImpulseConstraintSolver();
	_dynamicWorld = new btDiscreteDynamicsWorld(_worldDispatcher, _worldBroadPhaseInterface, _worldConstraintSolver, _worldCollisionConfiguration);
//#ifdef _DEBUG
	_debug = new eden_debug::Debug("Debug" + sceneID, sceneID);
	_debug->SetDebugMode(2);
//#endif
}

physics_manager::InfoPhysicWorld::~InfoPhysicWorld()
{
	delete _dynamicWorld;
	delete _worldConstraintSolver;
	delete _worldBroadPhaseInterface;
	delete _worldDispatcher;
	delete _worldCollisionConfiguration;
//#ifdef _DEBUG
	delete _debug;
//#endif
}

//#ifdef _DEBUG
eden_debug::Debug* physics_manager::InfoPhysicWorld::GetDebug()
{
	return _debug;
}
//#endif
