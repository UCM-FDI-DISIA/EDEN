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

//Nota: Aniadir ids distintas a cada instancia de la clase y darle ese nombre al nodo

eden_debug::DebugDrawer::DebugDrawer(std::string id, std::string sceneID) {
	_debugMode = DBG_DrawWireframe;
	_lines = std::vector<Ogre::MovableObject*>();
	_id = id;
	_sceneID = sceneID;
	render_wrapper::NodeManager::Instance()->CreateSceneObject(_id, _sceneID);
}

eden_debug::DebugDrawer::~DebugDrawer() {
	clearLines();
	render_wrapper::NodeManager::Instance()->RemoveSceneObject(_id, _sceneID);
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

	line->begin("BaseWhite", Ogre::RenderOperation::OT_LINE_LIST);
	line->position(origin.x(), origin.y(), origin.z());
	line->position(end.x(), end.y(), end.z());
	line->colour(Ogre::ColourValue(color.x(), color.y(), color.z()));
	line->end(); 

	render_wrapper::NodeManager::Instance()->Attach(line, _id, _sceneID);
	_lines.push_back(line);

}

void eden_debug::DebugDrawer::drawRigidBody(btRigidBody* rb, const btVector3& color) 
{
	btCollisionShape* shape = rb->getCollisionShape();
	btVector3 from;
	btVector3 to; 
	btTransform transform = rb->getWorldTransform();

	shape->getAabb(transform, from, to);

	btVector3 halfExtents = (to - from) * 0.5f;
	btVector3 center = (to + from) * 0.5f;
	int i, j;

	btVector3 edgecoord(1.f, 1.f, 1.f), pa, pb;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			pa = btVector3(edgecoord[0] * halfExtents[0], edgecoord[1] * halfExtents[1],
				edgecoord[2] * halfExtents[2]);
			pa += center;

			int othercoord = j % 3;
			edgecoord[othercoord] *= -1.f;
			pb = btVector3(edgecoord[0] * halfExtents[0], edgecoord[1] * halfExtents[1],
				edgecoord[2] * halfExtents[2]);
			pb += center;

			drawLine(pa, pb, color);
		}
		edgecoord = btVector3(-1.f, -1.f, -1.f);
		if (i < 3)
			edgecoord[i] *= -1.f;
	}
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
