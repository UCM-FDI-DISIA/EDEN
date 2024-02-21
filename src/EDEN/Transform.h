#ifndef TRANSFORM_H
#define TRANSFORM_H

class Component {};
class Vector3;

namespace eden_ec {
	/// @brief Componente que tiene toda entidad que gestiona su posici�n, rotaci�n y escala
	class Transform : public Component
	{
	public:
		/// @brief Constructora por defecto del Transform
		Transform();

		/// @brief Constructora con par�metros
		/// @param position Posici�n de la entidad en la que se va a generar
		/// @param rotation Rotaci�n de la entidad con la que se va a generar
		/// @param scale Escala de la entidad con la que se va a generar
		Transform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale);

		~Transform() = default;

		/// @brief Getter de la posici�n
		/// @return Devuelve el vector de posici�n
		inline eden_utils::Vector3 getPosition() const { return _position; }

		/// @brief Getter de la rotaci�n
		/// @return Devuelve el cuaterni�n de la rotaci�n
		inline eden_utils::Quaternion getRotation() const { return _rotation; }

		/// @brief Getter de la escala
		/// @return Devuelve el vector de la escala
		inline eden_utils::Vector3 getScale() const { return _scale; }

		/// @brief Setter de la posici�n
		/// @param position Nueva posici�n del transform
		inline void setPosition(eden_utils::Vector3 position) { _position = position; }

		/// @brief Setter de la rotaci�n
		/// @param rotation Nueva rotaci�n del transform
		inline void setRotation(eden_utils::Quaternion rotation) { _rotation = rotation; }

		/// @brief Setter de la escala
		/// @param scale Nueva escala del transform
		inline void setScale(eden_utils::Vector3 scale) { _scale = scale; }

		/// @brief Suma la posici�n
		/// @param position Vector que se va a sumar
		void translate(eden_utils::Vector3 position);

		/// @brief Rota el transform 
		/// @param angle �ngulo en grados 
		/// @param axis Eje sobre el que va a rotar
		void rotate(float angle, eden_utils::Vector3 axis);

		/// @brief Rota el transform en el eje X
		/// @param angle �ngulo en grados
		void pitch(float angle);

		/// @brief Rota el transform en el eje Y
		/// @param angle �ngulo en grados
		void yaw(float angle);

		/// @brief Rota el transform en el eje Z
		/// @param angle �ngulo en grados
		void roll(float angle);

		/// @brief Suma la escala del transform
		/// @param scale Vector que suma a la escala
		void escalate(eden_utils::Vector3 scale);
	private:
		eden_utils::Vector3 _position;
		eden_utils::Quaternion _rotation;
		eden_utils::Vector3 _scale;
	};
}
#endif

