#pragma warning(push)
#pragma warning(disable : 26495)
#include <BulletDynamics/Dynamics/btRigidBody.h>
#pragma warning(pop)

#include "CollisionCallback.h"
#include "RigidBody.h"
#include "Entity.h"
#include "CRigidBody.h"
#include "CollisionLayer.h"

physics_wrapper::CollisionCallback::CollisionCallback(RigidBody* rigidBody)
{
	_myRigidBody = rigidBody;
}

btScalar physics_wrapper::CollisionCallback::addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	eden_ec::Entity* otherEntity = nullptr;

	if (colObj0Wrap->getCollisionObject() == _myRigidBody->getBulletRigidBody()) {
		otherEntity = static_cast<eden_ec::Entity*>(colObj1Wrap->getCollisionObject()->getUserPointer());
	}
	else {
		otherEntity = static_cast<eden_ec::Entity*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	}
	eden_ec::CRigidBody* rb = static_cast<eden_ec::Entity*>(_myRigidBody->getBulletRigidBody()->getUserPointer())->GetComponent<eden_ec::CRigidBody>();
	eden_ec::CRigidBody* otherRb = otherEntity->GetComponent<eden_ec::CRigidBody>();

	if ((rb->GetCollisionLayer()->GetCollisionMask() & otherRb->GetCollisionLayer()->GetLayer()) != 0) {
		if(cp.getDistance() < 0){
			//Acaba de haber colisión
			if (_otherEntities.find(otherEntity) == _otherEntities.end()) {
				_otherEntities.insert(otherEntity);
				rb->OnCollisionEnter(otherEntity);
			}
			else { //Ya había colisión y permanece en ella
				rb->OnCollisionStay(otherEntity);
			}
		}
		else { //La distancia es mayor que 0 por lo que está saliendo de la colisión
			if(_otherEntities.find(otherEntity) != _otherEntities.end())
				_otherEntities.erase(otherEntity);
			rb->OnCollisionExit(otherEntity);
		}
	}

	return btScalar();
}
