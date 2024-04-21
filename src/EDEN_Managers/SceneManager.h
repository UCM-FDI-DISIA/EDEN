#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SCENE_MANAGER_H
#define EDEN_SCENE_MANAGER_H

#include <deque>
#include <vector>
#include <string>
#include <unordered_map>

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

	/// @brief Metodo encargado de crear una nueva escena y añadirla a la lista doblemente enlazada
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	EDEN_API Scene* PushScene(const std::string& ID);

	/// @brief Metodo encargado de vaciar la lista de escenas y añadir una nueva
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	EDEN_API Scene* ChangeScene(const std::string& ID);

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

	/// @brief Crea una instancia de un blueprint en la escena. Puede cambiarse su posición y rotación
	/// @param blueprintID el ID del blueprint a instanciar en la escena.
	/// @param pos Nueva posición para entidad
	/// @param rot Nueva orientación para entidad
	/// @return Nueva entidad creada
	/// @warning No se aplicarán cambios de posición ni rotación si la entidad NO tiene CTransform. NO se le pondrá uno automáticamente.
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos, eden_utils::Quaternion rot);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Quaternion rot);
	EDEN_API eden_ec::Entity* InstantiateBlueprint(std::string blueprintID);
private:


	/// @brief Puntero a la primera escena de la lista, a la cual se llama a su Update
	Scene* _activeScene = nullptr;

	/// @brief Guarda información de un Blueprint. 
	struct BlueprintInfo {
		/// @brief Componentes que definen la entidad
		std::vector<eden_script::ComponentArguments> components;
		/// @brief Número de veces que se ha instanciado
		int numInstances = 0;
	};

	EDEN_API inline std::vector<eden_script::ComponentArguments> GetBlueprintComponents(std::string ID) { return (*_Blueprints.find(ID)).second.components; }
	EDEN_API inline int GetBlueprintNumInstances(std::string ID) { return (*_Blueprints.find(ID)).second.numInstances; }
	EDEN_API inline void IncreaseBlueprintNumInstances(std::string ID) { (*_Blueprints.find(ID)).second.numInstances++; }


	/// @brief Guarda la información de los Blueprints leídos desde Lua
	std::unordered_map<std::string, BlueprintInfo> _Blueprints;

	/// @brief Lista doblemente enlazada de punteros a escenas
	std::deque<Scene*> _scenes;

	/// @brief Lista doblemente enlazada de punteros a escenas
	std::deque<Scene*> _scenesToDestroy;

	/// @brief Constructora por defecto de la clase SceneManager
	EDEN_API SceneManager();
};
}

#endif // SCENE_MANAGER_H