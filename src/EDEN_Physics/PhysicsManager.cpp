#include "PhysicsManager.h"
#include "../../dependencies/Bullet/src/src/btBulletDynamicsCommon.h"
#include "../EDEN/Entity.h"
#include "RayCast.h"


const eden_ec::Entity* physics_manager::PhysicsManager::getEntity(const btRigidBody* RBRef) const
{
	if (_entitiesMap.find(RBRef) != _entitiesMap.end()) {
		return _entitiesMap.at(RBRef);
	}
	return nullptr;
}

void physics_manager::PhysicsManager::updateSimulation(float deltaTime)
{
	_dynamicWorldRef->stepSimulation(deltaTime);
}


physics_manager::PhysicsManager::PhysicsManager()
{
	_worldCollisionConfiguration = new btDefaultCollisionConfiguration();
	_worldDispatcher = new btCollisionDispatcher(_worldCollisionConfiguration);
	_worldBroadPhaseInterface = new btDbvtBroadphase();
	_worldConstraintSolver = new btSequentialImpulseConstraintSolver();
	_dynamicWorldRef = new btDiscreteDynamicsWorld(_worldDispatcher, _worldBroadPhaseInterface, _worldConstraintSolver, _worldCollisionConfiguration);
	//Falta mirar como crear un objeto de debug
	//_physicsDebugDrawer = new btIDebugDraw() 
	//_dynamicWorldRef->setDebugDrawer(_physicsDebugDrawer);
	physics_wrapper::RayCast::Instance(_dynamicWorldRef, _physicsDebugDrawer);
}

inline eden_utils::Vector3 physics_manager::PhysicsManager::GetGravity()
{

	return eden_utils::Vector3(_dynamicWorldRef->getGravity().x(), _dynamicWorldRef->getGravity().y(),
		_dynamicWorldRef->getGravity().z());
}

physics_manager::PhysicsManager::~PhysicsManager()
{
	delete _worldDispatcher;
	delete _worldCollisionConfiguration;
	delete _worldConstraintSolver;
	delete _worldBroadPhaseInterface;
	delete _dynamicWorldRef;
	if (_physicsDebugDrawer) delete _physicsDebugDrawer;

}