#include "RigidBody.h"
#include "PhysicsManager.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

physics_wrapper::RigidBody::RigidBody(const RigidBodyConstruction& rb) {
	_physicsManagerInstance = physics_manager::PhysicsManager::Instance();
	btVector3 grav(_physicsManagerInstance->GetGravity());
	//_gravity(grav.x, grav.y, grav.x);
}

physics_wrapper::RigidBody::~RigidBody() {
	delete _physicsManagerInstance;
}
