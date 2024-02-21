#ifndef VECTOR3_H
#define VECTOR3_H
namespace eden_utils {
	class Vector3
	{
	public:
		/// @brief Constructora por defecto de Vector3
		Vector3();

		/// @brief Constructora con parámetros de Vector3
		/// @param x Coordenada en x
		/// @param y Coordenada en y
		/// @param z Coordenada en z
		Vector3(float x, float y, float z);

		~Vector3() = default;

		inline float getX() const { return _x; }
		inline float getY() const { return _y; }
		inline float getZ() const { return _z; }

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

		/// @brief Multiplicación de vector con escalar
		/// @param scalar Escalar que multiplica
		/// @return Vector resultante
		Vector3 operator*(float scalar);

		/// @brief División de un vector entre un escalar
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
		float magnitude();

		/// @brief Normaliza el vector
		void normalize();

		/// @brief Devuelve el vector normalizado, pero no lo cambia
		/// @return Vector normalizado
		Vector3 normalized();

		/// @brief Producto escalar de dos vectores
		/// @param other Vector con el que se hace el producto escalar
		/// @return Devuelve el producto escalar
		float dot(Vector3 other);

		/// @brief Producto vectorial de dos vectores
		/// @param other Vector con el que se hace el producto vectorial
		/// @return Devuelve el producto vectorial
		Vector3 cross(Vector3 other);
	private:
		float _x;
		float _y;
		float _z;
	};
}
#endif  VECTOR3_H


