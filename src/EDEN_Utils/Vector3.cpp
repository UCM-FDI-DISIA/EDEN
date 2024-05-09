#include <math.h>
#include <assert.h>

#include "Vector3.h"
#include "Quaternion.h"

eden_utils::Vector3::Vector3()
{
	_x = _y = _z = 0;
}

eden_utils::Vector3::Vector3(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

eden_utils::Vector3 eden_utils::Vector3::operator=(Vector3 other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;

	return *this;
}

eden_utils::Vector3 eden_utils::Vector3::operator+(Vector3 other)
{
	return Vector3(_x + other._x, _y + other._y, _z + other._z);
}

eden_utils::Vector3 eden_utils::Vector3::operator-(Vector3 other)
{
	return Vector3(_x - other._x, _y - other._y, _z - other._z);
}

eden_utils::Vector3 eden_utils::Vector3::operator*(float scalar)
{
	return Vector3(_x * scalar, _y * scalar, _z * scalar);
}

eden_utils::Vector3 eden_utils::Vector3::operator/(float scalar)
{
	assert(scalar != 0);
	return Vector3(_x / scalar, _y / scalar, _z / scalar);
}

eden_utils::Vector3 eden_utils::Vector3::operator+=(Vector3 other)
{
	_x += other._x;
	_y += other._y;
	_z += other._z;

	return *this;
}

eden_utils::Vector3 eden_utils::Vector3::operator-=(Vector3 other)
{
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;

	return *this;
}

eden_utils::Vector3 eden_utils::Vector3::operator*=(float scalar)
{
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;

	return *this;
}

eden_utils::Vector3 eden_utils::Vector3::operator/=(float scalar)
{
	assert(scalar != 0);
	_x /= scalar;
	_y /= scalar;
	_z /= scalar;

	return *this;
}

float eden_utils::Vector3::Magnitude()
{
	return float(sqrt((_x * _x) + (_y * _y) + (_z * _z)));
}

void eden_utils::Vector3::Normalize()
{
	float m = Magnitude();

	_x /= m;
	_y /= m;
	_z /= m;
}

eden_utils::Vector3 eden_utils::Vector3::Normalized()
{
	return Magnitude() == 0 ? Vector3(0, 0, 0) : *this / Magnitude();
}

float eden_utils::Vector3::Dot(Vector3 other)
{
	return _x * other._x + _y * other._y + _z * other._z;
}

eden_utils::Vector3 eden_utils::Vector3::Cross(Vector3 other)
{
	return Vector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}

eden_utils::Vector3 eden_utils::Vector3::RotatedAroundPoint(Vector3 axis, float angle)
{
	angle = angle * 3.1415f / 180.0f;

	Vector3 normalized = this->Normalized();
	Vector3 axisNormalized = axis.Normalized();

	float u = axisNormalized.GetX(), v = axisNormalized.GetY(), w = axisNormalized.GetZ();

	return *this * cos(angle) + axisNormalized.Cross(*this) * sin(angle) + axisNormalized * this->Dot(axisNormalized) * (1 - cos(angle));
}

std::array<std::array<float, 3>, 3> eden_utils::Vector3::GetRotationMatrix(Vector3 axis, float angle)
{
	angle = angle * 3.1415f / 180.0f;

	Vector3 axisNormalized = axis.Normalized();

	float u = axisNormalized.GetX(), v = axisNormalized.GetY(), w = axisNormalized.GetZ();

	std::array<std::array<float, 3>, 3> rotMat;
	rotMat[0][0] = cos(angle) + ((u * u) * (1 - cos(angle)));
	rotMat[0][1] = (u * v + (1 - cos(angle)) - w * sin(angle));
	rotMat[0][2] = (u * w * (1 - cos(angle)) + v * sin(angle));
	rotMat[1][0] = (u * v * (1 - cos(angle)) + w * sin(angle));
	rotMat[1][1] = cos(angle) + ((v * v) * (1 - cos(angle)));
	rotMat[1][2] = (v * w * (1 - cos(angle)) - u * sin(angle));
	rotMat[2][0] = (u * w * (1 - cos(angle)) - v * sin(angle));
	rotMat[2][1] = (v * w * (1 - cos(angle)) + u * sin(angle));
	rotMat[2][2] = cos(angle) + ((w * w) * (1 - cos(angle)));

	return rotMat;
}
