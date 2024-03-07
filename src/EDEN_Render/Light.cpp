#include "Light.h"

// Librerias adicionales
#include <OgreSceneManager.h>

// Archivos del proyecto
#include "RenderManager.h"
#include "Node.h"
#include "Vector3.h"

render_wrapper::Light::Light(const std::string entityID, LightType type) : _entityID(entityID)
{
	_light = getSceneManager()->createLight();

	Ogre::Light::LightTypes OgreLightType;

	switch (type)
	{
	case LT_POINT:
		OgreLightType = Ogre::Light::LightTypes::LT_POINT;
		break;
	case LT_DIRECTIONAL:
		OgreLightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;
		break;
	case LT_SPOTLIGHT:
		OgreLightType = Ogre::Light::LightTypes::LT_SPOTLIGHT;
		break;
	default:
		break;
	}
	_light->setType(OgreLightType);
	render_wrapper::Node::Instance()->Attach(GetRenderObject(), entityID);

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
	render_wrapper::Node::Instance()->LookAt(dir, _entityID);
}
Ogre::MovableObject* render_wrapper::Light::GetRenderObject()
{
	return _light;
}
