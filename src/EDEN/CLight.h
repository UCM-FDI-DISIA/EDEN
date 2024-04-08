#ifndef EDEN_C_LIGHT_H
#define EDEN_C_LIGHT_H

#include "Component.h"
#include <string>

namespace eden_script {
	class ComponentArguments;
}

namespace render_wrapper {
	class Light;
}

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_ec {

	class CTransform;
	class CLight : public Component
	{
	public:
		
		CLight() = default;
		~CLight() override;

		/// @brief Inicializa el componente, guardando los argumentos recibidos desde lua
		/// @param args los argumentos que contienen informacion sobre la luz
		void Init(eden_script::ComponentArguments* args) override;
		/// @brief 
		/// @param dt El tiempo transcurrido desde el ultimo frame
		void Update(float dt) override;
		/// @brief 
		void Start() override;
		/// @brief Devuelve el identificador del componente
		/// @return Identificador del componente
		static std::string GetID() { return _id; }

		/// @brief Setea la visibilidad de la luz
		/// @param visibility True -> Visible, False -> No visible
		inline void SetVisibility(bool visibility);
		/// @brief Devuelve si la luz es visible o no
		inline bool getVisibility();
		/// @brief 
		/// @param color Variable de color
		inline void SetDiffuse(eden_utils::Vector3 color);
		/// @brief 
		/// @param color Variable de color
		inline void SetSpecular(eden_utils::Vector3 color);
		/// @brief Setea la direccion de la luz
		/// @param dir Vector de direccion de la luz
		inline void SetDirection(eden_utils::Vector3 dir);

	protected:
		/// @brief Identificador del componente
		const static std::string _id;
		/// @brief Setea la posicion de la luz
		/// @param dir Vector de posicion de la luz
		inline void SetPosition(eden_utils::Vector3 dir);
		/// @brief 
		/// @param dir 
		inline void SetOrientation(eden_utils::Quaternion ori);

	private:
		/// @brief Transform de la entidad
		eden_ec::CTransform* _transform = nullptr;
		/// @brief 
		render_wrapper::Light* _lightWrapper = nullptr;
		/// @brief 
		std::string _lType;
	};
}

#endif// EDEN_C_LIGHT_H

