#include <assert.h>
#include <math.h>

#include "Quaternion.h"
#include "Vector3.h"

eden_utils::Quaternion::Quaternion() {
	_x = _y = _z = 0;
	_w = 1.0f;
}

eden_utils::Quaternion::Quaternion(float w, float x, float y, float z) {
	_w = w;
	_x = x;
	_y = y;
	_z = z;
}

eden_utils::Quaternion::Quaternion(float angle, Vector3 axis)
{
	angle = (angle * float(PI)) / 180.0f;
	_w = float(cos(angle / 2.0f));
	_x = axis.GetX() * float(sin(angle / 2.0f));
	_y = axis.GetY() * float(sin(angle / 2.0f));
	_z = axis.GetZ() * float(sin(angle / 2.0f));
}

eden_utils::Quaternion eden_utils::Quaternion::UnitQuaternion(Vector3 axis, float angle)
{
	return Quaternion(angle, axis).Normalized();
}

eden_utils::Vector3 eden_utils::Quaternion::operator*(const eden_utils::Vector3& v) const {
	std::array<std::array<float, 3>, 3> rotMax = GetRotationMatrix();

	float rX = rotMax[0][0] * v.GetX() + rotMax[0][1] * v.GetY() + rotMax[0][2] * v.GetZ();
	float rY = rotMax[1][0] * v.GetX() + rotMax[1][1] * v.GetY() + rotMax[1][2] * v.GetZ();
	float rZ = rotMax[2][0] * v.GetX() + rotMax[2][1] * v.GetY() + rotMax[2][2] * v.GetZ();

	return Vector3(rX, rY, rZ);
}

eden_utils::Quaternion eden_utils::Quaternion::operator=(Quaternion other)
{
	_w = other._w;
	_x = other._x;
	_y = other._y;
	_z = other._z;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::operator+(Quaternion other)
{
	return Quaternion(_w + other._w, _x + other._x, _y + other._y, _z + other._z);
}

eden_utils::Quaternion eden_utils::Quaternion::operator-(Quaternion other)
{
	return Quaternion(_w - other._w, _x - other._x, _y - other._y, _z - other._z);
}

eden_utils::Quaternion eden_utils::Quaternion::operator*(Quaternion other)
{
	return Quaternion(_w * other._w - _x * other._x - _y * other._y - _z * other._z,
		_w * other._x + _x * other._w + _y * other._z - _z * other._y,
		_w * other._y - _x * other._z + _y * other._w + _z * other._x,
		_w * other._z + _x * other._y - _y * other._x + _z * other._w);
}

eden_utils::Quaternion eden_utils::Quaternion::operator*(float scalar)
{
	return Quaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

eden_utils::Quaternion eden_utils::Quaternion::operator/(float scalar)
{
	assert(scalar != 0);
	return Quaternion(_w / scalar, _x / scalar, _y / scalar, _z / scalar);
}

eden_utils::Quaternion eden_utils::Quaternion::operator+=(Quaternion other)
{
	_w += other._w;
	_x += other._x;
	_y += other._y;
	_z += other._z;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::operator-=(Quaternion other)
{
	_w -= other._w;
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::operator*=(Quaternion other)
{
	float w = _w, x = _x, y = _y, z = _z;

	_w = w * other._w - x * other._x - y * other._y - z * other._z;
	_x = w * other._x + x * other._w - y * other._z + z * other._y;
	_y = w * other._y + x * other._z + y * other._w - z * other._x;
	_z = w * other._z - x * other._y + y * other._x + z * other._w;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::operator*=(float scalar)
{
	_w *= scalar;
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::operator/=(float scalar)
{
	assert(scalar != 0);
	_w /= scalar;
	_x /= scalar;
	_y /= scalar;
	_z /= scalar;

	return *this;
}

eden_utils::Quaternion eden_utils::Quaternion::Conjugate()
{
	return Quaternion(_w, -_x, -_y, -_z);
}

float eden_utils::Quaternion::Normal()
{
	return (_w * _w) + (_x * _x) + (_y * _y) + (_z * _z);
}

eden_utils::Quaternion eden_utils::Quaternion::Normalized()
{
	Quaternion q = *this;
	float length = float(sqrt(Normal()));
	q._w /= length;
	q._x /= length;
	q._y /= length;
	q._z /= length;
	return q;
}

eden_utils::Quaternion eden_utils::Quaternion::Inverse()
{
	return Conjugate() / Normal();
}

eden_utils::Vector3 eden_utils::Quaternion::Complex() const
{
	return Vector3(_x, _y, _z);
}


eden_utils::Vector3 eden_utils::Quaternion::ToEuler() const {
	// Rotacion en Z, Y y X respectivamente
	float heading = 0, pitch = 0, bank = 0;

	// Calculo de heading
	float numerador = 2 * (_x * _y + _z * _w);
	float denominador = 1 - 2 * (_y * _y + _z * _z);
	float result = numerador / denominador;
	heading = atanf(result);

	// Calculo de pitch
	result = 2 * (_x * _z - _w * _y);
	pitch = asinf(result);

	// Calculo de bank
	numerador = 2 * (_x * _w + _y * _z);
	denominador = 1 - 2 * (_z * _z + _w * _w);
	result = numerador / denominador;
	bank = atanf(result);

	return eden_utils::Vector3(bank, pitch, heading);
}

void eden_utils::Quaternion::RotateArroundPoint(Vector3 position, float angle)
{
	*this = Quaternion(angle, position) * (*this);
}

void eden_utils::Quaternion::RotateArroundPointLocal(Vector3 position, float angle)
{
	*this = (*this) * Quaternion(angle, position);
}

eden_utils::Quaternion eden_utils::Quaternion::Identity()
{
	return Quaternion(1, eden_utils::Vector3(0, 0, 0));
}

std::array<std::array<float, 3>, 3> eden_utils::Quaternion::GetRotationMatrix() const
{
	std::array<std::array<float, 3>, 3> rotMat;

	float fTx = 2.0f * _x, fTy = 2.0f * _y, fTz = 2.0f * _z,
		fTxw = fTx * _w, fTyw = fTy * _w, fTzw = fTz * _w,
		fTxx = fTx * _x, fTyx = fTy * _x, fTzx = fTz * _x, 	fTyy = fTy * _y, fTzy = fTz * _y, fTzz = fTz * _z;

	rotMat[0][0] = float(1.0f - (fTyy + fTzz));
	rotMat[0][1] = float(fTyx - fTzw);
	rotMat[0][2] = float(fTzx + fTyw);
	rotMat[1][0] = float(fTyx + fTzw);
	rotMat[1][1] = float(1.0f - (fTxx + fTzz));
	rotMat[1][2] = float(fTzy - fTxw);
	rotMat[2][0] = float(fTzx - fTyw);
	rotMat[2][1] = float(fTzy + fTxw);
	rotMat[2][2] = float(1.0f - (fTxx + fTyy));

	return rotMat;
}
