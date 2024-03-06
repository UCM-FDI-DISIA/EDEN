#include "MeshRenderer.h"
#include "RenderManager.h"
#include "Node.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

render_wrapper::MeshRenderer::MeshRenderer(const std::string entityID, const std::string meshName)
{
	_ent = getSceneManager()->createEntity(meshName);
	render_wrapper::Node::Instance()->Attach(GetRenderObject(), entityID);
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
