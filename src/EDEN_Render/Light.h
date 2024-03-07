#ifndef LIGHT_H
#define LIGHT_H

#include "RenderObject.h"
#include "OgreLight.h"


enum LightType { LT_POINT, LT_DIRECTIONAL, LT_SPOTLIGHT};

namespace eden_utils {
	class Vector3;
}

namespace render_wrapper
{
	class Light : public RenderObject
	{
	public:
		Light(const std::string entityID, LightType type);
		~Light() {};

		void SetVisible(bool visibility);

		bool isVisible();

		void SetDiffuse(eden_utils::Vector3 color);

		void SetSpecular(eden_utils::Vector3 color);

		void SetDirection(eden_utils::Vector3 dir);
	private:
		virtual Ogre::MovableObject* GetRenderObject();

		Ogre::Light* _light = nullptr;

		bool _visibility = true;

		std::string _entityID = "";
	};
}
#endif // LIGHT_H