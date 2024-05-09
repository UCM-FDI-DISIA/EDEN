#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreAnimationState.h>
#pragma warning(pop)

#include "MeshRenderer.h"
#include "Vector3.h"
#include "RenderManager.h"
#include "NodeManager.h"
#include "ErrorHandler.h"

render_wrapper::MeshRenderer::MeshRenderer(const std::string entityID, const std::string sceneID, const std::string meshName) : RenderObject(sceneID)
{
	try {
		_ent = GetSceneManager()->createEntity(meshName);
	}
	catch (std::exception e) {
		eden_error::ErrorHandler::Instance()->Exception("Mesh not found", "MeshRenderer ERROR in line 20, could not find mesh " + meshName);
	}

	if (!render_wrapper::NodeManager::Instance()->HasNode(entityID, sceneID))
		render_wrapper::NodeManager::Instance()->CreateSceneObject(entityID, sceneID);

	render_wrapper::NodeManager::Instance()->Attach(GetRenderObject(), entityID, sceneID);
}

render_wrapper::MeshRenderer::~MeshRenderer() {
	_ent->getParentSceneNode()->detachObject(_ent);
	GetSceneManager()->destroyEntity(_ent);
}

void render_wrapper::MeshRenderer::SetMaterial(const std::string material)
{
	_ent->setMaterialName(material);
}

void render_wrapper::MeshRenderer::SetInvisible(bool visibility)
{
	_ent->setVisible(!visibility);
}

Ogre::MovableObject* render_wrapper::MeshRenderer::GetRenderObject()
{
	return _ent;
}
