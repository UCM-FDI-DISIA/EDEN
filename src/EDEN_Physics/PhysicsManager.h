#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_PHYSICS_MANAGER_H
#define EDEN_PHYSICS_MANAGER_H

#include <unordered_set>
#include <unordered_map>

#include "Singleton.h"
#include "Vector3.h"

#define DEFAULT_GROUP "DEFAULT"
#define RAYCAST_GROUP "RAYCAST"
#define SCENEID_NULL ""
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
	class RayCast;
	class CollisionLayer;
}

#ifdef _DEBUG
namespace eden_debug {
	class Debug;
}
#endif

namespace physics_manager {
	class InfoPhysicWorld;
	class PhysicsManager;

	class LayerInfo {
		friend PhysicsManager;

	private:
		/// @brief Constructora por defecto
		LayerInfo() = default;
		
		/// @brief Constructora 
		/// @param name Nombre de la capa
		/// @param sceneID ID de la escena
		LayerInfo(std::string name, std::string sceneID);

		/// @brief Nombre de la capa
		std::string _name;

		/// @brief ID de la escena
		std::string _sceneID;
	public:
		
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
		/// @brief Crea el codigo Hash necesario para el unordered_map
		/// @param info El elemento que se va a usar en el mapa (Key)
		/// @return Devuelve el codigo Hash creado con el nombre de la capa
		std::size_t operator()(const physics_manager::LayerInfo& info) const
		{
			return std::hash<std::string>()(info.GetName());
		}
	};

	class PhysicsManager : public Singleton<PhysicsManager>
	{
		friend Singleton<PhysicsManager>;
		friend physics_wrapper::RigidBody;
		friend physics_wrapper::RayCast;
		friend eden::Scene;
		friend eden::SceneManager;

	public:

		/// @brief Realiza una actualizacion de la simulacion fisica
		/// @param deltaTime Tiempo entre simulaciones fisicas, como la simulacion se llama con el FixedUdpate, este tiempo es fijo y constante
		/// @param sceneID ID de la escena que se quiere actualizar
		void updateSimulation(float deltaTime, std::string sceneID);

		/// @brief Devuelve la gravedad del mundo
		/// @return Devuelve el valor de la gravedad mundial
		EDEN_API eden_utils::Vector3 GetGravity(std::string sceneID);

		/// @brief Aniade una entidad al mundo fisico
		/// @param e Entidad a añadir
		EDEN_API void AddPhysicsEntity(eden_ec::Entity* e);

		/// @brief Quita una entidad del mundo fisico
		/// @param e Entidad a quitar
		EDEN_API void RemovePhysicsEntity(eden_ec::Entity* e);

		/// @brief Setear a cada rigidbody el transform de cada entidad
		EDEN_API void UpdatePositions(std::string sceneID);

		/// @brief Setear a cada transform de cada entidad el transform del rigidbody
		EDEN_API void ResolvePositions(std::string sceneID);

		/// @brief Destructora de la clase
		~PhysicsManager() override;

		/// @brief Encuentra una capa dado un cierto nombre e ID de escena
		/// @param name Nombre de la capa que se quiere buscar
		/// @param sceneID ID de la escena en la que se encuentra la capa
		/// @return Devuelve una capa dado un cierto nombre e ID de escena, o nullptr en caso de fallar
		EDEN_API physics_wrapper::CollisionLayer* GetLayerByName(std::string name, std::string sceneID);

		EDEN_API static PhysicsManager* getInstance();

	protected:
		/// @brief La constructora se encarga de crear el mundo de la simulacion fisica y el objeto encargado de dibujar 
		PhysicsManager();
	private:

		/// @brief Mapa desordenado que guarda los nombres de las capas y su respectivo objeto CollisionLayer
		std::unordered_map <physics_manager::LayerInfo, physics_wrapper::CollisionLayer*, physics_manager::LayerHash> _layers;

