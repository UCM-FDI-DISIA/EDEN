#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_QUATERNION_H
#define EDEN_QUATERNION_H

#include <array>

#include "defs.h"

#define PI 3.1415926

namespace eden_utils {
	class Vector3;
	class Quaternion
	{
	public:
		/// @brief Constructora por defecto del cuaterni�n
		EDEN_API Quaternion();
		/// @brief Constructora con par�metros del cuaterni�n
		/// @param w Componente real del cuaterni�n
		/// @param x Componente i del cuaterni�n
		/// @param y Componente j del cuaterni�n
		/// @param z Componente k del cuaterni�n
		EDEN_API Quaternion(float w, float x, float y, float z);

		/// @brief Constructor de un cuaterni�n a partir de la rotaci�n en un eje
		/// @param angle �ngulo en el que rota en grados
		/// @param axis Eje en el que rota
		EDEN_API Quaternion(float angle, Vector3 axis);

		/// @brief Devuelve un cuaterni�n unitario
		/// @param axis Eje en el que rota
		/// @param angle �ngulo que rota
		/// @return Cuaterni�n normalizado
		EDEN_API static Quaternion UnitQuaternion(Vector3 axis, float angle);

		EDEN_API ~Quaternion() = default;

		/// @brief Iguala un cuaterni�n a otro
		/// @param other Cuaterni�n al que iguala
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator=(Quaternion other);

		/// @brief Suma de dos cuaterniones
		/// @param other Cuaterni�n al que suma
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator+(Quaternion other);

		/// @brief Resta de dos cuaterniones
		/// @param other Cuaterni�n al que resta
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator-(Quaternion other);

		/// @brief Multiplicaci�n de dos cuaterniones
		/// @param other Cuaterni�n que multiplica
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator*(Quaternion other);

		/// @brief Multiplicaci�n de cuaterni�n con escalar
		/// @param scalar Escalar que multiplica
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator*(float scalar);

		/// @brief Divisi�n de un cuaterni�n entre un escalar
		/// @param scalar Escalar que divide
		/// @return Cuaterni�n resultante
		EDEN_API Quaternion operator/(float scalar);

		/// @brief Suma al propio cuaterni�n con otro
		/// @param other Cuaterni�n que suma
		/// @return El propio cuaterni�n ya sumado
		EDEN_API Quaternion operator+=(Quaternion other);

		/// @brief Resta al propio cuaterni�n con otro
		/// @param other cuaterni�n que resta
		/// @return El propio cuaterni�n ya restado
		EDEN_API Quaternion operator-=(Quaternion other);

		/// @brief Multiplica al propio cuaterni�n con otro
		/// @param other cuaterni�n que multiplica
		/// @return El propio cuaterni�n ya multiplicado
		EDEN_API Quaternion operator*=(Quaternion other);

		/// @brief Multiplica al propio cuaterni�n con un escalar
		/// @param scalar Escalar que multiplica
		/// @return El propio cuaterni�n ya multiplicado
		EDEN_API Quaternion operator*=(float scalar);

		/// @brief Divide al propio cuaterni�n con un escalar
		/// @param other Escalar que divide
		/// @return El propio cuaterni�n ya dividido
		EDEN_API Quaternion operator/=(float scalar);

		/// @brief Conjugado del cuaterni�n
		/// @return Devuelve el conjugado de un cuaterni�n
		EDEN_API Quaternion Conjugate();

		/// @brief Normal de un cuaterni�n
		/// @return Devuelve la normal de un cuaterni�n
		EDEN_API float Normal();

		/// @brief Normaliza un cuaterni�n
		/// @return Devuelve el cuaterni�n normalizdo
		EDEN_API Quaternion Normalized();

		/// @brief Inverso de un cuaterni�n
		/// @return Devuelve el inverso de un cuaterni�n
		EDEN_API Quaternion Inverse();

		/// @brief Componente real de un cuaterni�n
		/// @return Devuelve la parte real de un cuaterni�n
		EDEN_API float Real() const { return _w; };

		/// @brief Componentes i, j y k del cuaterni�n
		/// @return Devuelve las componentes complejas a modo de vector
		EDEN_API Vector3 Complex() const;

		/// @brief Rota el cuaterni�n alrededor de un punto
		/// @param position Punto alrededor del que rota
		/// @param angle �ngulo que rota en grados
		EDEN_API void RotateArroundPoint(Vector3 position, float angle);

		/// @brief Cuaterni�n sin rotaci�n
		/// @return Devuelve el cuaterni�n identidad
		EDEN_API static Quaternion Identity();

		/// @brief Calcula la matriz de rotaci�n de un cuaterni�n
		/// @return Devuelve la matriz de rotaci�n
		EDEN_API std::array<std::array<float, 3>, 3> GetRotationMatrix();
	private:
		/// @brief Componente real del cuaterni�n
		float _w;
		/// @brief Componente i del cuaterni�n
		float _x;
		/// @brief Componente j del cuaterni�n
		float _y;
		/// @brief Componente k del cuaterni�n
		float _z;
	};
}
#endif
