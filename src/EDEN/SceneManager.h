#ifndef EDEN_SCENE_MANAGER_H
#define EDEN_SCENE_MANAGER_H

#include <deque>
#include <string>

#include "Singleton.h"


namespace eden {
class Scene;
/// @brief Clase que se encarga de gestionar las escenas, es decir, cargarlas y descargarlas, hacer su update, etc...
class SceneManager : public Singleton<SceneManager> {
	friend Singleton<SceneManager>;

public:
	/// @brief Destructora por defecto de la clase SceneManager
	~SceneManager() override;

	/// @brief Metodo encargado de crear una nueva escena y añadirla a la lista doblemente enlazada
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	Scene* PushScene(const std::string& ID);

	/// @brief Metodo encargado de vaciar la lista de escenas y añadir una nueva
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recien creada
	Scene* ChangeScene(const std::string& ID);

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

private:
	/// @brief Puntero a la primera escena de la lista, a la cual se llama a su Update
	Scene* _activeScene = nullptr;

	/// @brief Lista doblemente enlazada de punteros a escenas
	std::deque<Scene*> _scenes;

	/// @brief Constructora por defecto de la clase SceneManager
	SceneManager() = default;
};
}

#endif // SCENE_MANAGER_H