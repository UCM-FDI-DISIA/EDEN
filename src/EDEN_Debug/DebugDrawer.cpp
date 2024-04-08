#define _CRTDBG_MAP_ALLOC
#include "DebugDrawer.h"

#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26495)
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreMovableObject.h>
#pragma warning(pop)

#include "NodeManager.h"
#include "RenderManager.h"

//Nota: Añadir ids distintas a cada instancia de la clase y darle ese nombre al nodo

eden_debug::DebugDrawer::DebugDrawer(std::string id, std::string sceneID) {
	_debugMode = DBG_DrawWireframe;
	_lines = std::vector<Ogre::MovableObject*>();
	_id = id;
	_sceneID = sceneID;
	_node = eden_render::RenderManager::Instance()->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode(id);
}

eden_debug::DebugDrawer::~DebugDrawer() {
	clearLines();
	render_wrapper::NodeManager::Instance()->RemoveSceneObject(_id, _sceneID);
	_node = nullptr;
}

void eden_debug::DebugDrawer::clearLines() {

	Ogre::SceneManager* ogreSM = eden_render::RenderManager::Instance()->GetOgreSceneManager();

	for (auto& line : _lines) {
		if (line != nullptr)
			ogreSM->destroyMovableObject(line);
	}

	_lines.clear();
}

void eden_debug::DebugDrawer::drawLine(const btVector3& origin, const btVector3& end, const btVector3& color) {
	Ogre::ManualObject* line = eden_render::RenderManager::Instance()->GetOgreSceneManager()->createManualObject();

	line->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	line->position(origin.x(), origin.y(), origin.z());
	line->position(end.x(), end.y(), end.z());
	line->colour(Ogre::ColourValue(color.x(), color.y(), color.z()));
	line->end();

	render_wrapper::NodeManager::Instance()->Attach(line, _id, _sceneID);
	_lines.push_back(line);

}

void eden_debug::DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
	const btVector3& color) {}

void eden_debug::DebugDrawer::reportErrorWarning(const char* warningString) {}

void eden_debug::DebugDrawer::draw3dText(const btVector3& location, const char* textString) {}

void eden_debug::DebugDrawer::setDebugMode(int debugMode)
{
	_debugMode = (DebugDrawModes)debugMode;
}

int eden_debug::DebugDrawer::getDebugMode() const
{
	return (int)_debugMode;
}
