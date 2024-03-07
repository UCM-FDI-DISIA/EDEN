#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "Component.h"

namespace eden_ec {
	/// @brief Componente creado para comprobar el correcto funcionamiento del
	/// sistema Entidad-Componente del motor. Se debería borrar a final de proyecto.
	class cTestComponent : public Component
	{
	public:
		/// @brief Constructora por defecto
		cTestComponent() = default;

		/// @brief Método que devuelve la id del componente. Inprescindible tenerlo en cada nueva clase
		/// de componente
		/// @return ID del componente
		inline static std::string GetID() { return _id; };

		/// @brief Método ejecutado cada frame
		/// @param t Tiempo transcurrido desde el último frame
		virtual void update(float t);

		/// @brief No toma ningún argumento extra, entonces queda vacío.
		virtual void Init(eden_script::ComponentArguments* info) {};
	private:
		/// @brief Dar nuevo valor a la ID
		const static std::string _id;
	};
}

#endif // !TEST_COMPONENT_H