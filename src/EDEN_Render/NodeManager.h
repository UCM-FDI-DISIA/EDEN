#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_NODE_MANAGER_H
#define EDEN_NODE_MANAGER_H

#include <unordered_map> 
#include <string>

#include "Singleton.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
	class SceneNode;
	class Root;
}
namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_render {
	class RenderManager;
}

namespace render_wrapper {

	class RenderObject;
	/// @brief La clase NodeManager garantiza la abstraccion entre ogre y EDEN. Guarda todos los nodos de la escena actual, un nodo
	/// por entidad creada. Cuando se quiera manejar una entidad (por ejemplo: moverla, girarla, trasladarla, etc...), los wrappers
	/// asociados a sus componentes llamaran a los metodos correspondientes para realizar la accion pasandole la ID de su entidad.
	/// El ID de la entidad es un string unico y propio. El NodeManager guardara en un unordered_map el ID de la Entidad y su nodo asociado. 
	
	/// @brief Cuando se quiera realizar alguna accion, NodeManager buscara el Nodo asociado y, si no lo encuentra, lo crea ya que todo
	/// objeto en escena funciona mediante nodos. Esto garantiza que solo haya un nodo en cada Entidad y no por Componente y, por tanto,
	/// que sea mas eficiente a la hora de actualizar su Transform.
	class NodeManager :  public Singleton<NodeManager>
	{
	public:
		friend Singleton<NodeManager>;

		/// @brief Constructora por del NodeManager. Inicializa el mapa de nodos y hace referencia al RootSceneNode de la escena
		NodeManager();
		
		/// @brief Destructora del NodeManager
		~NodeManager();

		/// @brief Crea un Nodo con el nombre de la Entidad asociada y lo inserta al mapa
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void CreateSceneObject(const std::string id, const std::string sceneID);

		/// @brief Emparenta un nodo a otro y lo inserta en el mapa
		/// @param idChild Identificador de la entidad hijo al que queremos emparentar
		/// @param idParent Identificador de la entidad padre 
		void AddChildToObject(const std::string idChild, const std::string idParent, const std::string sceneID);

		/// @brief Devuelve la poscicion de la entidad, haciendo las transformaciones de Ogre a Vector3 de EDEN
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		/// @return Vector3 con la posicion de la entidad
		eden_utils::Vector3 GetPosition(const std::string id, const std::string sceneID);

		/// @brief Devuelve la escala de la entidad, haciendo las transformaciones de Ogre a Vector3 de EDEN
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		/// @return Vector3 con la escala de la entidad
		eden_utils::Vector3 GetScale(const std::string id, const std::string sceneID);

		/// @brief Modifica la posicion de la entidad
		/// @param pos Vector3 con la nueva posicion 
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void SetPosition(const eden_utils::Vector3 pos, const std::string id, const std::string sceneID);
		
		/// @brief Modifica la orientacion de la entidad
		/// @param pos Quaternion con la nueva orientacion  
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void SetOrientation(const eden_utils::Quaternion quat, const std::string id, const std::string sceneID);

		/// @brief Busca el nodo que se quiera borrar, lo destruye y saca del mapa
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void RemoveSceneObject(const std::string id, const std::string sceneID);

		void RemoveScene(const std::string sceneID);

		/// @brief Muestra la caja delimitadora del nodo 
		/// @param active Booleano para activar o desactivar el BoundingBox
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void ShowBoundingBox(bool active, const std::string id, const std::string sceneID);
		
		/// @brief Modifica la rotacion de la entidad
		/// @param rotation Vector3 con la rotacion que se quiera implementar 
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void Rotate(const eden_utils::Vector3 rotation, const std::string id, const std::string sceneID);
		
		/// @brief Modifica la roatcion relativa al espacio local de la entidad
		/// @param rotation Vector3 con la rotacion que se quiera implementar 
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void RotateLocal(const eden_utils::Vector3 rotation, const std::string id, const std::string sceneID);
		
		/// @brief Modifica la escala de la entidad
		/// @param scale Vector3 con la nueva escala  
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void Scale(const eden_utils::Vector3 scale, const std::string id, const std::string sceneID);

		/// @brief Permite que un nodo apunte/mire hacia una posicion deseada
		/// @param pos Posicion hacia la que queremos que nuestra entidad apunte
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void LookAt(const eden_utils::Vector3 pos, const std::string id, const std::string sceneID);
		
		/// @brief Mueve el nodo hacia una posicion deseada
		/// @param pos Posicion hacia la que queremos que nuestra entidad se mueva
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void Translate(const eden_utils::Vector3 pos, const std::string id, const std::string sceneID);

		/// @brief Asocia entidades de escena de Ogre a un nodo especifico
		/// @param obj La entidad de ogre que queremos añadir a un nodo 
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		void Attach(Ogre::MovableObject* obj, const std::string id, const std::string sceneID);

		/// @brief Comprueba si una entidad tiene un nodo asociado buscandolo en el mapa
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		/// @return Booleano que confirma si dicha entidad tiene un nodo creado o no
		bool HasNode(const std::string id, const std::string sceneID);

	private:

		/// @brief Método privado para asegurarnos que nadie tenga acceso a los nodos de Ogre
		/// Busca en el unordered_map el nodo asociado a la ID de una entidad
		/// @param id Identificador de la Entidad asociada para buscar su nodo
		/// @return Devuelve el nodo para poder realizar cualquier accion sobre el
		Ogre::SceneNode* FindNode(const std::string id, const std::string sceneID);

		/// @brief Metodos para poder convertir los vectores y cuaterniones de Ogre en los nuestros propios de EDEN
		eden_utils::Vector3 ConvertToEdenVector(const Ogre::Vector3 ogreVector);
		eden_utils::Quaternion ConvertToEdenQuaternion(const Ogre::Quaternion ogreQuaternion);
		
		/// @brief Metodos para poder convertir nuestros vectores y cuaterniones de EDEN en los de Ogre
		Ogre::Vector3 ConvertToOgreVector(const eden_utils::Vector3 edenVector);
		Ogre::Quaternion ConvertToOgreQuaternion(const eden_utils::Quaternion edenQuaternion);
		
		/// @brief Mapa que contiene los nodos asociados a un identificador de la entidad
		std::unordered_map <std::string, std::unordered_map<std::string, Ogre::SceneNode*>> _sceneObjectsMap;

		/// @brief Referencia al nodo raiz de Ogre para poder crear el resto de nodos como hijo suyo
		Ogre::SceneNode* _rootNode = nullptr;
		
	};
}
#endif // NODE_H
