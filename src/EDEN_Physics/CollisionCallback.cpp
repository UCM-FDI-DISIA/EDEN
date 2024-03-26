#include <BulletDynamics/Dynamics/btRigidBody.h>

#include "CollisionCallback.h"
#include "RigidBody.h"
#include<Entity.h>
#include<CRigidBody.h>

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

	if(cp.getDistance() < 0){
		//Acaba de haber colisión
		if (_otherEntities.find(otherEntity) == _otherEntities.end()) {
			_otherEntities.insert(otherEntity);
			static_cast<eden_ec::Entity*>(_myRigidBody->getBulletRigidBody()->getUserPointer())->GetComponent<eden_ec::CRigidBody>()->OnCollisionEnter(otherEntity);
		}
		else { //Ya había colisión y permanece en ella
			static_cast<eden_ec::Entity*>(_myRigidBody->getBulletRigidBody()->getUserPointer())->GetComponent<eden_ec::CRigidBody>()->OnCollisionStay(otherEntity);
		}
	}
	else { //La distancia es mayor que 0 por lo que está saliendo de la colisión
		if(_otherEntities.find(otherEntity) != _otherEntities.end())
			_otherEntities.erase(otherEntity);
		static_cast<eden_ec::Entity*>(_myRigidBody->getBulletRigidBody()->getUserPointer())->GetComponent<eden_ec::CRigidBody>()->OnCollisionExit(otherEntity);
	}

	return btScalar();
}
