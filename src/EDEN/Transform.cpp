#include "Transform.h"

#include "ScriptManager.h"
#include "ComponentArguments.h"

const std::string eden_ec::CTransform::_id = "TRANsFORM";

eden_ec::CTransform::CTransform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale) : Component(),
	_position(position), _rotation(rotation), _scale(scale) {};

void eden_ec::CTransform::Init(eden_script::ComponentArguments* args) {
	_position = args->GetValueToVector3("Position");
	_rotation = args->GetValueToQuaternion("Rotation");
	_scale = args->GetValueToVector3("Scale");
}

void eden_ec::CTransform::Translate(eden_utils::Vector3 position)
{
	_position += position;
}

void eden_ec::CTransform::Rotate(float angle, eden_utils::Vector3 axis)
{
	_rotation.RotateArroundPoint(axis, angle);
}

void eden_ec::CTransform::Pitch(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(1, 0, 0), angle);
}

void eden_ec::CTransform::Yaw(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0, 1, 0), angle);
}

void eden_ec::CTransform::Roll(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0, 0, 1), angle);
}

void eden_ec::CTransform::Escalate(eden_utils::Vector3 scale)
{
	_scale += scale;
}

eden_utils::Vector3 eden_ec::CTransform::GetForward()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][2], rotMat[1][2], rotMat[2][2]);
}

eden_utils::Vector3 eden_ec::CTransform::GetUp()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][1], rotMat[1][1], rotMat[2][1]);
}

eden_utils::Vector3 eden_ec::CTransform::GetRight()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][0], rotMat[1][0], rotMat[2][0]);
}
