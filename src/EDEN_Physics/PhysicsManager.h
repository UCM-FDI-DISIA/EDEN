#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include <unordered_map>
#include "../EDEN/Singleton.h"

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

namespace physics_manager {
	class PhysicsManager : public Singleton<PhysicsManager>
	{
		friend Singleton<PhysicsManager>;

	public:
		/// @brief Devuelve la entidad asociada a un sólido rígido
		/// @param RBRef Referencia del rigidbody que queremos buscar
		/// @return Devuelve la referencia a la entidad asociada al rigid body pasado como parámetro, o nullptr si no existe
		const eden_ec::Entity* getEntity(const class btRigidBody* RBRef) const;

		/// @brief Realiza una actualización de la simulación física
		/// @param deltaTime Tiempo entre simulaciones físicas, como la simulación se llama con el FixedUdpate, este tiempo es fijo y constante
		void updateSimulation(float deltaTime);

		/// @brief Devuelve la gravedad del mundo
		/// @return Devuelve el valor de la gravedad mundial
		//inline btVector3 GetGravity() { return _dynamicWorldRef->getGravity(); }

		~PhysicsManager() override;
	protected:
		/// @brief La constructora se encarga de crear el mundo de la simulación física y el objeto encargado de dibujar 
		PhysicsManager();
	private:
		/// @brief Mapa desordenado que asigna a cada Entidad su rigidbody correspondiente en la simulación física
		std::unordered_map<const class btRigidBody*, eden_ec::Entity*> _entitiesMap;

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
	};
}
#endif // !PHYSICS_MANAGER_h