#ifndef CAMERA_WRAPPER_H
#define CAMERA_WRAPPER_H

#include "RenderObject.h"

namespace Ogre {
	class Camera;
}

namespace eden_utils {
	class Vector3;
}

namespace eden_render {
	class RenderManager;
}

namespace render_wrapper {
	/// @brief Clase que se encarga de simplificar y "traducir" a un lenguaje que no tengan nada que ver con OGRE las llamadas a metodos relacionadas
	/// con la camara de OGRE
	class CameraWrapper : public render_wrapper::RenderObject {
	public:
		/// @brief Constructora por defecto para el wrapper de la camara
		CameraWrapper(std::string entityID);

		void SetNearClipDistance(float distance);

		void SetFarClipDistance(float distance);

		void SetBackgroundColor(float r, float g, float b, float a);

		eden_utils::Vector3 GetCameraDirection();
	private:
		/// @brief Puntero a una camara de OGRE, sobre la que trabajaremos
		Ogre::Camera* _camera;
	};
}

#endif //CAMERA_WRAPPER_H