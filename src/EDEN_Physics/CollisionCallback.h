#ifndef EDEN_COLLISION_CALLBACK_H
#define EDEN_COLLISION_CALLBACK_H

#include<unordered_set>

#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>

namespace eden_ec {
	class Entity;
}

namespace physics_wrapper {
	class RigidBody;

	/// @brief Clase para hacer callbacks de colisiones
	class CollisionCallback : public btCollisionWorld::ContactResultCallback
	{
	public:
		CollisionCallback(RigidBody* rigidBody);
		~CollisionCallback() = default;

		btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override;
	private:
		RigidBody* _myRigidBody;
		std::unordered_set<eden_ec::Entity*> _otherEntities;
	};
}
#endif // !1




