#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <deque>
#include <string>

#include "Singleton.h"

class Scene;
class SceneManager : public Singleton<SceneManager> {
	friend Singleton<SceneManager>;

public:
	SceneManager() = default;
	virtual ~SceneManager();

	/// @brief Metodo encargado de crear una nueva escena y añadirla a la lista doblemente enlazada
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recién creada
	Scene* PushScene(const std::string& ID);

	/// @brief Metodo encargado de vaciar la lista de escenas y añadir una nueva
	/// @param ID El nombre que identifica a la escena
	/// @return El puntero a la escena recién creada
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
};

#endif // SCENE_MANAGER_H