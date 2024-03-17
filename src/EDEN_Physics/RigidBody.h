#ifndef EDEN_RIGIDBODYWRAPPER_H
#define EDEN_RIGIDBODYWRAPPER_H

#include "Vector3.h"

class btRigidBody;
class btTransform;
class btVector3;
class btQuaternion;
class btCompoundShape;

namespace eden_utils {
	class Quaternion;
}

namespace eden_ec {
	class CTransform;
	class Entity;
}

namespace physics_wrapper {
	class RigidBody
	{

	public:
		static enum RigidBodyType { DYNAMIC, KINEMATIC, STATIC };

		/// @brief Tipo de forma que se puede crear
		static enum ShapeType { BOX, SPHERE, CAPSULE, CYLINDER };

		/// @brief Parametros de la forma que se vaya a crear
		static struct shapeParameters {
		public:
			/// @brief Tipo de forma
			ShapeType type;
			/// @brief Radio (en caso de esfera y capsula)
			float radius;
			/// @brief Longitudes de anchura, altura y profundidad (caso caja, altura en capsula y cilindro)
			eden_utils::Vector3 length;
			/// @brief Offset de posicion con respecto al centro del RigidBody
			eden_utils::Vector3 positionOffset;
		};

		/// @brief Constructora del RigidbodyWrapper
		/// @param transform Transform de la entidad
		/// @param mass Masa del RigidBody
		/// @param params Parametros de la forma gemoetrica inicial
		/// @param flag Tipo de RigidBody
		RigidBody(eden_ec::Entity* ent, float mass, const shapeParameters& params, const RigidBodyType& flag = DYNAMIC);

		/// @brief Destructora del RigidbodyWrapper
		~RigidBody();

		/// @brief Devuelve la posicion del Transform de Bullet
		/// @return Vector de posicion del Transform de Bullet
		eden_utils::Vector3 GetPosition();

		/// @brief Establece la posicion del Transform de Bullet
		/// @param position Vector de posicion a la que la quieres establecer
		void SetPosition(eden_utils::Vector3 position);

		/// @brief Devuelve la rotacion del Transform de Bullet
		/// @return Cuaternion de rotacion del Transform de Bullet
		eden_utils::Quaternion GetRotation();

		/// @brief Establece la rotacion del Transform de Bullet
		/// @param rotation Cuaternion de rotacion a la que quieres establecer
		void SetRotation(eden_utils::Quaternion rotation);

		/// @brief Devuelve la velocididad lineal del RigidBody de Bullet
		/// @return Vector de velocidad lineal
		eden_utils::Vector3 GetLinearVelocity();

		/// @brief Establece la velocidad lineal del RigidBody
		/// @param velocity Vector de velocidad a la que quieres establecer
		void SetLinealVelocity(eden_utils::Vector3 velocity);

		/// @brief A�ade velocidad lineal al RigidBody
		/// @param velocity Vector de velocidad que quieres sumar
		void AddLinearVelocity(eden_utils::Vector3 velocity);

		/// @brief Devuelve la velocidad angular del RigidBody de Bullet
		/// @return Vector de velocidad angular
		eden_utils::Vector3 GetAngularVelocity();

		/// @brief Establece la velocidad angular del RigidBody
		/// @param velocity Vector de angular a la que quieres establecer
		void SetAngularVelocity(eden_utils::Vector3 velocity);

		/// @brief Annade velocidad angular al RigidBody
		/// @param velocity Vector de velocidad que quieres sumar
		void AddAngularVelocity(eden_utils::Vector3 velocity);

		/// @brief Devuelve la masa del RigidBody
		/// @return Masa del RigidBody
		float GetMass();

		/// @brief Establece la masa del RigidBody
		/// @param mass Masa a la que quieres establecer
		void SetMass(float mass);

		/// @brief Devuelve la gravedad a la que esta sujeta el RigidBody
		/// @return Vector de gravedad
		eden_utils::Vector3 GetGravity();

		/// @brief Establece la gravedada a la que esta sujeta el RigidBody
		/// @param gravity Vector de gravedad que quieres establecer
		void SetGravity(eden_utils::Vector3 gravity);

		/// @brief Devuelve el damping al que esta sujeto el RigidBody
		/// @return Valor del damping
		float GetDamping();

		/// @brief Establece el damping al que esta sujeto el RigidBody
		/// @param damping Valor de damping que quieres establecer
		void SetDamping(float damping);

		/// @brief Establece la escala de la forma de colision
		/// @param scale Valor de la escala nueva que se quiere dar
		void SetScale(eden_utils::Vector3 scale);

		/// @brief Annade una fuerza al RigidBody
		/// @param force Vector de fuerza que quieres aplicar
		void ApplyForce(eden_utils::Vector3 force);

		/// @brief Annade torquue al RigidBody
		/// @param torque Vector de torque que quieres aplicar
		void ApplyTorque(eden_utils::Vector3 torque);

		/// @brief Quita las fuerzas que se aplican sobre el RigidBody
		void ClearForce();

		/// @brief Annade una forma al RigidBody
		/// @param params Parametros de la forma que se vaya a a�adir
		void AddShape(const shapeParameters& params);
	private:
		btRigidBody* _rigidBody;
		btCompoundShape* _collisionShape;

		/// @brief Traduce un vector del motor a vector de Bullet
		/// @param vector Vector del motor que quieres traducir
		/// @return Vector de Bullet traducido
		btVector3 EDENToBulletVector(eden_utils::Vector3 vector);

		/// @brief Traduce un vector de Bullet a vector del motor
		/// @param vector Vector de Bullet que quieres traducir
		/// @return Vector del motor traducido
		eden_utils::Vector3 BulletToEDENVector(btVector3 vector);

		/// @brief Traduce un Cuaternion del motor a cuaternion de Bullet
		/// @param quaternion Cuaternion del motor que quieres traducir
		/// @return Cuaternion de Bullet traducido
		btQuaternion EDENToBulletQuaternion(eden_utils::Quaternion quaternion);

		/// @brief Traduce un Cuaternion de Bullet a cuaternion del motor
		/// @param quaternion Cuaternion de Bullet que quieres traducir
		/// @return Cuaternion del motor traducido
		eden_utils::Quaternion BulletToEDENQuaternion(btQuaternion quaternion);
	};
}
#endif

