#define _CRTDBG_MAP_ALLOC
#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include <string>

#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

namespace eden_utils {
	class Vector3;
}

/// USO DE ESTA CLASE: Esta clase hace de wrapper de DebugDrawer y está pensada para que tambien actue de wrapper de 
/// cualquier otra clase o funcionalidad de debug que se quiera aniadir.
/// Cada instancia de Debug debe hacerse con un "id" distinto a los anteriores ya que el nodo que se creara debera ser unico a 
/// cada una.


namespace eden_debug {

	class DebugDrawer;

	class Debug
	{
	public:
		Debug(std::string id);

		~Debug();

		/// @brief Borrar las líneas actuales en pantalla
		void ClearLines();

		/// @brief Dibujar una nueva linea
		/// @param src Punto de origen
		/// @param dst Punto de destino
		/// @param color Color de la línea
		void DrawLine(const eden_utils::Vector3& src, const eden_utils::Vector3& dst, const eden_utils::Vector3& color);

		/// @brief Indicar el modo de debug que se quiere usar
		/// @param mode Modo pasado como int
		void SetDebugMode(int mode);

		/// @brief Obtiene el modo de debug actual
		/// @return Modo de debug en int
		int GetDebugMode();

	private:
		/// @brief Referencia a la clase DebugDrawer
		DebugDrawer* _debugDrawer;

		/// @brief Id propia de cada instancia de la clase
		std::string _id;

		/// @brief Traduce un vector del motor a vector de Bullet
		/// @param vector Vector del motor que quieres traducir
		/// @return Vector de Bullet traducido
		btVector3 EDENToBulletVector(eden_utils::Vector3 vector);
	};

}

#endif
