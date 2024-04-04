#define _CRTDBG_MAP_ALLOC

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

render_wrapper::MeshRenderer::MeshRenderer(const std::string entityID, const std::string meshName)
{
	_ent = getSceneManager()->createEntity(meshName);

	if (!render_wrapper::NodeManager::Instance()->HasNode(entityID))
		render_wrapper::NodeManager::Instance()->CreateSceneObject(entityID);

	render_wrapper::NodeManager::Instance()->Attach(GetRenderObject(), entityID);
}

void render_wrapper::MeshRenderer::SetMaterial(const std::string material)
{
	_ent->setMaterialName(material);
}

void render_wrapper::MeshRenderer::SetInvisible(bool visibility)
{
	_ent->setVisible(visibility);
}

Ogre::MovableObject* render_wrapper::MeshRenderer::GetRenderObject()
{
	return _ent;
}
