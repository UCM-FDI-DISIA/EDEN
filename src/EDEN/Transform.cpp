#include "Transform.h"
#include "Vector3.h"
#include "Quaternion.h"

const std::string eden_ec::Transform::_id = "TRASNFORM";

eden_ec::Transform::Transform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale) : Component(),
	_position(position), _rotation(rotation), _scale(scale) {};

void eden_ec::Transform::Translate(eden_utils::Vector3 position)
{
	_position += position;
}

void eden_ec::Transform::Rotate(float angle, eden_utils::Vector3 axis)
{
	_rotation.RotateArroundPoint(axis, angle);
}

void eden_ec::Transform::Pitch(float angle, AXIS_REFERENCE axis_system)
{
	axis_system == AXIS_WORLD ? _rotation.RotateArroundPoint(eden_utils::Vector3(1, 0, 0), angle) : _rotation.RotateArroundPoint(GetRight(), angle);
}

void eden_ec::Transform::Yaw(float angle, AXIS_REFERENCE axis_system)
{
	axis_system == AXIS_WORLD ? _rotation.RotateArroundPoint(eden_utils::Vector3(0, 1, 0), angle) : _rotation.RotateArroundPoint(GetUp(), angle);
}

void eden_ec::Transform::Roll(float angle, AXIS_REFERENCE axis_system)
{
	axis_system == AXIS_WORLD ? _rotation.RotateArroundPoint(eden_utils::Vector3(0, 0, 1), angle) : _rotation.RotateArroundPoint(GetForward(), angle);
}

void eden_ec::Transform::Escalate(eden_utils::Vector3 scale)
{
	_scale += scale;
}

eden_utils::Vector3 eden_ec::Transform::GetForward()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][2], rotMat[1][2], rotMat[2][2]);
}

eden_utils::Vector3 eden_ec::Transform::GetUp()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][1], rotMat[1][1], rotMat[2][1]);
}

eden_utils::Vector3 eden_ec::Transform::GetRight()
{
	std::array<std::array<int, 3>, 3> rotMat = _rotation.GetRotationMatrix();
	return eden_utils::Vector3(rotMat[0][0], rotMat[1][0], rotMat[2][0]);
}
