#include "RayCast.h"
#include "PhysicsManager.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "../../dependencies/Bullet/src/src/LinearMath/btIDebugDraw.h"


physics_wrapper::RayCast::RayCast(btDynamicsWorld* worldRef, btIDebugDraw* drawerRef)
{
	_dynamicWorldRef = worldRef;
	_debugDrawer = drawerRef;
	_physicsManagerInstance = physics_manager::PhysicsManager::Instance();
}

const physics_wrapper::RayCastHitResult& physics_wrapper::RayCast::singleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor) const
{
	btVector3 origin(rayOrigin.GetX(), rayOrigin.GetY(), rayOrigin.GetZ());
	btVector3 destiny(rayDestiny.GetX(), rayDestiny.GetY(), rayDestiny.GetZ());
	btCollisionWorld::ClosestRayResultCallback result(origin, destiny);
	if (drawDebugLine && _debugDrawer != nullptr) {
		btVector3 lineColor(debugLineColor.GetX(), debugLineColor.GetY(), debugLineColor.GetZ());
		_debugDrawer->drawLine(origin, destiny, lineColor);
	}
	_dynamicWorldRef->rayTest(origin, destiny, result);
	eden_utils::Vector3 rHitPoint(result.m_hitPointWorld.getX(), result.m_hitPointWorld.getY(), result.m_hitPointWorld.getZ());
	eden_utils::Vector3 rHitNormal(result.m_hitNormalWorld.getX(), result.m_hitNormalWorld.getY(), result.m_hitNormalWorld.getZ());
	const eden_ec::Entity* hitEntity = (eden_ec::Entity*)(btRigidBody::upcast(result.m_collisionObject))->getUserPointer();
	RayCastHitResult hitResult{ result.hasHit(), rHitPoint, rHitNormal, hitEntity };
	return hitResult;
}

const std::vector<physics_wrapper::RayCastHitResult> physics_wrapper::RayCast::multipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor) const
{
	btVector3 origin(rayOrigin.GetX(), rayOrigin.GetY(), rayOrigin.GetZ());
	btVector3 destiny(rayDestiny.GetX(), rayDestiny.GetY(), rayDestiny.GetZ());
	btCollisionWorld::AllHitsRayResultCallback result(origin, destiny);
	if (drawDebugLine) {
		btVector3 lineColor(debugLineColor.GetX(), debugLineColor.GetY(), debugLineColor.GetZ());
		_debugDrawer->drawLine(origin, destiny, lineColor);
	}
	_dynamicWorldRef->rayTest(origin, destiny, result);
	int numCollisions = result.m_hitPointWorld.size();
	std::vector<RayCastHitResult> multipleHitResult(numCollisions);
	eden_utils::Vector3 rHitPoint;
	eden_utils::Vector3 rHitNormal;
	const eden_ec::Entity* hitEntity = nullptr;
	for (int i = 0; i < numCollisions; ++i) {
		rHitPoint = { result.m_hitPointWorld[i].getX(), result.m_hitPointWorld[i].getY(), result.m_hitPointWorld[i].getZ()};
		rHitNormal = { result.m_hitNormalWorld[i].getX(), result.m_hitNormalWorld[i].getY(), result.m_hitNormalWorld[i].getZ() };
		hitEntity = (eden_ec::Entity*)(btRigidBody::upcast(result.m_collisionObjects[i]))->getUserPointer();
		multipleHitResult[i] = { result.hasHit(), rHitPoint, rHitNormal, hitEntity };
	}
	return multipleHitResult;
}

physics_wrapper::RayCast::~RayCast()
{
	
}
