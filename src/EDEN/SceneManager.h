#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SCENE_MANAGER_H
#define EDEN_SCENE_MANAGER_H

#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Singleton.h"

#include "defs.h"

namespace eden_script {
	struct EntityInfo;
	class ComponentArguments;
}

namespace eden_ec {
	class Entity;
}

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden {
class EDEN_API Scene;
/// @brief Clase que se encarga de gestionar las escenas, es decir, cargarlas y descargarlas, hacer su update, etc...
class SceneManager : public Singleton<SceneManager> {
	friend Singleton<SceneManager>;

public:
	/// @brief Destructora por defecto de la clase SceneManager
	~SceneManager() override;

	/// @brief Metodo encargado de crear una nueva escena y aniadirla a la lista doblemente enlazada
	/// @param ID El nombre que identifica a la escena
	void PushScene(const std::string& ID);

	/// @brief Metodo encargado de vaciar la lista de escenas y añadir una nueva
	/// @param ID El nombre que identifica a la escena
	void ChangeScene(const std::string& ID);

	/// @brief Metodo encargado de eliminar la primera escena de la lista
	void PopScene();

	/// @brief Metodo encargado de eliminar la(s) primera(s) escena(s) de la lista hasta encontrar
	/// una con el ID indicado
	/// @param ID El nombre que identifica a la escena
	void PopUntil(const std::string& ID);

	/// @brief Metodo encargado de eliminar todas las escenas de la lista
	void EmptyStack();

	/// @brief Metodo que llama al Update de la primera escena de la lista, y al render de todas las
	/// escenas que lo indiquen. Ademas, al final del bucle elimina las escenas que lo requieran;
	/// @param dt El DeltaTime
	void Update(float dt);

	/// @brief Metodo que devuelve la primera escena de la lista
	/// @return La escena activa
	inline Scene* GetCurrentScene() { return _activeScene; }

	/// @brief Crea una instancia de un blueprint en la escena. Puede cambiarse su posición y rotación
	/// @param blueprintID el ID del blueprint a instanciar en la escena.
	/// @param pos Nueva posición para entidad
	/// @param rot Nueva orientación para entidad
	/// @return Nueva entidad creada
	/// @warning No se aplicaran cambios de posicion ni rotacion si la entidad NO tiene CTransform. NO se le pondra uno automáticamente.
	eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos, eden_utils::Quaternion rot);
	eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Vector3 pos);
	eden_ec::Entity* InstantiateBlueprint(std::string blueprintID, eden_utils::Quaternion rot);
	eden_ec::Entity* InstantiateBlueprint(std::string blueprintID);

private:
	/// @brief Puntero a la primera escena de la lista, a la cual se llama a su Update
	Scene* _activeScene = nullptr;

	/// @brief Guarda informacion de un Blueprint. 
	struct BlueprintInfo {
		/// @brief Componentes que definen la entidad
		std::vector<eden_script::ComponentArguments> components;
		/// @brief Numero de veces que se ha instanciado
		int numInstances = 0;
	};

	/// @brief Guarda la informacion de los Blueprints leidos desde Lua
	static std::unordered_map<std::string, BlueprintInfo> _Blueprints;

	/// @brief Lista doblemente enlazada de punteros a escenas
	std::deque<Scene*> _scenes;

	/// @brief Lista doblemente enlazada que contiene el identificador de las escenas que se quieren crear
	std::deque<std::string> _scenesToAdd;

	/// @brief Lista doblemente enlazada de punteros a escenas que se quieren borrar
	std::deque<Scene*> _scenesToDestroy;

	/// @brief Identificadores de las escenas actuales
	std::unordered_set<std::string> _currentScenes;

	/// @brief Constructora por defecto de la clase SceneManager
	SceneManager();

	/// @brief Crea una escena
	/// @param ID Identificador de la escena que se quiere crear
	void CreateScene(std::string& ID);
};
}

#endif // SCENE_MANAGER_H