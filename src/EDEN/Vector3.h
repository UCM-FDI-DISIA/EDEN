#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_VECTOR3_H
#define EDEN_VECTOR3_H

namespace eden_utils {
	class Vector3
	{
	public:
		/// @brief Constructora por defecto de Vector3
		Vector3();

		/// @brief Constructora con par�metros de Vector3
		/// @param x Coordenada en x
		/// @param y Coordenada en y
		/// @param z Coordenada en z
		Vector3(float x, float y, float z);

		~Vector3() = default;

		/// @return El valor x del vector
		inline float GetX() const { return _x; }
		/// @return El valor y del vector
		inline float GetY() const { return _y; }
		/// @return El valor z del vector
		inline float GetZ() const { return _z; }

		/// @brief Iguala un vector a otro
		/// @param other Vector al que iguala
		/// @return Vector resultante
		Vector3 operator=(Vector3 other);

		/// @brief Suma de dos vectores
		/// @param other Vector al que suma
		/// @return Vector resultante
		Vector3 operator+(Vector3 other);

		/// @brief Resta de dos vectores
		/// @param other Vector al que resta
		/// @return Vector resultante
		Vector3 operator-(Vector3 other);

		/// @brief Multiplicaci�n de vector con escalar
		/// @param scalar Escalar que multiplica
		/// @return Vector resultante
		Vector3 operator*(float scalar);

		/// @brief Divisi�n de un vector entre un escalar
		/// @param scalar Escalar que divide
		/// @return Vector resultante
		Vector3 operator/(float scalar);

		/// @brief Suma al propio vector con otro
		/// @param other Vector que suma
		/// @return El propio vector ya sumado
		Vector3 operator+=(Vector3 other);

		/// @brief Resta al propio vector con otro
		/// @param other Vector que resta
		/// @return El propio vector ya restado
		Vector3 operator-=(Vector3 other);

		/// @brief Multiplica al propio vector con un escalar
		/// @param other Escalar que multiplica
		/// @return El propio vector ya multiplicado
		Vector3 operator*=(float scalar);
		
		/// @brief Divide al propio vector con un escalar
		/// @param other Escalar que divide
		/// @return El propio vector ya dividido
		Vector3 operator/=(float scalar);

		/// @brief Devuelve la longitud del vector
		/// @return 
		float Magnitude();

		/// @brief Normaliza el vector
		void Normalize();

		/// @brief Devuelve el vector normalizado, pero no lo cambia
		/// @return Vector normalizado
		Vector3 Normalized();

		/// @brief Producto escalar de dos vectores
		/// @param other Vector con el que se hace el producto escalar
		/// @return Devuelve el producto escalar
		float Dot(Vector3 other);

		/// @brief Producto vectorial de dos vectores
		/// @param other Vector con el que se hace el producto vectorial
		/// @return Devuelve el producto vectorial
		Vector3 Cross(Vector3 other);
	private:
		float _x;
		float _y;
		float _z;
	};
}
#endif  VECTOR3_H


