#ifndef EDEN_PHYSICS_MANAGER_H
#define EDEN_PHYSICS_MANAGER_H

#include <unordered_set>
#include <unordered_map>

#include "Singleton.h"

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

namespace eden {
	class Scene;
}

namespace eden_utils {
	class Vector3;
}

namespace physics_wrapper {
	class RigidBody;
	class CollisionLayer;
}

namespace eden_physics {
	class DebugDrawer;
}

namespace physics_manager {
	class PhysicsManager : public Singleton<PhysicsManager>
	{
		friend Singleton<PhysicsManager>;
		friend physics_wrapper::RigidBody;
		friend eden::Scene;
	public:
		/// @brief Devuelve la entidad asociada a un s�lido r�gido
		/// @param RBRef Referencia del rigidbody que queremos buscar
		/// @return Devuelve la referencia a la entidad asociada al rigid body pasado como par�metro, o nullptr si no existe
		//const eden_ec::Entity* getEntity(const class btRigidBody* RBRef) const;

		/// @brief Realiza una actualizaci�n de la simulaci�n f�sica
		/// @param deltaTime Tiempo entre simulaciones f�sicas, como la simulaci�n se llama con el FixedUdpate, este tiempo es fijo y constante
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

		void AddCollisionToLayer(std::string layerName, std::string collisionToAdd);

		physics_wrapper::CollisionLayer* GetLayerByName(std::string name);
	protected:
		/// @brief La constructora se encarga de crear el mundo de la simulaci�n f�sica y el objeto encargado de dibujar 
		PhysicsManager();
	private:
		/// @brief Mapa desordenado que asigna a cada Entidad su rigidbody correspondiente en la simulaci�n f�sica
		//std::unordered_map<const class btRigidBody*, eden_ec::Entity*> _entitiesMap;
		std::unordered_set<eden_ec::Entity*> _entitiesSet;

		std::unordered_map<std::string, physics_wrapper::CollisionLayer*> _layers;

		/// @brief Referencia al mundo de la simulacion fisica
		btDynamicsWorld* _dynamicWorldRef;

		/// @brief Encargado de hacer dibujos con caracter de debug
		eden_physics::DebugDrawer* _debugDrawer;

		/// @brief Clase de bullet encargada de determinar el algortimo de c�lculo de colisiones entre objetos segun su forma
		btDispatcher* _worldDispatcher;

		/// @brief Clase de bullet encargada de subdividir el mundo en sectores para facilitar los c�lculos de colision
		btBroadphaseInterface* _worldBroadPhaseInterface;

		/// @brief Clase de bullet encargada de gestionar las colisiones entre objetos
		btConstraintSolver* _worldConstraintSolver;

		/// @brief Clase de bullet encargada de la configuraci�n de las colisiones.
		btCollisionConfiguration* _worldCollisionConfiguration;

		/// @brief Devuelve el mundo
		/// @return Mundo de Bullet
		btDynamicsWorld* GetWorld();


		void CreateCollisionLayer(std::string name);
	};
}
#endif // !PHYSICS_MANAGER_h