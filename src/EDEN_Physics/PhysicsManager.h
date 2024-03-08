#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include "Singleton.h"
#include <unordered_set>

class btDynamicsWorld;
class btIDebugDraw;
class btDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;
class btCollisionConfiguration;
class btRigidBody;

namespace eden_ec {
	class Entity;
}

namespace eden_utils {
	class Vector3;
}

namespace physics_wrapper {
	class RigidBody;
}

namespace physics_manager {
	class PhysicsManager : public Singleton<PhysicsManager>
	{
		friend Singleton<PhysicsManager>;
		friend physics_wrapper::RigidBody;
	public:
		/// @brief Devuelve la entidad asociada a un sólido rígido
		/// @param RBRef Referencia del rigidbody que queremos buscar
		/// @return Devuelve la referencia a la entidad asociada al rigid body pasado como parámetro, o nullptr si no existe
		//const eden_ec::Entity* getEntity(const class btRigidBody* RBRef) const;

		/// @brief Realiza una actualización de la simulación física
		/// @param deltaTime Tiempo entre simulaciones físicas, como la simulación se llama con el FixedUdpate, este tiempo es fijo y constante
		void updateSimulation(float deltaTime);

		/// @brief Devuelve la gravedad del mundo
		/// @return Devuelve el valor de la gravedad mundial
		eden_utils::Vector3 GetGravity();

		/// @brief 
		/// @param e 
		void AddPhysicsEntity(eden_ec::Entity* e);

		/// @brief 
		/// @param e 
		void RemovePhysicsEntity(eden_ec::Entity* e);

		/// @brief Setear a cada rigidbody el transform de cada entidad
		void UpdatePositions();

		/// @brief Setear a cada transform de cada entidad el transform del rigidbody
		void ResolvePositions();

		~PhysicsManager() override;
	protected:
		/// @brief La constructora se encarga de crear el mundo de la simulación física y el objeto encargado de dibujar 
		PhysicsManager();
	private:
		/// @brief Mapa desordenado que asigna a cada Entidad su rigidbody correspondiente en la simulación física
		//std::unordered_map<const class btRigidBody*, eden_ec::Entity*> _entitiesMap;
		std::unordered_set<eden_ec::Entity*> _entitiesSet;

		/// @brief Referencia al mundo de la simulación física
		btDynamicsWorld* _dynamicWorldRef;

		/// @brief Encargado de hacer dibujos con caracter de debug
		btIDebugDraw* _physicsDebugDrawer;

		/// @brief Clase de bullet encargada de determinar el algortimo de cálculo de colisiones entre objetos según su forma
		btDispatcher* _worldDispatcher;

		/// @brief Clase de bullet encargada de subdividir el mundo en sectores para facilitar los cálculos de colisión
		btBroadphaseInterface* _worldBroadPhaseInterface;

		/// @brief Clase de bullet encargada de gestionar las colisiones entre objetos
		btConstraintSolver* _worldConstraintSolver;

		/// @brief Clase de bullet encargada de la configuración de las colisiones.
		btCollisionConfiguration* _worldCollisionConfiguration;

		/// @brief Devuelve el mundo
		/// @return Mundo de Bullet
		btDynamicsWorld* GetWorld();
	};
}
#endif // !PHYSICS_MANAGER_h