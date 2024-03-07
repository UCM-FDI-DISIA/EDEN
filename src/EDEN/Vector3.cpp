#include<math.h>
#include<assert.h>

#include "Vector3.h"

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
	return sqrt((_x * _x) + (_y * _y) + (_z * _z));
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
	return *this / Magnitude();
}

float eden_utils::Vector3::Dot(Vector3 other)
{
	return _x * other._x + _y * other._y + _z * other._z;
}

eden_utils::Vector3 eden_utils::Vector3::Cross(Vector3 other)
{
	return Vector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}
