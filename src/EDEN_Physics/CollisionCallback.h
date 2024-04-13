#ifndef EDEN_COLLISION_CALLBACK_H
#define EDEN_COLLISION_CALLBACK_H

//#include <unordered_set>
#include <unordered_map>

#pragma warning(push)
#pragma warning(disable : 26495)
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#pragma warning(pop)

namespace eden_ec {
	class Entity;
	class CRigidBody;
}

namespace physics_wrapper {
	class RigidBody;

	/// @brief Clase para hacer callbacks de colisiones
	class CollisionCallback : public btCollisionWorld::ContactResultCallback
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
	
		/// @brief Método que se encarga de eliminar las entidades que no han colisionado recientemente
		void UpdateCollisions();
	private:
		/// @brief Referencia al RigidBody de la entidad
		RigidBody* _myRigidBody;
		/// @brief Referencia al componente RigidBody de la entidad
		eden_ec::CRigidBody* rb;
		/// @brief Mapa desordenado que guarda qué entidades colisionan con este rigidbodyç
		/// @brief El booleano es para marcar aquellas entidades que han colisionado en el anterior frame, aquellas que lo tengan a false, se considerará que ya no están colisionando
		std::unordered_map<eden_ec::Entity*, bool> _otherEntities;
	};
}
#endif // !1




