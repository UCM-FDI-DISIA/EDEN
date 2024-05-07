#define _CRTDBG_MAP_ALLOC
#pragma warning(push)
#pragma warning(disable : 26495)
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btIDebugDraw.h>
#pragma warning(pop)

#include "RayCast.h"
#include "Entity.h"
#include "CRigidBody.h"
#include "PhysicsManager.h"


physics_wrapper::RayCast::RayCast(btDynamicsWorld* worldRef, btIDebugDraw* drawerRef)
{
	_dynamicWorldRef = worldRef;
	_debugDrawer = drawerRef;
}

const physics_wrapper::RayCastHitResult physics_wrapper::RayCast::SingleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor) 
{
	_dynamicWorldRef = physics_manager::PhysicsManager::getInstance()->GetWorld();
	btVector3 origin(rayOrigin.GetX(), rayOrigin.GetY(), rayOrigin.GetZ());
	btVector3 destiny(rayDestiny.GetX(), rayDestiny.GetY(), rayDestiny.GetZ());
	btCollisionWorld::ClosestRayResultCallback result(origin, destiny);
	if (drawDebugLine && _debugDrawer != nullptr) {
		btVector3 lineColor(debugLineColor.GetX(), debugLineColor.GetY(), debugLineColor.GetZ());
		_debugDrawer->drawLine(origin, destiny, lineColor);
	}
	_dynamicWorldRef->rayTest(origin, destiny, result);
	eden_utils::Vector3 rHitPoint(0,0,0);
	eden_utils::Vector3 rHitNormal(0,0,0);
	eden_ec::Entity* hitEntity = nullptr;
	if (result.hasHit()) {
		hitEntity = (eden_ec::Entity*)(btRigidBody::upcast(result.m_collisionObject))->getUserPointer();
		rHitPoint = eden_utils::Vector3(result.m_hitPointWorld.getX(), result.m_hitPointWorld.getY(), result.m_hitPointWorld.getZ());
		rHitNormal = eden_utils::Vector3(result.m_hitNormalWorld.getX(), result.m_hitNormalWorld.getY(), result.m_hitNormalWorld.getZ());
	}
	RayCastHitResult hitResult{ result.hasHit(), rHitPoint, rHitNormal, hitEntity };
	return hitResult;
}

const std::vector<physics_wrapper::RayCastHitResult> physics_wrapper::RayCast::MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor) 
{
	_dynamicWorldRef = physics_manager::PhysicsManager::getInstance()->GetWorld();
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
	eden_utils::Vector3 rHitPoint(0, 0, 0);
	eden_utils::Vector3 rHitNormal(0, 0, 0);
	eden_ec::Entity* hitEntity = nullptr;
	if (result.hasHit()) {
		for (int i = 0; i < numCollisions; ++i) {
			rHitPoint = { result.m_hitPointWorld[i].getX(), result.m_hitPointWorld[i].getY(), result.m_hitPointWorld[i].getZ() };
			rHitNormal = { result.m_hitNormalWorld[i].getX(), result.m_hitNormalWorld[i].getY(), result.m_hitNormalWorld[i].getZ() };
			hitEntity = (eden_ec::Entity*)(btRigidBody::upcast(result.m_collisionObjects[i]))->getUserPointer();
			multipleHitResult[i] = { result.hasHit(), rHitPoint, rHitNormal, hitEntity };
		}
	}
	return multipleHitResult;
}

const std::vector<physics_wrapper::RayCastHitResult> physics_wrapper::RayCast::MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const char* layerName, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor) 
{
	_dynamicWorldRef = physics_manager::PhysicsManager::getInstance()->GetWorld();
	btVector3 origin(rayOrigin.GetX(), rayOrigin.GetY(), rayOrigin.GetZ());
	btVector3 destiny(rayDestiny.GetX(), rayDestiny.GetY(), rayDestiny.GetZ());
	btCollisionWorld::AllHitsRayResultCallback result(origin, destiny);
	if (drawDebugLine) {
		btVector3 lineColor(debugLineColor.GetX(), debugLineColor.GetY(), debugLineColor.GetZ());
		_debugDrawer->drawLine(origin, destiny, lineColor);
	}
	_dynamicWorldRef->rayTest(origin, destiny, result);
	int numCollisions = result.m_hitPointWorld.size();
	std::vector<RayCastHitResult> multipleHitResult;
	eden_utils::Vector3 rHitPoint(0, 0, 0);
	eden_utils::Vector3 rHitNormal(0, 0, 0);
	eden_ec::Entity* hitEntity = nullptr;
	if (result.hasHit()) {
		for (int i = 0; i < numCollisions; ++i) {
			rHitPoint = { result.m_hitPointWorld[i].getX(), result.m_hitPointWorld[i].getY(), result.m_hitPointWorld[i].getZ() };
			rHitNormal = { result.m_hitNormalWorld[i].getX(), result.m_hitNormalWorld[i].getY(), result.m_hitNormalWorld[i].getZ() };
			hitEntity = (eden_ec::Entity*)(btRigidBody::upcast(result.m_collisionObjects[i]))->getUserPointer();
			if (hitEntity->GetComponent<eden_ec::CRigidBody>()->GetCollisionLayerName() == layerName) {
				multipleHitResult.push_back({ result.hasHit(), rHitPoint, rHitNormal, hitEntity });
			}
		}
	}
	return multipleHitResult;
}

const std::vector<physics_wrapper::RayCastHitResult> physics_wrapper::RayCast::MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const std::string layerName, const bool drawDebugLine, const eden_utils::Vector3 debugLineColor)
{
	return MultipleHitRayCast(rayOrigin, rayDestiny, layerName.c_str(), drawDebugLine, debugLineColor);
}
