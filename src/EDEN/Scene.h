#ifndef SCENE_H
#define SCENE_H

#include<string>
#include<unordered_map>

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
	class Scene
	{
	public:
		Scene(const std::string& ID, std::vector<eden_script::EntityInfo*> info);
		~Scene();

		/// @brief Método que devuelve el nombre identificativo de la escena
		inline std::string GetSceneID() { return _ID; }

		/// @brief Llama al render de todas las entidades de la escena
		void Render();

		/// @brief Llama al update de todas las entidades de la escena
		void Update(float dt);

		/// @brief Durante la ejecución del juego, añade una entidad nueva al mapa de entidades 
		/// @param id id Nombre de la entidad que se va a crear nueva
		void AddGameObject(const std::string& ID, eden_ec::Entity* _ent);

		/// @brief Devuleve una referencia a la cámara actual 
		inline eden_ec::Entity* GetCurrentCamara() { return _currentCamera; }

		/// @brief Cambia la referencia de la variable que indica cuál es la cámara actual  
		/// @param cam Referencia a la nueva cámara actual
		inline void SetCurrentCamara(eden_ec::Entity* cam) { _currentCamera = cam; }

		/// @brief Añade un componente a la entidad dado su tipo y los argumentos que requiera el
		/// @tparam id Nombre de la entidad a la que queremos acceder
		/// @return Componente cread
		eden_ec::Entity* GetEntityByID(const std::string& ID);

		/// @brief Inidica si la escena quiere renderizar sus elementos
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

		///@brief booleano que indica si la escena esta activa. Si una escena no esta activa no se ejecutará el 
		/// update pero si se seguirán renderizando sus entidades
		bool _isRendering = true;

		///@brief booleano que se activa cuando se quiere destruir una escena
		bool _toDestroy = false;

		/// @brief referencia a la cámara actual
		eden_ec::Entity* _currentCamera = nullptr;

		/// @brief mapa que contiene las referencias a todas las entidades de la escena
		std::unordered_map<std::string, eden_ec::Entity*> _gameEntitiesList;


	};
}
#endif // SCENE_H
