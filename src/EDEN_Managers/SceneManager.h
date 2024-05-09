#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SCENE_MANAGER_H
#define EDEN_SCENE_MANAGER_H

#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "ComponentArguments.h"
#include "Singleton.h"

#include "defs.h"

namespace eden_script {
	struct EntityInfo;
}

namespace eden_ec {
	class Entity;
}

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden {
class Scene;
/// @brief Clase que se encarga de gestionar las escenas, es decir, cargarlas y descargarlas, hacer su update, etc...
class SceneManager : public Singleton<SceneManager> {
	friend Singleton<SceneManager>;
	friend Scene;
public:
	/// @brief Destructora por defecto de la clase SceneManager
	EDEN_API ~SceneManager() override;

	/// @brief Metodo encargado de crear una nueva escena y aniadirla a la lista doblemente enlazada
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	EDEN_API void PushScene(const std::string& ID);

	/// @brief Metodo encargado de vaciar la lista de escenas y a�adir una nueva
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	EDEN_API void ChangeScene(const std::string& ID);

	/// @brief Metodo encargado de eliminar la primera escena de la lista
	EDEN_API void PopScene();

	/// @brief Metodo encargado de eliminar la(s) primera(s) escena(s) de la lista hasta encontrar
	/// una con el ID indicado
	/// @param ID El nombre que identifica a la escena
	EDEN_API void PopUntil(const std::string& ID);

	/// @brief Metodo encargado de eliminar todas las escenas de la lista
	EDEN_API void EmptyStack();

	/// @brief Metodo que llama al Update de la primera escena de la lista, y al render de todas las
	/// escenas que lo indiquen. Ademas, al final del bucle elimina las escenas que lo requieran;
	/// @param dt El DeltaTime
	EDEN_API void Update(float dt);

	/// @brief Metodo que devuelve la primera escena de la lista
	/// @return La escena activa
	EDEN_API inline Scene* GetCurrentScene() { return _activeScene; }

	EDEN_API static SceneManager* getInstance();

	EDEN_API inline bool BlueprintExists(std::string ID) { return _Blueprints.count(ID); }

	/// @brief M�todo que permite buscar una entidad en la escena actual, dado su ID
	/// @param id ID de la Entidad a buscar
	/// @return Devuelve el puntero a una entidad, devolver� nullptr si la entidad no existe en la escena
	EDEN_API eden_ec::Entity* FindEntity(std::string ID);

	/// @brief Busca todas las entidades con un componente dado y las devuelve
	/// @param componentID Componente a buscar
	/// @return Vector con todas las entidades que contengan ese component
	EDEN_API std::vector<eden_ec::Entity*> GetEntitiesWithComponent(std::string componentID);

	/// @brief Crea una instancia de un blueprint en la escena. Puede cambiarse su posici�n y rotaci�n
	/// @param blueprintID el ID del blueprint a instanciar en la escena.
	/// @param pos Nueva posici�n para entidad
	/// @param rot Nueva orientaci�n para entidad
	/// @return Nueva entidad creada
	/// @warning No se aplicar�n cambios de posici�n ni rotaci�n si la entidad NO tiene CTransform. NO se le pondr� uno autom�ticamente.
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos, eden_utils::Quaternion rot);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Quaternion rot);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID);
	EDEN_API bool AddEntityToDontDestroyOnLoad(eden_ec::Entity* ent, bool isAudio=false);
	EDEN_API inline std::string GetDontDestroyOnLoadID() { return _dontDestroyOnLoadID; }

	EDEN_API inline void SetDebugLog(bool debug) {
#ifdef _DEBUG
		_debugLog = debug;
#endif // _DEBUG
	}
private:

	bool _dontDestroySceneCreated = false;

	/// @brief Puntero a la primera escena de la lista, a la cual se llama a su Update
	Scene* _activeScene = nullptr;

	///@brief Escena DontDestroyOnLoad
	Scene* _dontDestroyOnLoadScene = nullptr;
	std::string _dontDestroyOnLoadID = "DontDestroyOnLoad";

	/// @brief Guarda informacion de un Blueprint. 
	struct BlueprintInfo {
		/// @brief Componentes que definen la entidad
		std::vector<eden_script::ComponentArguments> components;
		/// @brief Numero de veces que se ha instanciado
		int numInstances = 0;
	};

	/// @brief Devuelve los componentes de un Blueprint 
	/// @param ID ID del Blueprint que nos interesa
	/// @return Los componentes del Blueprint
	EDEN_API inline std::vector<eden_script::ComponentArguments> GetBlueprintComponents(std::string ID) { return (*_Blueprints.find(ID)).second.components; }
	/// @brief Devuelve el n�mero de instancias activas de un Blueprint
	/// @param ID ID del Blueprint que nos interesa
	/// @return El n�mero de instancias del Blueprint que nos interesa
	EDEN_API inline int GetBlueprintNumInstances(std::string ID) { return (*_Blueprints.find(ID)).second.numInstances; }
	/// @brief Suma 1 al n�mero de instancias de un Blueprint concreto
	/// @param ID ID del Blueprint que nos interesa
	EDEN_API inline void IncreaseBlueprintNumInstances(std::string ID) { (*_Blueprints.find(ID)).second.numInstances++; }


	/// @brief Guarda la informaci�n de los Blueprints le�dos desde Lua
	std::unordered_map<std::string, BlueprintInfo> _Blueprints;

	/// @brief Lista doblemente enlazada de punteros a escenas
	std::deque<Scene*> _scenes;

	/// @brief Lista doblemente enlazada que contiene el identificador de las escenas que se quieren crear
	std::deque<std::string> _scenesToAdd;

	/// @brief Lista doblemente enlazada de punteros a escenas que se quieren borrar
	std::deque<Scene*> _scenesToDestroy;

	/// @brief Identificadores de las escenas actuales
	std::unordered_set<std::string> _currentScenes;

	/// @brief Constructora por defecto de la clase SceneManager
	EDEN_API SceneManager();

	/// @brief Crea una escena
	/// @param ID Identificador de la escena que se quiere crear
	void CreateScene(std::string& ID);

	bool _debugLog = false;
};
}

#endif // SCENE_MANAGER_H