#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_VECTOR3_H
#define EDEN_VECTOR3_H

#include<array>
#include "defs.h"

namespace eden_utils {
	class Vector3
	{
	public:
		/// @brief Constructora por defecto de Vector3
		EDEN_API Vector3();

		/// @brief Constructora con parametros de Vector3
		/// @param x Coordenada en x
		/// @param y Coordenada en y
		/// @param z Coordenada en z
		EDEN_API Vector3(float x, float y, float z);

		EDEN_API ~Vector3() = default;

		/// @return El valor x del vector
		EDEN_API inline float GetX() const { return _x; }
		/// @return El valor y del vector
		EDEN_API inline float GetY() const { return _y; }
		/// @return El valor z del vector
		EDEN_API inline float GetZ() const { return _z; }

		/// @brief Iguala un vector a otro
		/// @param other Vector al que iguala
		/// @return Vector resultante
		EDEN_API Vector3 operator=(Vector3 other);

		/// @brief Suma de dos vectores
		/// @param other Vector al que suma
		/// @return Vector resultante
		EDEN_API Vector3 operator+(Vector3 other);

		/// @brief Resta de dos vectores
		/// @param other Vector al que resta
		/// @return Vector resultante
		EDEN_API Vector3 operator-(Vector3 other);

		/// @brief Multiplicacion de vector con escalar
		/// @param scalar Escalar que multiplica
		/// @return Vector resultante
		EDEN_API Vector3 operator*(float scalar);

		/// @brief Division de un vector entre un escalar
		/// @param scalar Escalar que divide
		/// @return Vector resultante
		EDEN_API Vector3 operator/(float scalar);

		/// @brief Suma al propio vector con otro
		/// @param other Vector que suma
		/// @return El propio vector ya sumado
		EDEN_API Vector3 operator+=(Vector3 other);

		/// @brief Resta al propio vector con otro
		/// @param other Vector que resta
		/// @return El propio vector ya restado
		EDEN_API Vector3 operator-=(Vector3 other);

		/// @brief Multiplica al propio vector con un escalar
		/// @param other Escalar que multiplica
		/// @return El propio vector ya multiplicado
		EDEN_API Vector3 operator*=(float scalar);
		
		/// @brief Divide al propio vector con un escalar
		/// @param other Escalar que divide
		/// @return El propio vector ya dividido
		EDEN_API Vector3 operator/=(float scalar);

		/// @brief Devuelve la longitud del vector
		/// @return 
		EDEN_API float Magnitude();

		/// @brief Normaliza el vector
		EDEN_API void Normalize();

		/// @brief Devuelve el vector normalizado, pero no lo cambia
		/// @return Vector normalizado
		EDEN_API Vector3 Normalized();

		/// @brief Producto escalar de dos vectores
		/// @param other Vector con el que se hace el producto escalar
		/// @return Devuelve el producto escalar
		EDEN_API float Dot(Vector3 other);

		/// @brief Producto vectorial de dos vectores
		/// @param other Vector con el que se hace el producto vectorial
		/// @return Devuelve el producto vectorial
		EDEN_API Vector3 Cross(Vector3 other);

		/// @brief Rotacion de un vector con respecto a un eje
		/// @param axis Eje alrededor al que rota
		/// @param angle Angulo que rota
		/// @return Vector rotado
		EDEN_API Vector3 RotatedAroundPoint(Vector3 axis, float angle);

		/// @brief Calcula la matriz de rotacion para vectores
		/// @param axis Eje al que rota
		/// @param angle Angulo que rota
		/// @return Matriz de rotacion
		EDEN_API std::array<std::array<float, 3>, 3> GetRotationMatrix(Vector3 axis, float angle);
	private:
		float _x;
		float _y;
		float _z;
	};
}
#endif //VECTOR3_H


