#include "CRigidBody.h"
#include "RigidBody.h"
#include "ComponentArguments.h"
#include "Entity.h"

const std::string eden_ec::CRigidBody::_id = "RIGIDBODY";

void eden_ec::CRigidBody::InitComponent()
{
	//Se comprueba si la entidad tiene o no un transform, en cuyo caso lo crea y lo añade
	if (_ent->GetComponent<CTransform>() != nullptr) {
		_transform = _ent->GetComponent<CTransform>();
		_rb = new physics_wrapper::RigidBody(_ent, _mass, _params);
	}

}

void eden_ec::CRigidBody::Update(float t)
{
	
}

void eden_ec::CRigidBody::HandleInput()
{

}

void eden_ec::CRigidBody::Init(eden_script::ComponentArguments* args) {
	
	_mass = args->GetValueToFloat("Mass");
	_params.length = args->GetValueToVector3("AABB");
	_params.positionOffset = args->GetValueToVector3("PosOffset");
	_params.radius = args->GetValueToFloat("Radius");

	std::string shape = args->GetValueToString("Shape");

	if (shape == "BOX") _params.type = physics_wrapper::RigidBody::BOX;
	else if(shape == "CYLINDER") _params.type = physics_wrapper::RigidBody::CYLINDER;
	else if(shape == "SPHERE") _params.type = physics_wrapper::RigidBody::SPHERE;
	else if(shape == "CAPSULE") _params.type = physics_wrapper::RigidBody::CAPSULE;

}

eden_ec::CRigidBody::~CRigidBody()
{
	delete _rb;
}

void eden_ec::CRigidBody::EdenTransformToPhysicsTransform()
{
	//Se modifican las componentes del transform del wrapper conforme a los valores del de EDEN
	_rb->SetPosition(_transform->GetPosition());
	_rb->SetRotation(_transform->GetRotation());
	_rb->SetScale(_transform->GetScale());
}

void eden_ec::CRigidBody::PhysicsTransformToEdenTransform()
{
	//Se modifican las componentes del transform de EDEN conforme a los valores del rigidbody wrapper
	_transform->SetPosition(_rb->GetPosition());
	_transform->SetRotation(_rb->GetRotation());
}

eden_utils::Vector3 eden_ec::CRigidBody::GetLinearVelocity()
{
	return _rb->GetLinearVelocity();
}

void eden_ec::CRigidBody::SetLinealVelocity(eden_utils::Vector3 velocity)
{
	_rb->SetLinealVelocity(velocity);
}

void eden_ec::CRigidBody::AddLinearVelocity(eden_utils::Vector3 velocity)
{
	_rb->AddLinearVelocity(velocity);
}

eden_utils::Vector3 eden_ec::CRigidBody::GetAngularVelocity()
{
	return _rb->GetAngularVelocity();
}

void eden_ec::CRigidBody::SetAngularVelocity(eden_utils::Vector3 velocity)
{
	_rb->SetAngularVelocity(velocity);
}

void eden_ec::CRigidBody::AddAngularVelocity(eden_utils::Vector3 velocity)
{
	_rb->AddAngularVelocity(velocity);
}

float eden_ec::CRigidBody::GetMass()
{
	return _rb->GetMass();
}

void eden_ec::CRigidBody::SetMass(float mass)
{
	_rb->SetMass(mass);
}

eden_utils::Vector3 eden_ec::CRigidBody::GetGravity()
{
	return _rb->GetGravity();
}

void eden_ec::CRigidBody::SetGravity(eden_utils::Vector3 gravity)
{
	_rb->SetGravity(gravity);
}

float eden_ec::CRigidBody::GetDamping()
{
	return _rb->GetDamping();
}

void eden_ec::CRigidBody::SetDamping(float damping)
{
	_rb->SetDamping(damping);
}

void eden_ec::CRigidBody::ApplyForce(eden_utils::Vector3 force)
{
	_rb->ApplyForce(force);
}

void eden_ec::CRigidBody::ApplyTorque(eden_utils::Vector3 torque)
{
	_rb->ApplyTorque(torque);
}

void eden_ec::CRigidBody::ClearForce()
{
	_rb->ClearForce();
}