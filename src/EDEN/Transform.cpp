#define _CRTDBG_MAP_ALLOC
#include "Transform.h"
#include <ScriptManager.h>
#include <ComponentArguments.h>

const std::string eden_ec::CTransform::_id = "TRANSFORM";

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
	_rotation.RotateArroundPoint(eden_utils::Vector3(1.0f, 0.0f, 0.0f), angle);
}

void eden_ec::CTransform::Yaw(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0.0f, 1.0f, 0.0f), angle);
}

void eden_ec::CTransform::Roll(float angle)
{
	_rotation.RotateArroundPoint(eden_utils::Vector3(0.0f, 0.0f, 1.0f), angle);
}

void eden_ec::CTransform::Escalate(eden_utils::Vector3 scale)
{
	_scale += scale;
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
