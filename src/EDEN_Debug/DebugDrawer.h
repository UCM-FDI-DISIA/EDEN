#define _CRTDBG_MAP_ALLOC
#ifndef DEBUG_DRAWER_H
#define DEBUG_DRAWER_H

#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

#include <vector>
#include <string>

namespace Ogre {
	class SceneNode;
	class MovableObject;
	class SceneManager;
}

namespace eden_debug {
	/// @brief Dibuja las bounding boxes de los objetos fisicos
	class __declspec(dllexport) DebugDrawer : public btIDebugDraw
	{
	public:

		DebugDrawer(std::string id, std::string sceneID);
		~DebugDrawer() override;

		/// @brief Elimina todas las lineas dibujadas hasta el momento
		void clearLines() override;

		/// @brief Dibuja una nueva linea
		/// @param origin Punto de partida de la nueva linea
		/// @param end Punto de llegada de la nueva linea
		/// @param color Color que se le quiera dar
		void drawLine(const btVector3& origin, const btVector3& end, const btVector3& color) override;

		/// @brief
		/// @param PointOnB 
		/// @param normalOnB 
		/// @param distance 
		/// @param lifeTime 
		/// @param color 
		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
			const btVector3& color) override;

		/// @brief 
		/// @param warningString Tipo de error recogido como cadena de caracteres
		void reportErrorWarning(const char* warningString) override;

		/// @brief Dibuja texto en 3d
		/// @param location Lugar del mundo donde se quiere posicionar
		/// @param textString Texto que se quiere escribir
		void draw3dText(const btVector3& location, const char* textString) override;

		/// @brief Configura el modo de debug que se quiera usar
		/// @param debugMode Numero correspondiente al struct DebugDrawModes de la clase btIDebugDraw
		void setDebugMode(int debugMode) override;
		
		/// @brief Devuelve el modo debug en el que se encuentra
		/// @return Int que corresponde al modo debug de DebugDrawModes
		int getDebugMode()const override;

	private:
		/// @brief Tipo enumerado con los tipos de debug que existen
		DebugDrawModes _debugMode;

		/// @brief Referencia a un nodo de ogre
		Ogre::SceneNode* _node;

		/// @brief Vector con todas las aristas que se vayan a dibujar
		std::vector<Ogre::MovableObject*> _lines;

		std::string _id;

		std::string _sceneID;
	};

}

#endif

