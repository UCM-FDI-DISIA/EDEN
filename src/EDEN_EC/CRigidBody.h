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

#include "defs.h"

namespace physics_manager {
	class PhysicsManager;
}

namespace physics_wrapper{
	class CollisionLayer;
}

namespace eden_ec {
	class CLuaBehaviour;
	class CRigidBody : public Component
	{

		friend physics_manager::PhysicsManager;
	public:
		/// @brief Constructora por defecto. No usar
		EDEN_API CRigidBody() = default;

		/// @brief Funcion para inicializar el componente con los scripts de lua
		/// @param args Argumentos leidos del script de lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override;

		/// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
		EDEN_API void Start() override;

		/// @brief Metodo ejecutado cada frame
		/// @param t Tiempo transcurrido desde el ultimo frame
		EDEN_API void Update(float t) override;

		/// @brief Los rigidbodies por defecto desactivan su simulaci�n pasado un tiempo para evitar problemas de 
		/// optimizaci�n. Esto tambi�n sucede si nuestro personaje recibe un input y deja de recibirlo despu�s durante
		/// un peque�o periodo de tiempo. Con este m�todo podremos activar o desactivar esa opci�n.
		/// @param input True = Se desactiva la desactivaci�n | False = Se activa
		EDEN_API void SetTemporalDeactivation(bool input);

		/// @brief Destructora
		EDEN_API ~CRigidBody() override;

		/// @brief Devuelve la velocididad lineal del RigidBody de Bullet
		/// @return Vector de velocidad lineal
		EDEN_API eden_utils::Vector3 GetLinearVelocity();

		/// @brief Establece la velocidad lineal del RigidBody
		/// @param velocity Vector de velocidad a la que quieres establecer
		EDEN_API void SetLinealVelocity(eden_utils::Vector3 velocity);

		/// @brief Annade velocidad lineal al RigidBody
		/// @param velocity Vector de velocidad que quieres sumar
		EDEN_API void AddLinearVelocity(eden_utils::Vector3 velocity);

		/// @brief Devuelve la velocidad angular del RigidBody de Bullet
		/// @return Vector de velocidad angular
		EDEN_API eden_utils::Vector3 GetAngularVelocity();

		/// @brief Establece la velocidad angular del RigidBody
		/// @param velocity Vector de angular a la que quieres establecer
		EDEN_API void SetAngularVelocity(eden_utils::Vector3 velocity);

		/// @brief Annade velocidad angular al RigidBody
		/// @param velocity Vector de velocidad que quieres sumar
		EDEN_API void AddAngularVelocity(eden_utils::Vector3 velocity);

		/// @brief Devuelve la masa del RigidBody
		/// @return Masa del RigidBody
		EDEN_API float GetMass();

		/// @brief Establece la masa del RigidBody
		/// @param mass Masa a la que quieres establecer
		EDEN_API void SetMass(float mass);

		/// @brief Devuelve la gravedad a la que esta sujeta el RigidBody
		/// @return Vector de gravedad
		EDEN_API eden_utils::Vector3 GetGravity();

		/// @brief Establece la gravedada a la que esta sujeta el RigidBody
		/// @param gravity Vector de gravedad que quieres establecer
		EDEN_API void SetGravity(eden_utils::Vector3 gravity);

		/// @brief Devuelve el damping al que esta sujeto el RigidBody
		/// @return Valor del damping
		EDEN_API float GetDamping();

		/// @brief Establece el damping al que esta sujeto el RigidBody
		/// @param damping Valor de damping que quieres establecer
		EDEN_API void SetDamping(float damping);

		/// @brief Annade una fuerza al RigidBody
		/// @param force Vector de fuerza que quieres aplicar
		EDEN_API void ApplyForce(eden_utils::Vector3 force);

		/// @brief Annade torquue al RigidBody
		/// @param torque Vector de torque que quieres aplicar
		EDEN_API void ApplyTorque(eden_utils::Vector3 torque);

		/// @brief Quita las fuerzas que se aplican sobre el RigidBody
		EDEN_API void ClearForce();

		/// @brief Se llama cuando un rigidBody empieza a colisionar con el rigidBody
		/// @param Entidad que colisiona
		EDEN_API void OnCollisionEnter(eden_ec::Entity* other);

		/// @brief Se llama cada vez que haya una colision despues de que se haya llamado el OnCollisionEnter
		/// @param Entidad que colisiona
		EDEN_API void OnCollisionStay(eden_ec::Entity* other);
		
		/// @brief Se llama cuando un rogidBody acaba de terminar la colision con el RigidBody
		/// @param Entidad que colisiona
		EDEN_API void OnCollisionExit(eden_ec::Entity* other);

		/// @brief Devuelve la propiedad de rebote
		/// @return Devuelve la propiedad de rebote 
		EDEN_API float GetBounciness();

		/// @brief Devuelve la propiedad de friccion
		/// @return Devuelve la propiedad de friccion 
		EDEN_API float GetFriction();

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		EDEN_API static std::string GetID() { return "RIGIDBODY"; }

		/// @brief Devuelve la capa de colision del objeto
		/// @return Devuelve la capa de colision del objeto 
		EDEN_API physics_wrapper::CollisionLayer* GetCollisionLayer();

		/// @brief Devuelve el nombre de la capa de colision del objeto
		/// @return Devuelve el nombre de la capa de colision del objeto 
		EDEN_API std::string GetCollisionLayerName();

		EDEN_API physics_wrapper::RigidBody* GetWrapperRigidBody();

	protected:
		const static std::string _id;

	private:
		/// @brief Masa asociada al RigidBody
		float _mass = 0;

		/// @brief Efecto de rebote, indica cuanta energia se mantiene despues de la colision
		float _restitution = 0;

		/// @brief Friccion asociada al RigidBody
		float _friction = 0;

		/// @brief Booleano para indicar si se comporta como un trigger o un collider
		bool _isTrigger = false;

		/// @brief Variable que se encarga de contener los parametros de la figura asociada al rigidBody
		physics_wrapper::RigidBody::ShapeParameters _params;

		/// @brief Tipo de RigidBody (STATIC, DYNAMIC, KINEMATIC)
		physics_wrapper::RigidBody::RigidBodyType _type = physics_wrapper::RigidBody::RigidBodyType::DYNAMIC;

		/// @brief Nombre de la capa de colision asignada
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
