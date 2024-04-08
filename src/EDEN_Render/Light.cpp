#define _CRTDBG_MAP_ALLOC
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreSceneManager.h>
#include <OgreLight.h>
#pragma warning(pop)

#include "Light.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "RenderManager.h"
#include "NodeManager.h"

render_wrapper::Light::Light(const std::string entityID, const std::string sceneID, const std::string type,
	const eden_utils::Vector3 DifusseColor, const eden_utils::Vector3 SpecularColor) : RenderObject(sceneID), _entityID(entityID)
{
	_light = GetSceneManager()->createLight();

	if (!render_wrapper::NodeManager::Instance()->HasNode(entityID))
		render_wrapper::NodeManager::Instance()->CreateSceneObject(entityID);

	// inicializacion generica
	Ogre::Light::LightTypes OgreLightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;

	if (type == "LT_POINT") {
		OgreLightType = Ogre::Light::LightTypes::LT_POINT;
	}
	else if (type == "LT_DIRECTIONAL") {
		OgreLightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;
	}
	else if (type == "LT_SPOTLIGHT") {
		OgreLightType = Ogre::Light::LightTypes::LT_SPOTLIGHT;
	}
	else if (type == "LT_DIRECTIONAL") {
		OgreLightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;
	}
	else OgreLightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;

	_light->setType(OgreLightType);

	SetDiffuse(DifusseColor);
	SetSpecular(SpecularColor);
	render_wrapper::NodeManager::Instance()->Attach(GetRenderObject(), entityID, sceneID);

}

void render_wrapper::Light::SetVisible(bool visibility)
{
	_visibility = visibility;
	_light->setVisible(_visibility);
}

bool render_wrapper::Light::isVisible()
{
	return _visibility;
}

void render_wrapper::Light::SetDiffuse(eden_utils::Vector3 color)
{
	_light->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
}

void render_wrapper::Light::SetSpecular(eden_utils::Vector3 color)
{
	_light->setSpecularColour(color.GetX(), color.GetY(), color.GetZ());
}

void render_wrapper::Light::SetDirection(eden_utils::Vector3 dir)
{
	render_wrapper::NodeManager::Instance()->LookAt(dir, _entityID, _sceneID);
}

void render_wrapper::Light::SetPosition(eden_utils::Vector3 dir)
{
	render_wrapper::NodeManager::Instance()->SetPosition(dir, _entityID, _sceneID);
}

void render_wrapper::Light::SetOrientation(eden_utils::Quaternion ori) {
	render_wrapper::NodeManager::Instance()->SetOrientation(ori, _entityID, _sceneID);
}

Ogre::MovableObject* render_wrapper::Light::GetRenderObject()
{
	return _light;
}

