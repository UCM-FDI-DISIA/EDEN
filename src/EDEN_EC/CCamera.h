#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_C_CAMERA_H
#define EDEN_C_CAMERA_H

#include "Component.h"

#include "defs.h"

namespace render_wrapper {
	class CameraWrapper;
}

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_ec {
	/// @brief Componente de camara.
	class CTransform;
	class EDEN_API CCamera : public Component {
	public:
		/// @brief Constructora por defecto de la camara
		CCamera() = default;

		/// @brief Destructora de la camara
		~CCamera();
		
		/// @brief Necesario para evitar que sea una clase abstracta. No usado
		void Init(eden_script::ComponentArguments* args) override {};

		void Awake() override;

		/// @brief Guarda la referencia al transform, crea el CameraWrapper y añade la entidad al RenderManager
		void Start() override;

		/// @brief Metodo que se ejecutara cada frame y actualizara constantemente la posicion de la camara en caso de que la entidad
		/// a la que este enganchada se mueva
		/// @param dt Tiempo transcurrido desde el ultimo frame
		void Update(float dt) override;

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

		/// @brief Establece si se puede recalcular automaticamente la relacion de aspecto de la camara. Deberia estar siempre en true, o si no, algunas
		/// camaras pueden verse mal. Mas info en el wrapper de la camara.
		/// @param set Booleano indicando si se setea que la relacion de aspecto se recalcule automaticamente.
		void SetAutoAspectRatio(bool set);


		/// @brief Establece la direccion en la que se quiere que apunte la camara
		/// @param lookat Vector3 con la direccion en la que se quiere que apunte la camara
		void LookAt(eden_utils::Vector3 lookat);

		/// @brief Devuelve la posicion de la camara
		/// @return Vector3 con la posicion de la camara
		eden_utils::Vector3 GetCameraPosition() const;

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		inline static std::string GetID() { return "CAMERA"; }

	private:
		/// @brief Puntero al wrapper de la camara, que contendra la camara en si y sobre el que se aplicaran todos los metodos de arriba
		render_wrapper::CameraWrapper* _cameraWrapper = nullptr;

		/// @brief Transform de la entidad sobre la que se engancha la camara
		eden_ec::CTransform* _transform = nullptr;
		/// @brief Establece la posicion de la camara
		/// @param pos Vector3 con la posicion en la que se quiere establecer la camara
		void SetCameraPosition(eden_utils::Vector3 pos);

		/// @brief Establece la rotacion de la camara
		/// @param rot Quaternion con la rotacion de la camara
		void SetCameraRotation(eden_utils::Quaternion rot);
	};
}

#endif //CCAMERA_H