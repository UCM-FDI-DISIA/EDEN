#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_QUATERNION_H
#define EDEN_QUATERNION_H

#include <array>

#include "defs.h"

#define PI 3.1415926

namespace eden_utils {
	class Vector3;
	class EDEN_API Quaternion
	{
	public:
		/// @brief Constructora por defecto del cuaternion
		Quaternion();
		/// @brief Constructora con parametros del cuaternion
		/// @param w Componente real del cuaternion
		/// @param x Componente i del cuaternion
		/// @param y Componente j del cuaternion
		/// @param z Componente k del cuaternion
		Quaternion(float w, float x, float y, float z);

		/// @brief Constructor de un cuaternion a partir de la rotacion en un eje
		/// @param angle angulo en el que rota en grados
		/// @param axis Eje en el que rota
		Quaternion(float angle, Vector3 axis);

		/// @brief Devuelve un cuaternion unitario
		/// @param axis Eje en el que rota
		/// @param angle angulo que rota
		/// @return Cuaternion normalizado
		static Quaternion UnitQuaternion(Vector3 axis, float angle);

		~Quaternion() = default;

		/// @brief Iguala un cuaternion a otro
		/// @param other Cuaternion al que iguala
		/// @return Cuaternion resultante
		Quaternion operator=(Quaternion other);

		/// @brief Suma de dos cuaterniones
		/// @param other Cuaternion al que suma
		/// @return Cuaternion resultante
		Quaternion operator+(Quaternion other);

		/// @brief Resta de dos cuaterniones
		/// @param other Cuaternion al que resta
		/// @return Cuaternion resultante
		Quaternion operator-(Quaternion other);

		/// @brief Multiplicacion de dos cuaterniones
		/// @param other Cuaternion que multiplica
		/// @return Cuaternion resultante
		Quaternion operator*(Quaternion other);

		/// @brief Multiplicacion de cuaternion con escalar
		/// @param scalar Escalar que multiplica
		/// @return Cuaternion resultante
		Quaternion operator*(float scalar);

		/// @brief Division de un cuaternion entre un escalar
		/// @param scalar Escalar que divide
		/// @return Cuaternion resultante
		Quaternion operator/(float scalar);

		/// @brief Suma al propio cuaternion con otro
		/// @param other Cuaternion que suma
		/// @return El propio cuaternion ya sumado
		Quaternion operator+=(Quaternion other);

		/// @brief Resta al propio cuaternion con otro
		/// @param other cuaternion que resta
		/// @return El propio cuaternion ya restado
		Quaternion operator-=(Quaternion other);

		/// @brief Multiplica al propio cuaternion con otro
		/// @param other cuaternion que multiplica
		/// @return El propio cuaternion ya multiplicado
		Quaternion operator*=(Quaternion other);

		/// @brief Multiplica al propio cuaternion con un escalar
		/// @param scalar Escalar que multiplica
		/// @return El propio cuaternion ya multiplicado
		Quaternion operator*=(float scalar);

		/// @brief Divide al propio cuaternion con un escalar
		/// @param other Escalar que divide
		/// @return El propio cuaternion ya dividido
		Quaternion operator/=(float scalar);

		/// @brief Conjugado del cuaternion
		/// @return Devuelve el conjugado de un cuaternion
		Quaternion Conjugate();

		/// @brief Normal de un cuaternion
		/// @return Devuelve la normal de un cuaternion
		float Normal();

		/// @brief Normaliza un cuaternion
		/// @return Devuelve el cuaternion normalizdo
		Quaternion Normalized();

		/// @brief Inverso de un cuaternion
		/// @return Devuelve el inverso de un cuaternion
		Quaternion Inverse();

		/// @brief Componente real de un cuaternion
		/// @return Devuelve la parte real de un cuaternion
		float Real() const { return _w; };

		/// @brief Componentes i, j y k del cuaternion
		/// @return Devuelve las componentes complejas a modo de vector
		Vector3 Complex() const;

		/// @brief Rota el cuaternion alrededor de un punto
		/// @param position Punto alrededor del que rota
		/// @param angle angulo que rota en grados
		void RotateArroundPoint(Vector3 position, float angle);

		/// @brief Cuaternion sin rotacion
		/// @return Devuelve el cuaternion identidad
		static Quaternion Identity();

		/// @brief Calcula la matriz de rotacion de un cuaternion
		/// @return Devuelve la matriz de rotacion
		std::array<std::array<float, 3>, 3> GetRotationMatrix();
	private:
		/// @brief Componente real del cuaternion
		float _w;
		/// @brief Componente i del cuaternion
		float _x;
		/// @brief Componente j del cuaternion
		float _y;
		/// @brief Componente k del cuaternion
		float _z;
	};
}
#endif
