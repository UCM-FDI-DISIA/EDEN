#ifndef QUATERNION_H
#define QUATERNION_H

#define PI 3.1415926

namespace eden_utils {
	class Vector3;
	class Quaternion
	{
	public:
		/// @brief Constructora por defecto del cuaternión
		Quaternion();
		/// @brief Constructora con parámetros del cuaternión
		/// @param w Componente real del cuaternión
		/// @param x Componente i del cuaternión
		/// @param y Componente j del cuaternión
		/// @param z Componente k del cuaternión
		Quaternion(float w, float x, float y, float z);

		/// @brief Constructor de un cuaternión a partir de la rotación en un eje
		/// @param angle Ángulo en el que rota en grados
		/// @param axis Eje en el que rota
		Quaternion(float angle, Vector3 axis);

		/// @brief Devuelve un cuaternión unitario
		/// @param axis Eje en el que rota
		/// @param angle Ángulo que rota
		/// @return Cuaternión normalizado
		static Quaternion UnitQuaternion(Vector3 axis, float angle);

		~Quaternion() = default;

		/// @brief Iguala un cuaternión a otro
		/// @param other Cuaternión al que iguala
		/// @return Cuaternión resultante
		Quaternion operator=(Quaternion other);

		/// @brief Suma de dos cuaterniones
		/// @param other Cuaternión al que suma
		/// @return Cuaternión resultante
		Quaternion operator+(Quaternion other);

		/// @brief Resta de dos cuaterniones
		/// @param other Cuaternión al que resta
		/// @return Cuaternión resultante
		Quaternion operator-(Quaternion other);

		/// @brief Multiplicación de dos cuaterniones
		/// @param other Cuaternión que multiplica
		/// @return Cuaternión resultante
		Quaternion operator*(Quaternion other);

		/// @brief Multiplicación de cuaternión con escalar
		/// @param scalar Escalar que multiplica
		/// @return Cuaternión resultante
		Quaternion operator*(float scalar);

		/// @brief División de un cuaternión entre un escalar
		/// @param scalar Escalar que divide
		/// @return Cuaternión resultante
		Quaternion operator/(float scalar);

		/// @brief Suma al propio cuaternión con otro
		/// @param other Cuaternión que suma
		/// @return El propio cuaternión ya sumado
		Quaternion operator+=(Quaternion other);

		/// @brief Resta al propio cuaternión con otro
		/// @param other cuaternión que resta
		/// @return El propio cuaternión ya restado
		Quaternion operator-=(Quaternion other);

		/// @brief Multiplica al propio cuaternión con otro
		/// @param other cuaternión que multiplica
		/// @return El propio cuaternión ya multiplicado
		Quaternion operator*=(Quaternion other);

		/// @brief Multiplica al propio cuaternión con un escalar
		/// @param scalar Escalar que multiplica
		/// @return El propio cuaternión ya multiplicado
		Quaternion operator*=(float scalar);

		/// @brief Divide al propio cuaternión con un escalar
		/// @param other Escalar que divide
		/// @return El propio cuaternión ya dividido
		Quaternion operator/=(float scalar);

		/// @brief Conjugado del cuaternión
		/// @return Devuelve el conjugado de un cuaternión
		Quaternion conjugate();

		/// @brief Normal de un cuaternión
		/// @return Devuelve la normal de un cuaternión
		float normal();

		/// @brief Normaliza un cuaternión
		/// @return Devuelve el cuaternión normalizdo
		Quaternion normalized();

		/// @brief Inverso de un cuaternión
		/// @return Devuelve el inverso de un cuaternión
		Quaternion inverse();

		/// @brief Componente real de un cuaternión
		/// @return Devuelve la parte real de un cuaternión
		float real() const { return _w; };

		/// @brief Componentes i, j y k del cuaternión
		/// @return Devuelve las componentes complejas a modo de vector
		Vector3 complex() const;

		/// @brief Rota el cuaternión alrededor de un punto
		/// @param position Punto alrededor del que rota
		/// @param angle Ángulo que rota en grados
		void rotateArroundPoint(Vector3 position, float angle);

		static Quaternion identity();
	private:
		/// @brief Componente real del cuaternión
		float _w;
		/// @brief Componente i del cuaternión
		float _x;
		/// @brief Componente j del cuaternión
		float _y;
		/// @brief Componente k del cuaternión
		float _z;
	};
}
#endif
