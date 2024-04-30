#include "Transform.h"
#include <ScriptManager.h>
#include <ComponentArguments.h>

eden_ec::CTransform::CTransform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale) : Component(),
	_position(position), _rotation(rotation), _scale(scale) {};

void eden_ec::CTransform::Init(eden_script::ComponentArguments* args) {
	_position = args->GetValueToVector3("Position");
	_rotation = args->GetValueToQuaternion("Rotation");
	_scale = args->GetValueToVector3("Scale");
}

void eden_ec::CTransform::SetPosition(eden_utils::Vector3 position)
{
	for (eden_ec::CTransform* t : _childrenVector) {
		t->SetPosition(position + (t->_position - t->_parentTransform->_position));
	}
	_position = position;
}

void eden_ec::CTransform::SetRotation(eden_utils::Quaternion rotation)
{
	for (eden_ec::CTransform* t : _childrenVector) t->SetRotation(rotation);
	_rotation = rotation;
}

void eden_ec::CTransform::SetScale(eden_utils::Vector3 scale)
{
	for (eden_ec::CTransform* t : _childrenVector) {
		eden_utils::Vector3 cScale(scale.GetX() * (t->_scale.GetX() / _scale.GetX()), scale.GetY() * (t->_scale.GetY() / _scale.GetY()), scale.GetZ() * (t->_scale.GetZ() / _scale.GetZ()));
		t->SetScale(cScale);
	}
	_scale = scale;
}

void eden_ec::CTransform::Translate(eden_utils::Vector3 position, bool isGlobal)
{
	if (!isGlobal) _position += _rotation * position;
	else _position += position;
	for (eden_ec::CTransform* t : _childrenVector) t->Translate(position);
}

void eden_ec::CTransform::Rotate(float angle, eden_utils::Vector3 axis)
{
	_rotation.RotateArroundPoint(axis, angle);
	for (eden_ec::CTransform* t : _childrenVector) t->RotateAroundObject(this, angle, axis);
}

void eden_ec::CTransform::LocalRotate(float angle, eden_utils::Vector3 axis)
{
	_rotation.RotateArroundPointLocal(axis, angle);
	for (eden_ec::CTransform* t : _childrenVector) t->LocalRotateAroundObject(this, angle, axis);
}

void eden_ec::CTransform::Pitch(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(1.0f, 0.0f, 0.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->RotateAroundObject(this, angle, eden_utils::Vector3(1, 0, 0));
}

void eden_ec::CTransform::LocalPitch(float angle)
{
	_rotation.RotateArroundPointLocal(eden_utils::Vector3(1.0f, 0.0f, 0.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->LocalRotateAroundObject(this, angle, this->GetRight());
}

void eden_ec::CTransform::Yaw(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0.0f, 1.0f, 0.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->RotateAroundObject(this, angle, eden_utils::Vector3(0, 1, 0));
}

void eden_ec::CTransform::LocalYaw(float angle)
{
	_rotation.RotateArroundPointLocal(eden_utils::Vector3(0.0f, 1.0f, 0.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->LocalRotateAroundObject(this, angle, this->GetUp());
}

void eden_ec::CTransform::Roll(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0.0f, 0.0f, 1.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->RotateAroundObject(this, angle, eden_utils::Vector3(0,0,1));
}

void eden_ec::CTransform::LocalRoll(float angle)
{
	_rotation.RotateArroundPointLocal(eden_utils::Vector3(0.0f, 0.0f, 1.0f), angle);
	for (eden_ec::CTransform* t : _childrenVector) t->LocalRotateAroundObject(this, angle, this->GetForward());
}

void eden_ec::CTransform::Escalate(eden_utils::Vector3 scale)
{
	_scale += scale;
	for (eden_ec::CTransform* t : _childrenVector) t->Escalate(scale);
}

eden_utils::Vector3 eden_ec::CTransform::GetForward()
{
	std::array<std::array<float, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(float(rotMat[0][2]), float(rotMat[1][2]), float(rotMat[2][2]));
}

eden_utils::Vector3 eden_ec::CTransform::GetUp()
{
	std::array<std::array<float, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(float(rotMat[0][1]), float(rotMat[1][1]), float(rotMat[2][1]));
}

eden_utils::Vector3 eden_ec::CTransform::GetRight()
{
	std::array<std::array<float, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(float(rotMat[0][0]), float(rotMat[1][0]), float(rotMat[2][0]));
}

void eden_ec::CTransform::SetParent(CTransform* pTr)
{
	pTr->AddChild(this);
}

eden_ec::CTransform* eden_ec::CTransform::GetParent()
{
	return _parentTransform;
}

void eden_ec::CTransform::AddChild(CTransform* cTr)
{
	_childrenVector.push_back(cTr);
	cTr->_parentTransform = this;
}

bool eden_ec::CTransform::RemoveChild(CTransform* cTr)
{
	if (_childrenVector.size() == 0) return false;
	std::vector<CTransform*>::iterator it = _childrenVector.begin();
	while (it != _childrenVector.end() && *it != cTr) {
		++it;
	}
	if (*it == cTr) {
		_childrenVector.erase(it);
		cTr->SetParent(nullptr);
		return true;
	}
	return false;
}

eden_ec::CTransform* eden_ec::CTransform::GetChild(int index)
{
	if (index < 0 || index >= _childrenVector.size()) return nullptr;
	return _childrenVector[index];
}

int eden_ec::CTransform::HasChild(CTransform* cTr)
{
	if (_childrenVector.size() == 0) return -1;
	std::vector<CTransform*>::iterator it = _childrenVector.begin();
	int index = 0;
	while (it != _childrenVector.end() && *it != cTr) {
		++index;
		++it;
	}
	return (*it == cTr ? index : -1);
}

void eden_ec::CTransform::RotateAroundObject(CTransform* other, float angle, eden_utils::Vector3 axis)
{
	Rotate(angle, axis);
	_position = (_position - other->GetPosition()).RotatedAroundPoint(axis, angle) + other->GetPosition();
}

void eden_ec::CTransform::LocalRotateAroundObject(CTransform* other, float angle, eden_utils::Vector3 axis)
{
	LocalRotate(angle, axis);
	_position = (_position - other->GetPosition()).RotatedAroundPoint(axis, angle) + other->GetPosition();
}

