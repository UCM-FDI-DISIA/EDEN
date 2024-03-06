#include "MeshRenderer.h"
#include "RenderManager.h"
#include "Node.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Vector3.h"
#include "OgreAnimationState.h";
render_wrapper::MeshRenderer::MeshRenderer(const std::string entityID, const std::string meshName)
{
	_ent = getSceneManager()->createEntity(meshName);

	Ogre::AnimationStateSet* anims = _ent->getAllAnimationStates();
	auto iterator = anims->getAnimationStateIterator();
	auto it = iterator.begin();
	_anim = it->second;
	_anim->setEnabled(true);
	_anim->setLoop(true);
	_anim->setTimePosition(0);

	if (!render_wrapper::Node::Instance()->HasNode(entityID))
		render_wrapper::Node::Instance()->CreateSceneObject(entityID);

	render_wrapper::Node::Instance()->Attach(GetRenderObject(), entityID);



}

void render_wrapper::MeshRenderer::ActivateAnim(float dt) {
	_anim->addTime(0.01);
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
