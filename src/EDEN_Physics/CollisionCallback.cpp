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
	rb = static_cast<eden_ec::Entity*>(_myRigidBody->getBulletRigidBody()->getUserPointer())->GetComponent<eden_ec::CRigidBody>();
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
	eden_ec::CRigidBody* otherRb = otherEntity->GetComponent<eden_ec::CRigidBody>();

	if ((rb->GetCollisionLayer()->GetCollisionMask() & otherRb->GetCollisionLayer()->GetLayer()) != 0) {
		if(cp.getDistance() <= 0){
			//Acaba de haber colision
			if (_otherEntities.find(otherEntity) == _otherEntities.end()) {
				//_otherEntities.insert(std::make_pair(otherEntity, true));
				rb->OnCollisionEnter(otherEntity);
			}
			else { //Ya había colision y permanece en ella
				rb->OnCollisionStay(otherEntity);
				//_otherEntities[otherEntity] = true;
			}
		}
	}
	return btScalar();
}

void physics_wrapper::CollisionCallback::UpdateCollisions()
{
	/*auto it = _otherEntities.begin();
	while (it != _otherEntities.end()) {
		if (!it->second) {
			rb->OnCollisionExit(it->first);
			it = _otherEntities.erase(it);
		}
		else {
			it->second = false;
			++it;
		}
	}*/
}
