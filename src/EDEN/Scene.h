#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <unordered_map>

namespace eden_script {
	struct EntityInfo;
}
namespace eden_render {
	class RenderManager;
}
namespace eden_ec {
	class Entity;
}

namespace eden {
	/// @brief Clase que define una escena de juego. Tendra un render, un update y todos los metodos que se encarguen del manejo de los gameobjects que
	/// la componen.
	class Scene
	{
	public:
		/// @brief Constructora por defecto de la clase Scene
		/// @param ID Identificador de la escena
		/// @param info Informacion de las entidades que estan en la escena
		Scene(const std::string& ID, std::vector<eden_script::EntityInfo*> info);
		~Scene();

		/// @brief Metodo que devuelve el nombre identificativo de la escena
		inline std::string GetSceneID() { return _ID; }

		/// @brief Llama al render de todas las entidades de la escena
		void Render();

		/// @brief Llama al update de todas las entidades de la escena
		void Update(float dt);

		/// @brief Durante la ejecucion del juego, anade una entidad nueva al mapa de entidades 
		/// @param id id Nombre de la entidad que se va a crear nueva
		void AddGameObject(const std::string& ID, eden_ec::Entity* _ent);

		/// @brief Devuleve una referencia a la camara actual 
		inline eden_ec::Entity* GetCurrentCamara() { return _currentCamera; }

		/// @brief Cambia la referencia de la variable que indica cual es la cámara actual  
		/// @param cam Referencia a la nueva camara actual
		inline void SetCurrentCamara(eden_ec::Entity* cam) { _currentCamera = cam; }

		/// @brief Anade un componente a la entidad dado su tipo y los argumentos que requiera el
		/// @tparam id Nombre de la entidad a la que queremos acceder
		/// @return Componente creado
		eden_ec::Entity* GetEntityByID(const std::string& ID);

		/// @brief Indica si la escena quiere renderizar sus elementos
		inline void SetToRender(bool render) { _isRendering = render; }

		/// @brief Devuelve la variable que indica si la escena se va a renderizar
		/// @return _isRendering True = se renderiza | _isRendering = no se renderiza
		inline bool GetToRender() { return _isRendering; }

		/// @brief Pone a true el booleano correpondiente para indicar que va a ser destruida
		inline void SetToDestroy() { _toDestroy = true; }

		/// @brief Devuelve la variable que indica si la escena se va a eliminar
		/// @return _toDestroy True = no se quiere destruir | _toDestroy = se va a destruir
		inline bool GetToDestroy() { return _toDestroy; }

	private:
		///@brief identificador de escena
		std::string _ID;

		//OgreWrapper _renderScene;

		///@brief booleano que indica si la escena esta activa. Si una escena no esta activa no se ejecutara el 
		/// update pero si se seguirán renderizando sus entidades
		bool _isRendering = true;

		///@brief booleano que se activa cuando se quiere destruir una escena
		bool _toDestroy = false;

		/// @brief referencia a la camara actual
		eden_ec::Entity* _currentCamera = nullptr;

		/// @brief mapa que contiene las referencias a todas las entidades de la escena
		std::unordered_map<std::string, eden_ec::Entity*> _gameEntitiesList;
	};
}
#endif // SCENE_H
