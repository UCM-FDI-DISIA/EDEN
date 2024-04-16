#define _CRTDBG_MAP_ALLOC
#include "Debug.h"

#include "Vector3.h"
#include "DebugDrawer.h"
#include "CRigidBody.h"
#include "RigidBody.h"

eden_debug::Debug::Debug(std::string id, std::string sceneID)
{
	_id = id;
	_debugDrawer = new eden_debug::DebugDrawer(_id, sceneID);
}

eden_debug::Debug::~Debug()
{
	delete _debugDrawer;
}

void eden_debug::Debug::ClearLines()
{
	_debugDrawer->clearLines();
}

void eden_debug::Debug::DrawLine(const eden_utils::Vector3& src, const eden_utils::Vector3& dst, const eden_utils::Vector3& color)
{
	btVector3 _src = EDENToBulletVector(src);
	btVector3 _dst = EDENToBulletVector(dst);
	btVector3 _color = EDENToBulletVector(color);

	_debugDrawer->drawLine(_src, _dst, _color);
}

void eden_debug::Debug::SetDebugMode(int mode)
{
	_debugDrawer->setDebugMode(mode);
}

void eden_debug::Debug::DrawRigidBody(eden_ec::CRigidBody* rb, const eden_utils::Vector3& color)
{
	physics_wrapper::RigidBody* _rb = rb->GetWrapperRigidBody();
	btRigidBody* btRB = _rb->getBulletRigidBody();
	
	btVector3 btColor = EDENToBulletVector(color);

	_debugDrawer->drawRigidBody(btRB, btColor);
}

int eden_debug::Debug::GetDebugMode()
{
	return _debugDrawer->getDebugMode();
}

btVector3 eden_debug::Debug::EDENToBulletVector(eden_utils::Vector3 vector)
{
	return btVector3(vector.GetX(), vector.GetY(), vector.GetZ());
}


