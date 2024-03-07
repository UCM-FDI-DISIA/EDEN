#include "RigidBody.h"
#include "PhysicsManager.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

physics_wrapper::RigidBody::RigidBody(const RigidBodyConstruction& rb) {
	_physicsManagerInstance = physics_manager::PhysicsManager::Instance();
	_gravity = (_physicsManagerInstance->GetGravity());
}

void physics_wrapper::RigidBody::applyForce(eden_utils::Vector3 force)
{
}

void physics_wrapper::RigidBody::ClearForces()
{
}

physics_wrapper::RigidBody::~RigidBody() {
	delete _physicsManagerInstance;
}
