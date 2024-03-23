#ifndef EDEN_C_RIGIDBODY_H
#define EDEN_C_RIGIDBODY_H

#include <string>

#include "Component.h"
#include "Transform.h"

//Debe incluirse en el .h para que no se generen errores de tipo del struct shapeParameters
#ifdef _MSC_VER
#include "RigidBody.h"
#endif
#ifdef __clang__
#include "./../EDEN_Physics/RigidBody.h"
#endif

namespace physics_manager {
	class PhysicsManager;
}

namespace eden_ec {
	class CRigidBody : public Component
	{
		friend physics_manager::PhysicsManager;
	public:
		/// @brief Constructora por defecto. No usar
		CRigidBody() = default;

		/// @brief Funcion para inicializar el componente con los scripts de lua
		/// @param args Argumentos leidos del script de lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
		void Start() override;

		/// @brief Metodo ejecutado cada frame
		/// @param t Tiempo transcurrido desde el ultimo frame
		virtual void Update(float t);

		/// @brief Se encarga de la entrada de input
		virtual void HandleInput();

		/// @brief Destructora
		virtual ~CRigidBody();

		/// @brief Devuelve la velocididad lineal del RigidBody de Bullet
		/// @return Vector de velocidad lineal
		eden_utils::Vector3 GetLinearVelocity();

		/// @brief Establece la velocidad lineal del RigidBody
		/// @param velocity Vector de velocidad a la que quieres establecer
		void SetLinealVelocity(eden_utils::Vector3 velocity);

		/// @brief Annade velocidad lineal al RigidBody
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

		/// @brief Annade una fuerza al RigidBody
		/// @param force Vector de fuerza que quieres aplicar
		void ApplyForce(eden_utils::Vector3 force);

		/// @brief Annade torquue al RigidBody
		/// @param torque Vector de torque que quieres aplicar
		void ApplyTorque(eden_utils::Vector3 torque);

		/// @brief Quita las fuerzas que se aplican sobre el RigidBody
		void ClearForce();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return _id; }

	protected:
		const static std::string _id;

	private:
		/// @brief Masa asociada al rigidBody
		float _mass;

		/// @brief Variable que se encarga de contener los parametros de la figura asociada al rigidBody
		physics_wrapper::RigidBody::ShapeParameters _params;

		physics_wrapper::RigidBody::RigidBodyType _type;

		std::string _layer = "DEFAULT";

		/// @brief Referencia al wrapper de rigid body del modulo de fisicas
		physics_wrapper::RigidBody* _rb = nullptr;

		/// @brief Referencia al componente transform
		eden_ec::CTransform* _transform = nullptr;

		/// @brief Convierte el componente transform propio al transform del motor de fisicas
		void EdenTransformToPhysicsTransform();

		/// @brief Convierte el transform del motor de fisicas al componente transform propio
		void PhysicsTransformToEdenTransform();
	};

}

#endif
