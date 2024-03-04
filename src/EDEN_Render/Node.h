#ifndef NODE_H
#define NODE_H

#include <unordered_map> 
#include <string>

#include "Singleton.h"

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace Ogre {
	class SceneNode;
	class Root;
}
namespace eden_render {
	class RenderManager;
}

namespace render_wrapper {
	
	class RenderObject;
	class Node :  public Singleton<Node>
	{
	public:
		friend Singleton<Node>;

		Node();
		
		~Node();

		void CreateSceneObject(const std::string id);

		void AddChildToObject(const std::string idChild, const std::string idParent);

		eden_utils::Vector3 GetPosition(const std::string id);

		eden_utils::Vector3 GetScale(const std::string id);

		void SetPosition(const eden_utils::Vector3 pos, const std::string id);
		
		void SetOrientation(const eden_utils::Quaternion quat, const std::string id);

		void RemoveSceneObject(const std::string id);

		void ShowBoundingBox(bool active, const std::string id);
		
		void Rotate(const eden_utils::Vector3 rotation, const std::string id);
		
		void RotateLocal(const eden_utils::Vector3 rotation, const std::string id);
		
		void Scale(const eden_utils::Vector3 scale, const std::string id);

		void LookAt(const eden_utils::Vector3 pos, const std::string id);
		
		void Translate(const eden_utils::Vector3 pos, const std::string id);

		void Attach(render_wrapper::RenderObject* obj, const std::string id);

	private:

		Ogre::SceneNode* FindNode(const std::string id);

		eden_utils::Vector3 convertToEdenVector(const Ogre::Vector3 ogreVector);
		eden_utils::Quaternion convertToEdenQuaternion(const Ogre::Quaternion ogreQuaternion);
		
		Ogre::Vector3 convertToOgreVector(const eden_utils::Vector3 edenVector);
		Ogre::Quaternion convertToOgreQuaternion(const eden_utils::Quaternion edenQuaternion);
		
		std::unordered_map<std::string, Ogre::SceneNode*> _sceneObjectsMap;

		Ogre::SceneNode* _rootNode = nullptr;
		
	};
}
#endif // NODE_H
