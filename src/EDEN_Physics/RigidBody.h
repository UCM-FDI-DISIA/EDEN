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


	class RigidBody : public Singleton<RigidBody>
	{
		friend Singleton<RigidBody>;

	public:
		enum ShapeType{BOX, PLANE, CAPSULE, CONE, CYLINDER, SPHERE, TRIANGLE };

		struct RigidBodyConstruction {
			float mass;
			ShapeType shape;
			float linearDamping;
			float angularDamping;
		};


		/// @brief Destructora
		~RigidBody() override;

		/// @brief Se encarga de dar un valor propio a la gravedad
		/// @param g Nuevo valor de la gravedad
		inline void SetGravity(const eden_utils::Vector3 g) { _gravity = g; }

		/// @brief Devuelve el valor actual de la gravedad de la instancia del rigidbody, no del mundo
		inline eden_utils::Vector3 GetGravity() { return _gravity; }

	protected:

		RigidBody(const RigidBodyConstruction& rb);

		/// @brief Constructora por defecto. No usar.
		RigidBody() = default;


	private:

		/// @brief Referencia al manager de físicas
		physics_manager::PhysicsManager* _physicsManagerInstance = nullptr;

		/// @brief Variable de gravedad
		eden_utils::Vector3 _gravity;

	};

}

#endif //RIGIDBODY_H