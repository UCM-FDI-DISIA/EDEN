#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SCENE_H
#define EDEN_SCENE_H

#include <string>
#include <unordered_map>

#include "defs.h"
#include "ComponentArguments.h"

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
	class SceneManager;

	/// @brief Clase que define una escena de juego. Tendra un render, un update y todos los metodos que se encarguen del manejo de los gameobjects que
	/// la componen.
	class EDEN_API Scene
	{
		friend SceneManager;
	public:
		Scene(const std::string& ID);
		~Scene();

		/// @brief Metodo que devuelve el nombre identificativo de la escena
		inline std::string GetSceneID() { return _ID; }

		/// @brief Llama al render de todas las entidades de la escena
		void Render();

		/// @brief Llama al update de todas las entidades de la escena
		void Update(float dt);

		/// @brief Instancia una serie de entidades en la escena
		/// @param info Informacion de las entidades a instanciar
		void Instantiate(std::vector<eden_script::EntityInfo*> info);

		/// @brief Al principio la ejecucion del juego, anade una entidad nueva al mapa de entidades 
		/// @param id id Nombre de la entidad que se va a crear nueva
		void AddNewGameObject(eden_ec::Entity* _ent);

		/// @brief Durante la ejecucion del juego, anade una entidad nueva al mapa de entidades 
		/// @param id id Nombre de la entidad que se va a crear nueva
		bool AddExistingGameObject(eden_ec::Entity* _ent);

		/// @brief Durante la ejecucion del juego, borra una entidad del mapa de entidades 
		/// @param id id Nombre de la entidad que se va a borrar
		bool RemoveGameObject(eden_ec::Entity* _ent);

		/// @brief Devuleve una referencia a la camara actual 
		inline eden_ec::Entity* GetCurrentCamara() { return _currentCamera; }

		/// @brief Cambia la referencia de la variable que indica cual es la camara actual  
		/// @param cam Referencia a la nueva camara actual
		inline void SetCurrentCamara(eden_ec::Entity* cam) { _currentCamera = cam; }

		/// @brief Aniade un componente a la entidad dado su tipo y los argumentos que requiera el
		/// @tparam id Nombre de la entidad a la que queremos acceder
		/// @return Componente creado
		eden_ec::Entity* GetEntityByID(const std::string& ID);

		/// @brief Indica si la escena quiere renderizar sus elementos
		inline void SetToRender(bool render) { _isRendering = render; }

		/// @brief Devuelve la variable que indica si la escena se va a renderizar
		/// @return _isRendering True = se renderiza | _isRendering = no se renderiza
		inline bool GetToRender() { return _isRendering; }

		/// @brief Instancia una entidad en la escena. Puede cambiarse su posicion y rotacion
		/// @param info Informaci�n de una entidad 
		/// @param pos Nueva posici�n para entidad
		/// @param rot Nueva orientaci�n para entidad
		/// @return Nueva entidad creada
		/// @warning No se aplicar�n cambios de posicion ni rotacion si la entidad NO tiene CTransform. NO se le pondra uno autom�ticamente.
		eden_ec::Entity* Instantiate(eden_script::EntityInfo* info, eden_utils::Vector3 pos, eden_utils::Quaternion rot);
		eden_ec::Entity* Instantiate(eden_script::EntityInfo* info, eden_utils::Vector3 pos);
		eden_ec::Entity* Instantiate(eden_script::EntityInfo* info, eden_utils::Quaternion rot);
		eden_ec::Entity* Instantiate(eden_script::EntityInfo* info);
	private:
		void InitScene(std::vector<eden_script::EntityInfo*>& info, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo);
		/// @brief Llama al Awake de las entidades que van a a�adirse a la escena. Se hace al final de cada frame si nuevas entidades se han a�adido a la escena
		void AwakeEntities();
		/// @brief Llama al Start de las entidades que van a a�adirse a la escena. Se hace al principio de cada frame si nuevas entidades se a�adieron a la escena en el frame anterior
		void StartEntities();

		///@brief identificador de escena
		std::string _ID;

		///@brief booleano que indica si la escena esta activa. Si una escena no esta activa no se ejecutara el 
		/// update pero si se seguiran renderizando sus entidades
		bool _isRendering = true;

		int _currentIteration = 0;

		/// @brief referencia a la camara actual
		eden_ec::Entity* _currentCamera = nullptr;

		/// @brief mapa que contiene las referencias a todas las entidades de la escena
		std::unordered_map<std::string, eden_ec::Entity*> _gameEntitiesList;

		/// @brief Vector que tiene las entidades que se a�adir�n al final del frame
		std::unordered_map<int, std::unordered_map<std::string, eden_ec::Entity*>> _newEntities;
	};
}
#endif // SCENE_H
