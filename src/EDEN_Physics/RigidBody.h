#ifndef EDEN_RIGIDBODYWRAPPER_H
#define EDEN_RIGIDBODYWRAPPER_H
#include <string>

#include "Vector3.h"

class btRigidBody;
class btTransform;
class btVector3;
class btQuaternion;
class btCompoundShape;
struct btDefaultMotionState;

namespace eden_utils {
	class Quaternion;
}

namespace eden_ec {
	class CTransform;
	class Entity;
}

namespace physics_manager {
	class PhysicsManager;
}

#ifdef _DEBUG
namespace eden_debug {
	class Debug;
}
#endif

namespace physics_wrapper {
	class CollisionCallback;

	class RigidBody
	{
		friend CollisionCallback;
		friend physics_manager::PhysicsManager;
#ifdef _DEBUG
		friend eden_debug::Debug;
#endif

	public:
		enum RigidBodyType { DYNAMIC, KINEMATIC, STATIC };

		/// @brief Tipo de forma que se puede crear
		enum ShapeType { BOX, SPHERE, CAPSULE, CYLINDER };

		/// @brief Parametros de la forma que se vaya a crear
		struct ShapeParameters {
		public:
			/// @brief Tipo de forma
			ShapeType type = BOX;
			/// @brief Radio (en caso de esfera y capsula)
			float radius = 0;
			/// @brief Longitudes de anchura, altura y profundidad (caso caja, altura en capsula y cilindro)
			eden_utils::Vector3 length = eden_utils::Vector3(0,0,0);
			/// @brief Offset de posicion con respecto al centro del RigidBody
			eden_utils::Vector3 positionOffset = eden_utils::Vector3(0, 0, 0);
		};

		/// @brief Constructora del RigidbodyWrapper
		/// @param ent Entidad a la que va a corresponder el Rigidbody
		/// @param params Parametros de la forma gemoetrica inicial
		/// @param mass Masa del RigidBody
		/// @param friction Friccion del RigidBody
		/// @param bounciness Rebote del RigidBody
		/// @param flag Tipo de RigidBody (STATIC, DYNAMIC, KINEMATIC)
		/// @param layerName Nombre de la capa de colisión que se va a usar
		/// @param isTrigger Booleano para indicar si se comporta como un trigger o un collider
		RigidBody(eden_ec::Entity* ent, const ShapeParameters& params, float mass = 1.0f, float friction = 1.0f, float bounciness = 1.0f, const RigidBodyType& flag = STATIC, std::string* layerName = nullptr, bool isTrigger = false);

		/// @brief Destructora del RigidbodyWrapper
		~RigidBody();

		/// @brief Devuelve la posicion del Transform de Bullet
		/// @return Vector de posicion del Transform de Bullet
		eden_utils::Vector3 GetPosition();

		/// @brief Establece la posicion del Transform de Bullet
		/// @param position Vector de posicion a la que la quieres establecer
		void SetPosition(eden_utils::Vector3 position);

		/// @brief Bullet tiene una desactivación temporal de objetos si no se le aplican fuerzas durante un tiempo. 
		/// Con este método podremos Activar o Desactivar esa opción
		/// @param activation True = Desactivado | False = Activado
		void SetTemporalDeactivation(bool activation);

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

		/// @brief Aniade velocidad lineal al RigidBody
		/// @param velocity Vector de velocidad que quieres sumar
		void AddLinearVelocity(eden_utils::Vector3 velocity);

		/// @brief Devuelve la velocidad angular del RigidBody de Bullet
		/// @return Vector de velocidad angular
		eden_utils::Vector3 GetAngularVelocity();

		/// @brief Establece la velocidad angular del RigidBody
		/// @param velocity Vector de angular a la que quieres establecer
		void SetAngularVelocity(eden_utils::Vector3 velocity);

		/// @brief Aniade velocidad angular al RigidBody
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

		/// @brief Establece la gravedad a la que esta sujeta el RigidBody
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

		/// @brief Aniade torquue al RigidBody
		/// @param torque Vector de torque que quieres aplicar
		void ApplyTorque(eden_utils::Vector3 torque);

		/// @brief Quita las fuerzas que se aplican sobre el RigidBody
		void ClearForce();

		/// @brief Annade una forma al RigidBody
		/// @param params Parametros de la forma que se vaya a aniadir
		void AddShape(const ShapeParameters& params);

		/// @brief Establece un valor de friccion al RigidBody
		/// @param friction Valor nuevo de friccion para el RigidBody
		void SetFriction(float friction);
		
		/// @brief Devuelve la propiedad de friccion
		/// @return Devuelve la propiedad de friccion
		float GetFriction();

		/// @brief Establece un valor de rebote al RigidBody
		/// @param friction Valor nuevo de rebote para el RigidBody
		void SetBounciness(float bounciness);

		/// @brief Devuelve la propiedad de rebote
		/// @return Devuelve la propiedad de rebote 
		float GetBounciness();

		/// @brief Metodo que actualiza el estado de las colisiones para ver si se ha dejado de colisionar con algun objeto.
		void Update();

		/// @brief Devuelve el rigidBody de la libreria fisica asociado a este rigidBody
		btRigidBody* getBulletRigidBody();

	private:
		btRigidBody* _rigidBody = nullptr;
		btDefaultMotionState* _motionState = nullptr;
		btCompoundShape* _collisionShape = nullptr;
		CollisionCallback* _collisionCallback = nullptr;
		eden_ec::Entity* _entRef = nullptr;

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

	protected:

	};
}
#endif

