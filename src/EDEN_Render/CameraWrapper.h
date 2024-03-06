#ifndef CAMERA_WRAPPER_H
#define CAMERA_WRAPPER_H

#include "RenderObject.h"

namespace Ogre {
	class Camera;
	class Viewport;
}

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_render {
	class RenderManager;
}

namespace render_wrapper {
	/// @brief Clase que se encarga de simplificar y "traducir" a un lenguaje que no tengan nada que ver con OGRE las llamadas a metodos relacionadas
	/// con la camara de OGRE
	class CameraWrapper : public RenderObject {
	public:
		/// @brief Constructora por defecto para el wrapper de la camara
		/// @param entityID ID de la entidad a la que se quiere asociar la camara
		CameraWrapper(std::string entityID);
		/// @brief Destructora por defecto para el wrapper de la camara
		~CameraWrapper() = default;

		/// @brief Establece la distancia del plano mas cercano en el frustrum de la camara
		/// @param distance Distancia en numero decimal
		void SetNearClipDistance(float distance);

		/// @brief Establece la distancia del plano mas lejano en el frustrum de la camara
		/// @param distance Distancia en numero decimal
		void SetFarClipDistance(float distance);

		/// @brief Establece el color de fondo de renderizado de la camara, en escala RGBA
		/// @param r Porcentaje de rojo en escala RGBA
		/// @param g Porcentaje de verde en escala RGBA
		/// @param b Porcentaje de azul en escala RGBA
		/// @param a Porcentaje de transparencia (valor alfa) de la escala RGBA. Por defecto, establecido en 1.0f (opaco).
		void SetBackgroundColor(float r, float g, float b, float a = 1.0f);

		/// @brief Establece si el viewport que es dueno del frustrum de la camara puede recalcular la relacion de aspecto
		/// si el frustrum cambia de tamano (esto es, se cambian las distancias de los planos cercano y lejano). Por defecto se usara
		/// en true, ya que el frustrum/camara solo esta usado por un viewport.
		/// @warning En caso de que se establezca en false, la relacion de aspecto para algunos viewports será incorrecta y se vera mal.
		/// @param set Booleano indicando si se setea que la relacion de aspecto la recalcule el viewport dueno de la camara.
		void SetAutoAspectRatio(bool set);

		/// @brief Establece la posicion del nodo de la camara
		/// @param pos Vector3 con la posicion en la que se quiere establecer el nodo de la camara
		void SetCameraPosition(eden_utils::Vector3 pos);

		/// @brief Establece la rotacion del nodo de la camara
		/// @param rot Quaternion con la rotacion del nodo de la camara
		void SetCameraRotation(eden_utils::Quaternion rot);

		/// @brief Establece la direccion en la que se quiere que apunte la camara
		/// @param lookat Vector3 con la direccion en la que se quiere que apunte la camara
		void LookAt(eden_utils::Vector3 lookat);

		/// @brief Devuelve la posicion de la camara
		/// @return Vector3 con la posicion de la camara
		eden_utils::Vector3 GetCameraPosition() const;
	private:
		std::string _entityID;
		/// @brief Puntero a una camara de OGRE, sobre la que trabajaremos
		Ogre::Camera* _camera;

		/// @brief Puntero a un viewport de OGRE, que servira de soporte para la camara
		Ogre::Viewport* _viewport;
		
		/// @brief Devuelve el objeto de render como movable object (en este caso, nuestra camara)
		/// @return Un movable object de OGRE, siendo en este caso, la camara
		Ogre::MovableObject* GetRenderObject() override;
	};
}

#endif //CAMERA_WRAPPER_H