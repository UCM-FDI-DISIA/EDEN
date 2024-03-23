#ifndef EDEN_COLLISIONLAYER_H
#define EDEN_COLLISIONLAYER_H

#include <string>
namespace physics_manager {
	class PhysicsManager;
}

namespace physics_wrapper {
	class CollisionLayer
	{
		friend physics_manager::PhysicsManager;
	private:
		static int _currentLayer;
		const std::string _layerName;
		const int _layer;
		int _collisionMask = 0;
		CollisionLayer(std::string layerName);
		void AddCollisionToLayer(physics_wrapper::CollisionLayer* layer);
	public:
		std::string GetName();
		int GetLayer();
		int GetCollisionMask();
	};
}
#endif

