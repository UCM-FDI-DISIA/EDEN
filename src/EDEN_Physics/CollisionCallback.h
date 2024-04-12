#ifndef EDEN_COLLISION_CALLBACK_H
#define EDEN_COLLISION_CALLBACK_H

#include <unordered_set>

#pragma warning(push)
#pragma warning(disable : 26495)
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#pragma warning(pop)

#include "defs.h"

namespace eden_ec {
	class Entity;
}

namespace physics_wrapper {
	class RigidBody;

	/// @brief Clase para hacer callbacks de colisiones
	class EDEN_API CollisionCallback : public btCollisionWorld::ContactResultCallback
	{
	public:
		CollisionCallback(RigidBody* rigidBody);
		~CollisionCallback() = default;

		/// @brief Metodo override de Bullet que determina qué hace en una colision
		/// @param cp Informacion del punto en el que colisionan
		/// @param colObj0Wrap Wrapper de colision de Bullet del objeto 1
		/// @param partId0 Parametro necesario para la funcion de bullet que no utilizamos
		/// @param index0 Parametro necesario para la funcion de bullet que no utilizamos
		/// @param colObj1Wrap Wrapper de colision de Bullet del objeto 2
		/// @param partId1 Parametro necesario para la funcion de bullet que no utilizamos
		/// @param index1 Parametro necesario para la funcion de bullet que no utilizamos
		/// @return Escalar de Bullet que no utilizamos
		btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override;
	private:
		RigidBody* _myRigidBody;
		std::unordered_set<eden_ec::Entity*> _otherEntities;
	};
}
#endif // !1




