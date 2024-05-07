#define _CRTDBG_MAP_ALLOC
#include "CRigidBody.h"
#include <ComponentArguments.h>
#include <PhysicsManager.h>
#include "Entity.h"
#include "RayCast.h"
#include "CLuaBehaviour.h"
#include "ErrorHandler.h"

void eden_ec::CRigidBody::Start()
{
	//Se comprueba si la entidad tiene o no un transform, en cuyo caso lo crea y lo aniade
	if(_ent->GetComponent<CLuaBehaviour>() != nullptr)
		_behaviour = _ent->GetComponent<CLuaBehaviour>();
}

void eden_ec::CRigidBody::Awake() {
	if (_ent->GetComponent<CTransform>() != nullptr) {
		_transform = _ent->GetComponent<CTransform>();
		_rb = new physics_wrapper::RigidBody(_ent, _params, _mass, _friction, _restitution, _type, &_layer, _isTrigger);
		physics_manager::PhysicsManager::Instance()->AddPhysicsEntity(_ent);
	}
}

physics_wrapper::CollisionLayer* eden_ec::CRigidBody::GetCollisionLayer() {
	return physics_manager::PhysicsManager::Instance()->GetLayerByName(_layer, _ent->GetSceneID());
}

std::string eden_ec::CRigidBody::GetCollisionLayerName() {
	return _layer;
}

physics_wrapper::RigidBody* eden_ec::CRigidBody::GetWrapperRigidBody()
{
	return _rb;
}



void eden_ec::CRigidBody::Update(float t)
{
	_rb->Update();
}

void eden_ec::CRigidBody::HandleInput()
{

}

void eden_ec::CRigidBody::Init(eden_script::ComponentArguments* args) {
	
	_mass = args->GetValueToFloat("Mass");
	_restitution = args->GetValueToFloat("Bounciness");
	_friction = args->GetValueToFloat("Friction");
	_params.length = args->GetValueToVector3("AABB");
	_params.positionOffset = args->GetValueToVector3("PosOffset");
	_params.radius = args->GetValueToFloat("Radius");
	_isTrigger = args->GetValueToBool("Trigger");
	if (_params.length.GetX() < 0 || _params.length.GetY() < 0 || _params.length.GetZ() < 0 || _params.radius < 0)
		eden_error::ErrorHandler::Instance()->Exception("Size was negative", "CRigdBody ERROR in line 52/54");

	std::string shape = args->GetValueToString("Shape");

	if(shape == "CYLINDER") _params.type = physics_wrapper::RigidBody::CYLINDER;
	else if(shape == "SPHERE") _params.type = physics_wrapper::RigidBody::SPHERE;
	else if(shape == "CAPSULE") _params.type = physics_wrapper::RigidBody::CAPSULE;
	else _params.type = physics_wrapper::RigidBody::BOX; // BOX por defecto

	std::string flag = args->GetValueToString("CollisionFlag");
	if (flag == "STATIC") { _type = physics_wrapper::RigidBody::STATIC; _mass = 0; }
	else if (flag == "KINEMATIC") _type = physics_wrapper::RigidBody::KINEMATIC;
	else _type = physics_wrapper::RigidBody::DYNAMIC; // DYNAMIC por defecto

	_layer = args->GetValueToString("CollisionLayer");
}

void eden_ec::CRigidBody::SetTemporalDeactivation(bool input)
{
	_rb->SetTemporalDeactivation(input);
}

eden_ec::CRigidBody::~CRigidBody()
{
	physics_manager::PhysicsManager::Instance()->RemovePhysicsEntity(_ent);
	delete _rb;
}

float eden_ec::CRigidBody::GetBounciness() {
	return _rb->GetBounciness();
}

float eden_ec::CRigidBody::GetFriction() {
	return _rb->GetFriction();
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

void eden_ec::CRigidBody::OnCollisionEnter(eden_ec::Entity* other)
{
	if (_behaviour != nullptr)
		_behaviour->OnCollisionEnter(_ent, other);
}

void eden_ec::CRigidBody::OnCollisionStay(eden_ec::Entity* other)
{
	if (_behaviour != nullptr)
		_behaviour->OnCollisionStay(_ent, other);
}

void eden_ec::CRigidBody::OnCollisionExit(eden_ec::Entity* other)
{
	if (_behaviour != nullptr)
		_behaviour->OnCollisionExit(_ent, other);
}
