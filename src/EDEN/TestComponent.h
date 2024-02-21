#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "Component.h"

namespace eden_ec {
	/// @brief Componente creado para comprobar el correcto funcionamiento del
	/// sistema Entidad-Componente del motor. Se debería borrar a final de proyecto.
	class cTestComponent : public Component
	{
	private:
		/// @brief Dar nuevo valor a la ID
		const static std::string _id;
	public:
		/// @brief Constructora por defecto
		cTestComponent() = default;

		/// @brief Método que devuelve la id del componente. Inprescindible tenerlo en cada nueva clase
		/// de componente
		/// @return ID del componente
		static std::string GetID();

		/// @brief Método ejecutado cada frame
		/// @param t Tiempo transcurrido desde el último frame
		virtual void update(float t);
	};
}

#endif // !TEST_COMPONENT_H