		/// @brief Referencia a los mundos de la simulacion fisica
		std::unordered_map <std::string, InfoPhysicWorld*> _physicsScenes;

		/// @brief Referencia al mundo fisico actual
		btDynamicsWorld* _currentPhysicScene;

		/// @brief  Vector de Gravedad de la escena por defecto
		eden_utils::Vector3 _defaultGravity;

		/// @brief 
		InfoPhysicWorld* info;

		/// @brief Devuelve el mundo
		/// @return Mundo de Bullet
		btDynamicsWorld* GetWorld(std::string sceneID = SCENEID_NULL);

		/// @brief Quita colision a una capa con otra capa (por defecto todas las capas colisionan con todas)
		/// @param layerName Nombre de la capa a la que le se quiere quitar colision
		/// @param collisionToAdd Nombre de la capa con la que no se quiere que colisione
		/// @param sceneID ID de la escena asociada a ambas capas
		void RemoveCollisionToLayer(std::string layerName, std::string collisionToAdd, std::string sceneID);

		/// @brief Crea una capa de colision
		/// @param name Nombre de la capa que se quiere crear
		/// @param sceneID ID de la escena asociada a la capa
		void CreateCollisionLayer(std::string name, std::string sceneID);

		/// @brief Borra todas las capas de una escena
		/// @param sceneID ID de la escena
		void RemoveAllSceneLayers(std::string sceneID);

		/// @brief Crea una nueva escena. Si existe, actualiza la escena actual 
		/// @param sceneID ID de la escena que se quiere crear
		void CreatePhysicsScene(std::string sceneID);

		void SetPhysicsScene(std::string sceneID);

		/// @brief Borra la escena sceneToRemoveID si existe. Luego crea una escena con ID newCurrentSceneID
		/// @param sceneToRemoveID ID de la escena que se quiere borrar
		/// @param newCurrentSceneID ID de la escena que se quiere crear
		void RemovePhysicsScene(std::string sceneToRemoveID, std::string newCurrentSceneID);

		/// @brief Inicializa las capas de colision de una escena
		/// @param sceneID ID de la escena que se quiere inicializar
		/// @param collisionInfo Informacion de la colision
		void InitLayers(std::string sceneID, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo);

	};

	/// @brief Contiene informacion de la escena y las entidades que utilizan Bullet. Cada instancia de esta clase representa una escena.
	class InfoPhysicWorld
	{
		friend PhysicsManager;
#ifdef _DEBUG
		eden_debug::Debug* GetDebug();
#endif
	private:
		/// @brief Constructora de la clase
		InfoPhysicWorld(std::string sceneID);
		
		/// @brief Destructora de la clase
		~InfoPhysicWorld();
		
		/// @brief Referencia al mundo fisico
		btDynamicsWorld* _dynamicWorld;

		/// @brief Clase de bullet encargada de determinar el algortimo de calculo de colisiones entre objetos segun su forma
		btDispatcher* _worldDispatcher;
#ifdef _DEBUG
		/// @brief Encargado de hacer dibujos con caracter de debug
		eden_debug::Debug* _debug;
#endif
		/// @brief Clase de bullet encargada de subdividir el mundo en sectores para facilitar los calculos de colision
		btBroadphaseInterface* _worldBroadPhaseInterface;

		/// @brief Clase de bullet encargada de gestionar las colisiones entre objetos
		btConstraintSolver* _worldConstraintSolver;

		/// @brief Clase de bullet encargada de la configuraci�n de las colisiones.
		btCollisionConfiguration* _worldCollisionConfiguration;

		/// @brief Set desordenado que asigna a cada Entidad su rigidbody correspondiente en la simulacion fisica
		std::unordered_set<eden_ec::Entity*> _entitiesSet;

		/// @brief Devuelve el mundo fisico
		/// @return Devuelve el mundo fisico 
		btDynamicsWorld* GetWorld();
	};
}
#endif // !PHYSICS_MANAGER_h