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

namespace eden_ec {
	class CRigidBody;
}

/// USO DE ESTA CLASE: Esta clase hace de wrapper de DebugDrawer y esta pensada para que tambien actue de wrapper de 
/// cualquier otra clase o funcionalidad de debug que se quiera aniadir.
/// Cada instancia de Debug debe hacerse con un "id" distinto a los anteriores ya que el nodo que se creara debera ser unico a 
/// cada una.


namespace eden_debug {

	class DebugDrawer;

	class __declspec(dllexport) Debug
	{
	public:
		/// @brief Constructora publica de la clase
		/// @param id Nombre del nodo de Ogre
		/// @param sceneID Identificador de la escena
		Debug(std::string id, std::string sceneID);

		/// @brief Destructora publica de la clase
		~Debug();

		/// @brief Borrar las lineas actuales en pantalla
		void ClearLines();

		/// @brief Dibujar una nueva linea
		/// @param src Punto de origen
		/// @param dst Punto de destino
		/// @param color Color de la l�nea
		void DrawLine(const eden_utils::Vector3& src, const eden_utils::Vector3& dst, const eden_utils::Vector3& color);

		/// @brief Indicar el modo de debug que se quiere usar
		/// @param mode Modo pasado como int
		void SetDebugMode(int mode);

		/// @brief Dibuja el RigidBody (del color que se le indique)
		/// @param rb El RigidBody a dibujar
		/// @param color El color del que queramos que se pinte el RigidBody
		void DrawRigidBody(eden_ec::CRigidBody* rb, const eden_utils::Vector3& color);

		/// @brief Obtiene el modo de debug actual
		/// @return Modo de debug en int
		int GetDebugMode();

	private:
		/// @brief Referencia a la clase DebugDrawer
		DebugDrawer* _debugDrawer;

		/// @brief Id propia de cada instancia de la clase
		std::string _id = " ";

		/// @brief Traduce un vector del motor a vector de Bullet
		/// @param vector Vector del motor que quieres traducir
		/// @return Vector de Bullet traducido
		btVector3 EDENToBulletVector(eden_utils::Vector3 vector);
	};

}

#endif
