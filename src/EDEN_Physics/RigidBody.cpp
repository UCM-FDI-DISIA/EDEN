#include "RigidBody.h"
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>ç
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include<EDEN/Transform.h>
#include<EDEN/Vector3.h>
#include<EDEN/Quaternion.h>

#include "PhysicsManager.h"
#include "ShapeCreator.h"

physics_wrapper::RigidBody::RigidBody(eden_ec::CTransform transform, float mass, shapeParameters params)
{
	_transform = new btTransform(EDENToBulletQuaternion(transform.GetRotation()), EDENToBulletVector(transform.GetPosition()));

	_collisionShape = new btCompoundShape();
	AddShape(params);

	btDefaultMotionState* motionState = new btDefaultMotionState(*_transform);
	btVector3 localInertia = btVector3();
	_collisionShape->calculateLocalInertia(mass, localInertia);

	_rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass,
		motionState,
		_collisionShape,
		localInertia));

	physics_manager::PhysicsManager::Instance()->GetWorld()->addRigidBody(_rigidBody);
}

physics_wrapper::RigidBody::~RigidBody()
{
	delete _transform;


	for (int i = 0; i < _collisionShape->getNumChildShapes(); ++i) {
		btCollisionShape* shape = _collisionShape->getChildShape(i);
		_collisionShape->removeChildShape(shape);
		delete shape;
	}
	delete _collisionShape;
}

eden_utils::Vector3 physics_wrapper::RigidBody::GetPosition()
{
	return eden_utils::Vector3(BulletToEDENVector(_transform->getOrigin()));
}

void physics_wrapper::RigidBody::SetPosition(eden_utils::Vector3 position)
{
	_transform->setOrigin(EDENToBulletVector(position));
	_rigidBody->getMotionState()->setWorldTransform(*_transform);
}

eden_utils::Quaternion physics_wrapper::RigidBody::GetRotation()
{
	return eden_utils::Quaternion(BulletToEDENQuaternion(_transform->getRotation()));
}

void physics_wrapper::RigidBody::SetRotation(eden_utils::Quaternion rotation)
{
	_transform->setRotation(EDENToBulletQuaternion(rotation));
	_rigidBody->getMotionState()->setWorldTransform(*_transform);
}

eden_utils::Vector3 physics_wrapper::RigidBody::GetLinearVelocity()
{
	return eden_utils::Vector3(BulletToEDENVector(_rigidBody->getLinearVelocity()));
}

void physics_wrapper::RigidBody::SetLinealVelocity(eden_utils::Vector3 velocity)
{
	_rigidBody->setLinearVelocity(EDENToBulletVector(velocity));
}

void physics_wrapper::RigidBody::AddLinearVelocity(eden_utils::Vector3 velocity)
{
	_rigidBody->setLinearVelocity(_rigidBody->getLinearVelocity() + EDENToBulletVector(velocity));
}

eden_utils::Vector3 physics_wrapper::RigidBody::GetAngularVelocity()
{
	return eden_utils::Vector3(BulletToEDENVector(_rigidBody->getAngularVelocity()));
}

void physics_wrapper::RigidBody::SetAngularVelocity(eden_utils::Vector3 velocity)
{
	_rigidBody->setAngularVelocity(EDENToBulletVector(velocity));
}

void physics_wrapper::RigidBody::AddAngularVelocity(eden_utils::Vector3 velocity)
{
	_rigidBody->setAngularVelocity(_rigidBody->getAngularVelocity() + EDENToBulletVector(velocity));
}

float physics_wrapper::RigidBody::GetMass()
{
	return _rigidBody->getMass();
}

void physics_wrapper::RigidBody::SetMass(float mass)
{
	btVector3 localInertia;
	_collisionShape->calculateLocalInertia(mass, localInertia);
	_rigidBody->setCollisionShape(_collisionShape);
}

eden_utils::Vector3 physics_wrapper::RigidBody::GetGravity()
{
	return eden_utils::Vector3(BulletToEDENVector(_rigidBody->getGravity()));
}

void physics_wrapper::RigidBody::SetGravity(eden_utils::Vector3 gravity)
{
	_rigidBody->setGravity(EDENToBulletVector(gravity));
}

float physics_wrapper::RigidBody::GetDamping()
{
	return _rigidBody->getLinearDamping();
}

void physics_wrapper::RigidBody::SetDamping(float damping)
{
	_rigidBody->setDamping(damping, damping);
}

void physics_wrapper::RigidBody::ApplyForce(eden_utils::Vector3 force)
{
	_rigidBody->applyCentralForce(EDENToBulletVector(force));
}

void physics_wrapper::RigidBody::ApplyTorque(eden_utils::Vector3 torque)
{
	_rigidBody->applyTorque(EDENToBulletVector(torque));
}

void physics_wrapper::RigidBody::ClearForce()
{
	_rigidBody->clearForces();
}

void physics_wrapper::RigidBody::AddShape(shapeParameters params)
{
	btCollisionShape* shape;
	switch (params.type) {
	case ShapeType::BOX:
		shape = ShapeCreator::CreateBox(params.length);
		break;
	case ShapeType::CAPSULE:
		shape = ShapeCreator::CreateCapsule(params.radius, params.length.GetY());
		break;
	case ShapeType::CYLINDER:
		shape = ShapeCreator::CreateCylinder(params.length);
		break;
	case ShapeType::SPHERE:
		shape = ShapeCreator::CreateSphere(params.radius);
		break;
	default:
		shape = ShapeCreator::CreateBox(1, 1, 1);
	}

	_collisionShape->addChildShape(btTransform(EDENToBulletQuaternion(eden_utils::Quaternion::Identity()), EDENToBulletVector(params.positionOffset)),
		shape);
}

btVector3 physics_wrapper::RigidBody::EDENToBulletVector(eden_utils::Vector3 vector)
{
	return btVector3(vector.GetX(), vector.GetY(), vector.GetZ());
}

eden_utils::Vector3 physics_wrapper::RigidBody::BulletToEDENVector(btVector3 vector)
{
	return eden_utils::Vector3(vector.getX(), vector.getY(), vector.getZ());
}

btQuaternion physics_wrapper::RigidBody::EDENToBulletQuaternion(eden_utils::Quaternion quaternion)
{
	return btQuaternion(quaternion.Complex().GetX(), quaternion.Complex().GetY(), quaternion.Complex().GetZ(), quaternion.Real());
}

eden_utils::Quaternion physics_wrapper::RigidBody::BulletToEDENQuaternion(btQuaternion quaternion)
{
	return eden_utils::Quaternion(quaternion.getW(), quaternion.getX(), quaternion.getY(), quaternion.getZ());
}
