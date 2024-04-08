#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#pragma warning(pop)

#include "ParticleSystem.h"
#include "NodeManager.h"

render_wrapper::ParticleSystem::ParticleSystem(const std::string entityID, const std::string sceneID, const std::string resourceName, const std::string systemName) : RenderObject(sceneID)
{
	_name = systemName;

	_ogrePSystem = GetSceneManager()->createParticleSystem(_name, resourceName);

	if (!render_wrapper::NodeManager::Instance()->HasNode(entityID, sceneID))
		render_wrapper::NodeManager::Instance()->CreateSceneObject(entityID, sceneID);

	render_wrapper::NodeManager::Instance()->Attach(_ogrePSystem, entityID, sceneID);
}

render_wrapper::ParticleSystem::~ParticleSystem() {
	GetSceneManager()->destroyParticleSystem(_name);
}

bool render_wrapper::ParticleSystem::IsActive()
{
	return _ogrePSystem->getEmitting();
}

void render_wrapper::ParticleSystem::SetActive(bool active)
{
	_ogrePSystem->setEmitting(active);
}

void render_wrapper::ParticleSystem::SetVisible(bool active)
{
	_ogrePSystem->setVisible(active);
}

void render_wrapper::ParticleSystem::SetMaterial(const std::string material)
{
	_ogrePSystem->setMaterialName(material);
}

Ogre::MovableObject* render_wrapper::ParticleSystem::GetRenderObject()
{
	return _ogrePSystem;
}
