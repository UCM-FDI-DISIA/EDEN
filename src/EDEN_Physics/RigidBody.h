#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../EDEN/Singleton.h"
#include "../EDEN/Vector3.h"
#include "../EDEN/Transform.h"

class btRigidBody;
class btTransform;
class btVector3;

namespace physics_manager {
	class PhysicsManager;
}

namespace physics_wrapper {


	class RigidBody
	{
	public:
		enum ShapeType{BOX, PLANE, CAPSULE, CONE, CYLINDER, SPHERE, TRIANGLE };

		struct RigidBodyConstruction {
			eden_utils::Vector3 position;
			// rotation;
			// linearVel;
			// angularVel;
			float mass;
			ShapeType shape;
			float linearDamping;
			float angularDamping;
		};


		/// @brief Destructora
		~RigidBody();

		/// @brief Se encarga de dar un valor propio a la gravedad
		/// @param g Nuevo valor de la gravedad
		inline void SetGravity(const eden_utils::Vector3 g) { _gravity = g; }

		/// @brief Devuelve el valor actual de la gravedad de la instancia del rigidbody, no del mundo
		inline eden_utils::Vector3 GetGravity() { return _gravity; }

		/// @brief
		/// @param rb
		RigidBody(const RigidBodyConstruction& rb);

		/// @brief Aplica las fuerzas recibidas al rigidbody
		/// @param force Variable de fuerza a añadir al vector de fuerzas actuales actuando sobre el rigidbody
		void applyForce(eden_utils::Vector3 force);

		/// @brief Borra todas las fuerzas que estén actuando sobre el rigidbody
		void ClearForces();


		///METODOS DE CONFIGURACION DE VARIABLES

		/// @brief Devuelve la posicion del rigidbody
		eden_utils::Vector3 GetPosition();

		/// @brief Devuelve la rotacion del rigidbody
		eden_utils::Quaternion GetRotation();

		/// @brief Devuelve la velocidad lineal del rigidbody
		eden_utils::Vector3 GetLinearVel();

		/// @brief Devuelve la velocidad angular del rigidbody
		eden_utils::Vector3 GetAngularVel();

		/// @brief Devuelve la masa del rigidbody
		float GetMass();

		/// @brief Devuelve el damping del rigidbody
		float GetDamping();


		///MÉTODOS DE DEVOLUCIÓN DE VARIABLES
		
		/// @brief Se encarga de dar un valor a la posicion
		void SetPosition(eden_utils::Vector3 pos);

		/// @brief Se encarga de dar un valor a la rotacion
		void SetRotation(eden_utils::Quaternion rot);

		/// @brief Se encarga de dar un valor a la velocidad lineal
		void SetLnearVel(eden_utils::Vector3 lVel);

		/// @brief Se encarga de dar un valor a la velocidad angular
		void SetAngularVel(eden_utils::Vector3 aVel);

		/// @brief Se encarga de dar un valor a la masa
		void SetMass(float m);

		/// @brief Se encarga de dar un valor al damping
		void SetDumping(float d);

	protected:

		/// @brief Constructora por defecto. No usar.
		RigidBody() = default;


	private:

		/// @brief Referencia al manager de físicas
		physics_manager::PhysicsManager* _physicsManagerInstance = nullptr;

		/// @brief Variable de gravedad
		eden_utils::Vector3 _gravity;

		/// @brief Referencia al transform de Bullet
		btTransform* _transform = nullptr;

		/// @brief Referencia al rigid body de Bullet
		btRigidBody* _rb = nullptr;
	};

}

#endif //RIGIDBODY_H