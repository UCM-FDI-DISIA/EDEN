#ifndef EDEN_C_LIGHT_H
#define EDEN_C_LIGHT_H

#include "Component.h"
#include "Vector3.h"

#include <string>

#include "defs.h"

namespace eden_script {
	class ComponentArguments;
}

namespace render_wrapper {
	class Light;
}

namespace eden_utils {
	class Quaternion;
}

namespace eden_ec {

	class CTransform;
	class EDEN_API CLight : public Component
	{
	public:
		
		CLight() = default;
		~CLight() override;

		/// @brief Inicializa el componente, guardando los argumentos recibidos desde lua
		/// @param args los argumentos que contienen informacion sobre la luz
		void Init(eden_script::ComponentArguments* args) override;
		/// @brief Metodo encargado de ajustar el transform en cada frame
		/// @param dt El tiempo transcurrido desde el ultimo frame
		void Update(float dt) override;
		/// @brief Crea el wrapper de luz
		void Awake() override;
		/// @brief Se usa para guardad la referencia al transform
		void Start() override;
		/// @brief Devuelve el identificador del componente
		/// @return Identificador del componente
		static std::string GetID() { return "LIGHT"; }

		/// @brief Setea la visibilidad de la luz
		/// @param visibility True -> Visible, False -> No visible
		void SetVisibility(bool visibility, bool sceneChanged = false);
		/// @brief Devuelve si la luz es visible o no
		bool getVisibility();
		/// @brief Ajusta el Diffuse Color de la luz
		/// @param color Variable de color
		void SetDiffuse(eden_utils::Vector3 color);
		/// @brief Ajusta el Specular Color de la luz
		/// @param color Variable de color
		void SetSpecular(eden_utils::Vector3 color);
		/// @brief Setea la direccion de la luz
		/// @param dir Vector de direccion de la luz
		void SetDirection(eden_utils::Vector3 dir);

	protected:
		/// @brief Setea la posicion de la luz
		/// @param dir Vector de posicion de la luz
		void SetPosition(eden_utils::Vector3 dir);
		/// @brief Setea la orientacion de la luz
		/// @param dir Quaternion de orientacion de la luz
		void SetOrientation(eden_utils::Quaternion ori);

	private:
		/// @brief Transform de la entidad
		eden_ec::CTransform* _transform = nullptr;
		/// @brief Referencia al wrapper de luz
		render_wrapper::Light* _lightWrapper = nullptr;
		/// @brief String que guarda el tipo de la luz desde lua
		std::string _lType = "";
		/// @brief Vector de color donde se guarda el Diffuse Color desde lua
		eden_utils::Vector3 _diffuseColor = {0.0, 0.0, 0.0};
		/// @brief Vector de color donde se guarda el Specular Color desde lua
		eden_utils::Vector3 _specularColor= {0.0, 0.0, 0.0};
		/// @brief 
		bool _lightVisibility = true;

	};
}

#endif// EDEN_C_LIGHT_H

