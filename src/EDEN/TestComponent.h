#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "Component.h"

namespace eden_ec {
	/// @brief Componente creado para comprobar el correcto funcionamiento del
	/// sistema Entidad-Componente del motor. Se deber�a borrar a final de proyecto.
	class cTestComponent : public Component
	{
	private:
		/// @brief Dar nuevo valor a la ID
		const static std::string _id;
	public:
		/// @brief Constructora por defecto
		cTestComponent() = default;

		/// @brief M�todo que devuelve la id del componente. Inprescindible tenerlo en cada nueva clase
		/// de componente
		/// @return ID del componente
		static std::string GetID();

		/// @brief M�todo ejecutado cada frame
		/// @param t Tiempo transcurrido desde el �ltimo frame
		virtual void update(float t);
	};
}

#endif // !TEST_COMPONENT_H