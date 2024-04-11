#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_PHYSICS_MANAGER_H
#define EDEN_PHYSICS_MANAGER_H

#include <unordered_set>
#include <unordered_map>

#include "Singleton.h"
#include "Vector3.h"

#define DEFAULT_GROUP "DEFAULT"
#define RAYCAST_GROUP "RAYCAST"
#define COLLISIONMASK_NULL ""

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
	class SceneManager;
}

namespace physics_wrapper {
	class RigidBody;
	class CollisionLayer;
}

namespace eden_debug {
	class DebugDrawer;
}


namespace physics_manager {
	class InfoPhysicWorld;
	class __declspec(dllexport) LayerInfo {
	private:
		/// @brief Nombre de la capa
		std::string _name;

		/// @brief ID de la escena
		std::string _sceneID;
	public:
		/// @brief Constructora por defecto
		LayerInfo() = default;
		
		/// @brief Constructora 
		/// @param name Nombre de la capa
		/// @param sceneID ID de la escena
		LayerInfo(std::string name, std::string sceneID);
		
		/// @brief Devuelve el nombre de la capa
		/// @return Devuelve el nombre de la capa
		const inline std::string GetName() const { return _name; }

		/// @brief Devuelve el ID de la escena
		/// @return Devuelve el ID de la escena
		const inline std::string GetSceneID() const { return _sceneID; }

		/// @brief Operador para comparar en el unordered_map del PhysicsManager
		/// @param other La otra capa con la que se compara
		/// @return True si la capa tiene el mismo nombre e ID de la escena, False en cualquier otro caso
		bool operator==(const LayerInfo& other) const;
	};

	struct LayerHash
	{
		/// @brief Crea el código Hash necesario para el unordered_map
		/// @param info El elemento que se va a usar en el mapa (Key)
		/// @return Devuelve el código Hash creado con el nombre de la capa
		std::size_t operator()(const physics_manager::LayerInfo& info) const
		{
			return std::hash<std::string>()(info.GetName());
		}
	};

	class __declspec(dllexport) PhysicsManager : public Singleton<PhysicsManager>
	{
		friend Singleton<PhysicsManager>;
		friend physics_wrapper::RigidBody;
		friend eden::Scene;
		friend eden::SceneManager;

	public:
		/// @brief Devuelve la entidad asociada a un s�lido r�gido
		/// @param RBRef Referencia del rigidbody que queremos buscar
		/// @return Devuelve la referencia a la entidad asociada al rigid body pasado como par�metro, o nullptr si no existe
		//const eden_ec::Entity* getEntity(const class btRigidBody* RBRef) const;

		/// @brief Realiza una actualizaci�n de la simulaci�n f�sica
		/// @param deltaTime Tiempo entre simulaciones f�sicas, como la simulaci�n se llama con el FixedUdpate, este tiempo es fijo y constante
		void updateSimulation(float deltaTime, std::string sceneID);

		/// @brief Devuelve la gravedad del mundo
		/// @return Devuelve el valor de la gravedad mundial
		eden_utils::Vector3 GetGravity(std::string sceneID);

		/// @brief Añade una entidad al mundo físico
		/// @param e Entidad a añadir
		void AddPhysicsEntity(eden_ec::Entity* e);

		/// @brief QUita una entidad del mundo físico
		/// @param e Entidad a quitar
		void RemovePhysicsEntity(eden_ec::Entity* e);

		/// @brief Setear a cada rigidbody el transform de cada entidad
		void UpdatePositions(std::string sceneID);

		/// @brief Setear a cada transform de cada entidad el transform del rigidbody
		void ResolvePositions(std::string sceneID);

		~PhysicsManager() override;

		/// @brief Encuentra una capa dado un cierto nombre e ID de escena
		/// @param name Nombre de la capa que se quiere buscar
		/// @param sceneID ID de la escena en la que se encuentra la capa
		/// @return Devuelve una capa dado un cierto nombre e ID de escena, o nullptr en caso de fallar
		physics_wrapper::CollisionLayer* GetLayerByName(std::string name, std::string sceneID);
	protected:
		/// @brief La constructora se encarga de crear el mundo de la simulaci�n f�sica y el objeto encargado de dibujar 
		PhysicsManager();
	private:

		/// @brief Mapa desordenado que guarda los nombres de las capas y su respectivo objeto CollisionLayer
		std::unordered_map <physics_manager::LayerInfo, physics_wrapper::CollisionLayer*, physics_manager::LayerHash> _layers;

		/// @brief Referencia a los mundos de la simulacion fisica
		std::unordered_map <std::string, InfoPhysicWorld*> _physicsScenes;

		/// @brief
		btDynamicsWorld* _currentPhysicScene;
		
		/// @brief Encargado de hacer dibujos con caracter de debug
		eden_debug::DebugDrawer* _debugDrawer;

		/// @brief  Vector de Gravedad de la escena por defecto
		eden_utils::Vector3 _defaultGravity;

		/// @brief Devuelve el mundo
		/// @return Mundo de Bullet
		btDynamicsWorld* GetWorld(std::string sceneID);

		/// @brief Quita colisión a una capa con otra capa (por defecto todas las capas colisionan con todas)
		/// @param layerName Nombre de la capa a la que le se quiere quitar colisión
		/// @param collisionToAdd Nombre de la capa con la que no se quiere que colisione
		/// @param sceneID ID de la escena asociada a ambas capas
		void RemoveCollisionToLayer(std::string layerName, std::string collisionToAdd, std::string sceneID);

		/// @brief Crea una capa de colisión
		/// @param name Nombre de la capa que se quiere crear
		/// @param sceneID ID de la escena asociada a la capa
		void CreateCollisionLayer(std::string name, std::string sceneID);

		/// @brief Borra todas las capas de una escena
		/// @param sceneID ID de la escena
		void RemoveAllSceneLayers(std::string sceneID);

		/// @brief Crea una nueva escena, si existe actualiza la escena actual 
		/// 
		void CreatePhysicsScene(std::string sceneID);

		/// @brief 
		/// @param sceneID 
		void RemovePhysicsScene(std::string sceneToRemoveID, std::string newCurrentSceneID);
	};

	class __declspec(dllexport) InfoPhysicWorld
	{
		friend PhysicsManager;

	public:
		InfoPhysicWorld();
		~InfoPhysicWorld();

	private:
		/// @brief 
		btDynamicsWorld* _dynamicWorld;

		/// @brief Clase de bullet encargada de determinar el algortimo de c�lculo de colisiones entre objetos segun su forma
		btDispatcher* _worldDispatcher;

		/// @brief Clase de bullet encargada de subdividir el mundo en sectores para facilitar los c�lculos de colision
		btBroadphaseInterface* _worldBroadPhaseInterface;

		/// @brief Clase de bullet encargada de gestionar las colisiones entre objetos
		btConstraintSolver* _worldConstraintSolver;

		/// @brief Clase de bullet encargada de la configuraci�n de las colisiones.
		btCollisionConfiguration* _worldCollisionConfiguration;

		/// @brief Set desordenado que asigna a cada Entidad su rigidbody correspondiente en la simulaci�n f�sica
		//std::unordered_map<const class btRigidBody*, eden_ec::Entity*> _entitiesMap;
		std::unordered_set<eden_ec::Entity*> _entitiesSet;

		btDynamicsWorld* GetWorld();
	};
}
#endif // !PHYSICS_MANAGER_h