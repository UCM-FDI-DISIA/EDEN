#include "Transform.h"
#include "Vector3.h"
#include "Quaternion.h"

void eden_ec::Transform::translate(eden_utils::Vector3 position)
{
	_position += position;
}

void eden_ec::Transform::rotate(float angle, eden_utils::Vector3 axis)
{
	_rotation.rotateArroundPoint(axis, angle);
}

void eden_ec::Transform::pitch(float angle)
{
	_rotation.rotateArroundPoint(eden_utils::Vector3(1, 0, 0), angle);
}

void eden_ec::Transform::yaw(float angle)
{
	_rotation.rotateArroundPoint(eden_utils::Vector3(0, 1, 0), angle);
}

void eden_ec::Transform::roll(float angle)
{
	_rotation.rotateArroundPoint(eden_utils::Vector3(0, 0, 1), angle);
}

void eden_ec::Transform::escalate(eden_utils::Vector3 scale)
{
	_scale += scale;
}
