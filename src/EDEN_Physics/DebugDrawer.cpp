#include "DebugDrawer.h"
#include <OgreSceneNode.h>

eden_physics::DebugDrawer::DebugDrawer() {

}

eden_physics::DebugDrawer::~DebugDrawer() {

}

void eden_physics::DebugDrawer::clearLines() {

}

void eden_physics::DebugDrawer::drawLine(const btVector3& origin, const btVector3& end, const btVector3& color) {

}

void eden_physics::DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
	const btVector3& color) {

}

void eden_physics::DebugDrawer::reportErrorWarning(const char* warningString)
{

}

void eden_physics::DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}

void eden_physics::DebugDrawer::setDebugMode(int debugMode)
{

}

int eden_physics::DebugDrawer::getDebugMode() const
{
	return 0;
}
