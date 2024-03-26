#define _CRTDBG_MAP_ALLOC
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

#include <ErrorHandler.h>

#include "RigidBody.h"
#include <Transform.h>
#include <Quaternion.h>
#include <Entity.h>
#include "PhysicsManager.h"
#include "CollisionLayer.h"
#include "ShapeCreator.h"
#include "CollisionCallback.h"
#include "PhysicsManager.h"

physics_wrapper::RigidBody::RigidBody(eden_ec::Entity* ent, float mass, const ShapeParameters& params, const RigidBodyType& flag, std::string layerName)
{
	btVector3 localInertia = btVector3();

	_collisionShape = new btCompoundShape();
	_collisionShape->calculateLocalInertia(mass, localInertia);

	AddShape(params);

	eden_ec::CTransform* entTransform = ent->GetComponent<eden_ec::CTransform>();

	btTransform transform = btTransform(EDENToBulletQuaternion(entTransform->GetRotation()), 
		EDENToBulletVector(entTransform->GetPosition()));

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);

	_rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass,
		motionState,
		_collisionShape,
		localInertia));

	switch (flag) {
		case KINEMATIC:
			_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
			break;
		case STATIC:
			_rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
			break;
		case DYNAMIC:
			_rigidBody->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
			break;
	}
	
	physics_manager::PhysicsManager* physicsManager = physics_manager::PhysicsManager::Instance();
	physics_wrapper::CollisionLayer* layer = physicsManager->GetLayerByName(layerName);
	if (layer != nullptr)
	{
		physicsManager->GetWorld()->addRigidBody(_rigidBody, layer->GetLayer(), layer->GetCollisionMask());
	}
	else
	{
		physicsManager->GetWorld()->addRigidBody(_rigidBody);
	}

	// Todos los rigidbodies tienen ahora un puntero a la entidad que los contiene
	_rigidBody->setUserPointer(ent);

	_collisionCallback = new CollisionCallback(this);
}

physics_wrapper::RigidBody::~RigidBody()
{
	btCollisionShape* shape;
	for (int i = 0; i < _collisionShape->getNumChildShapes(); ++i) {
		shape = _collisionShape->getChildShape(i);
		_collisionShape->removeChildShape(shape);
		delete shape;
		shape = nullptr;
	}
	delete _collisionShape;
	delete _collisionCallback;
}


eden_utils::Vector3 physics_wrapper::RigidBody::GetPosition()
{
	btTransform transform = _rigidBody->getWorldTransform();
	return eden_utils::Vector3(BulletToEDENVector(transform.getOrigin()));
}

void physics_wrapper::RigidBody::SetPosition(eden_utils::Vector3 position)
{
	_rigidBody->getWorldTransform().setOrigin(EDENToBulletVector(position));
}

eden_utils::Quaternion physics_wrapper::RigidBody::GetRotation()
{
	btTransform transform = _rigidBody->getWorldTransform();
	return eden_utils::Quaternion(BulletToEDENQuaternion(transform.getRotation()));
}

void physics_wrapper::RigidBody::SetRotation(eden_utils::Quaternion rotation)
{
	_rigidBody->getWorldTransform().setRotation(EDENToBulletQuaternion(rotation));
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
	// Si se trata de un objeto estatico no se puede cambiar su masa ya que esta debe ser siempre 0 para que se mantenga
	// estatico
	if (_rigidBody->getCollisionFlags() == btCollisionObject::CF_STATIC_OBJECT) {
		eden_error::ErrorHandler::Instance()->Warning("Tried changing mass of a static objects. An static object mass must be 0 always for it to remain static.");
		return;
	}
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

void physics_wrapper::RigidBody::SetScale(eden_utils::Vector3 scale)
{
	_collisionShape->setLocalScaling(EDENToBulletVector(scale));
}

void physics_wrapper::RigidBody::ApplyTorque(eden_utils::Vector3 torque)
{
	_rigidBody->applyTorque(EDENToBulletVector(torque));
}

void physics_wrapper::RigidBody::ClearForce()
{
	_rigidBody->clearForces();
}

void physics_wrapper::RigidBody::AddShape(const ShapeParameters& params)
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

btRigidBody* physics_wrapper::RigidBody::getBulletRigidBody() {
	return _rigidBody;
}
