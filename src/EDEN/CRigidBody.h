#define _CRTDBG_MAP_ALLOC
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
	class CLuaBehaviour;
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

		/// @brief Se llama cuando un rigidBody empieza a colisionar con el rigidBody
		/// @param Entidad que colisiona
		void OnCollisionEnter(eden_ec::Entity* other);

		/// @brief Se llama cada vez que haya una colision despu�s de que se haya llamado el OnCollisionEnter
		/// @param Entidad que colisiona
		void OnCollisionStay(eden_ec::Entity* other);
		
		/// @brief Se llama cuando un rogidBody acaba de terminar la colision con el RigidBody
		/// @param Entidad que colisiona
		void OnCollisionExit(eden_ec::Entity* other);

		/// @brief Devuelve la propiedad de rebote
		/// @return Devuelve la propiedad de rebote 
		float GetBounciness();

		/// @brief Devuelve la propiedad de fricci�n
		/// @return Devuelve la propiedad de fricci�n 
		float GetFriction();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return _id; }

	protected:
		const static std::string _id;

	private:
		/// @brief Masa asociada al RigidBody
		float _mass = 0;

		/// @brief Efecto de rebote, indica cuanta energ�a se mantiene despu�s de la colisi�n
		float _restitution = 0;

		/// @brief Fricci�n asociada al RigidBody
		float _friction = 0;

		/// @brief Variable que se encarga de contener los parametros de la figura asociada al rigidBody
		physics_wrapper::RigidBody::ShapeParameters _params;

		physics_wrapper::RigidBody::RigidBodyType _type = physics_wrapper::RigidBody::RigidBodyType::DYNAMIC;

		std::string _layer = "DEFAULT";

		/// @brief Referencia al wrapper de rigid body del modulo de fisicas
		physics_wrapper::RigidBody* _rb = nullptr;

		/// @brief Referencia al componente transform
		eden_ec::CTransform* _transform = nullptr;

		eden_ec::CLuaBehaviour* _behaviour = nullptr;

		/// @brief Convierte el componente transform propio al transform del motor de fisicas
		void EdenTransformToPhysicsTransform();

		/// @brief Convierte el transform del motor de fisicas al componente transform propio
		void PhysicsTransformToEdenTransform();
	};

}

#endif
