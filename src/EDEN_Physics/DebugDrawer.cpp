#define _CRTDBG_MAP_ALLOC
#include "DebugDrawer.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreMovableObject.h>

#include <NodeManager.h>
#include <RenderManager.h>

eden_physics::DebugDrawer::DebugDrawer() {
	_debugMode = DBG_DrawWireframe;
	_lines = std::vector<Ogre::MovableObject*>();

	/*_node = eden_render::RenderManager::Instance()->getOgreSceneManager()
		->getRootSceneNode()->createChildSceneNode();*/
}

eden_physics::DebugDrawer::~DebugDrawer() {
	clearLines();
	//render_wrapper::NodeManager::Instance()->RemoveSceneObject(_node);
	//_node = nullptr;
}

void eden_physics::DebugDrawer::clearLines() {

	//Ogre::SceneManager* ogreSM = eden_render::RenderManager::Instance()->getOgreSceneManager();

	//for (auto& line : _lines) {
	//	if (line != nullptr)
	//		ogreSM->destroyMovableObject(line);
	//}

	_lines.clear();
}

void eden_physics::DebugDrawer::drawLine(const btVector3& origin, const btVector3& end, const btVector3& color) {
	//Ogre::ManualObject* line = RenderManager::getInstance()->getOgreSceneManager()->createManualObject();

	/*line->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	line->position(origin.x(), origin.y(), origin.z());
	line->position(end.x(), end.y(), end.z());
	line->colour(Ogre::ColourValue(color.x(), color.y(), color.z()));
	line->end();

	_node->attachObject(line);
	_lines.push_back(line);*/

}

void eden_physics::DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
	const btVector3& color) {}

void eden_physics::DebugDrawer::reportErrorWarning(const char* warningString) {}

void eden_physics::DebugDrawer::draw3dText(const btVector3& location, const char* textString) {}

void eden_physics::DebugDrawer::setDebugMode(int debugMode)
{
	_debugMode = (DebugDrawModes)debugMode;
}

int eden_physics::DebugDrawer::getDebugMode() const
{
	return (int)_debugMode;
}
