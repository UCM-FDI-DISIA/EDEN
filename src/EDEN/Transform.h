#ifndef TRANSFORM_H
#define TRANSFORM_H

class Component {};

#include <string>

#include "Vector3.h"
#include "Quaternion.h"


namespace eden_ec {
	/// @brief Componente que tiene toda entidad que gestiona su posición, rotación y escala
	class Transform : public Component
	{
	protected:
		const static std::string _id;
	public:
		enum AXIS_REFERENCE {AXIS_WORLD, AXIS_LOCAL};
		/// @brief Constructora por defecto del Transform
		Transform() = default;

		/// @brief Constructora con parámetros
		/// @param position Posición de la entidad en la que se va a generar
		/// @param rotation Rotación de la entidad con la que se va a generar
		/// @param scale Escala de la entidad con la que se va a generar
		Transform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale);

		~Transform() = default;

		/// @brief Getter de la posición
		/// @return Devuelve el vector de posición
		inline eden_utils::Vector3 GetPosition() const { return _position; }

		/// @brief Getter de la rotación
		/// @return Devuelve el cuaternión de la rotación
		inline eden_utils::Quaternion GetRotation() const { return _rotation; }

		/// @brief Getter de la escala
		/// @return Devuelve el vector de la escala
		inline eden_utils::Vector3 getScale() const { return _scale; }

		/// @brief Setter de la posición
		/// @param position Nueva posición del transform
		inline void SetPosition(eden_utils::Vector3 position) { _position = position; }

		/// @brief Setter de la rotación
		/// @param rotation Nueva rotación del transform
		inline void SetRotation(eden_utils::Quaternion rotation) { _rotation = rotation; }

		/// @brief Setter de la escala
		/// @param scale Nueva escala del transform
		inline void SetScale(eden_utils::Vector3 scale) { _scale = scale; }

		/// @brief Suma la posición
		/// @param position Vector que se va a sumar
		void Translate(eden_utils::Vector3 position);

		/// @brief Rota el transform 
		/// @param angle Ángulo en grados 
		/// @param axis Eje sobre el que va a rotar
		void Rotate(float angle, eden_utils::Vector3 axis);

		/// @brief Rota el transform en el eje X
		/// @param angle Ángulo en grados
		/// @param axis_system Sistema de referencia en el que va a rotar
		void Pitch(float angle, AXIS_REFERENCE axis_system = AXIS_LOCAL);

		/// @brief Rota el transform en el eje Y
		/// @param angle Ángulo en grados
		/// @param axis_system Sistema de referencia en el que va a rotar
		void Yaw(float angle, AXIS_REFERENCE axis_system = AXIS_LOCAL);

		/// @brief Rota el transform en el eje Z
		/// @param angle Ángulo en grados
		/// @param axis_system Sistema de referencia en el que va a rotar
		void Roll(float angle, AXIS_REFERENCE axis_system = AXIS_LOCAL);

		/// @brief Suma la escala del transform
		/// @param scale Vector que suma a la escala
		void Escalate(eden_utils::Vector3 scale);

		/// @brief Calcula el eje z positivo local
		/// @return Devuelve el vector forward
		eden_utils::Vector3 GetForward();

		/// @brief Calcula el eje y positivo local
		/// @return Devuelve el vector up
		eden_utils::Vector3 GetUp();

		/// @brief Calcula el eje x positivo local
		/// @return Devuelve el vector right
		eden_utils::Vector3 GetRight();
	private:
		eden_utils::Vector3 _position;
		eden_utils::Quaternion _rotation;
		eden_utils::Vector3 _scale;
	};
}
#endif

