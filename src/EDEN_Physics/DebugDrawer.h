#define _CRTDBG_MAP_ALLOC
#ifndef DEBUG_DRAWER_H
#define DEBUG_DRAWER_H

#include <btBulletDynamicsCommon.h>

namespace Ogre {
	class OgreSceneNode;
}


namespace eden_physics {
	/// @brief Dibuja las bounding boxes de los objetos fisicos
	class DebugDrawer : public btIDebugDraw
	{
	public:
		DebugDrawer();
		~DebugDrawer();

		/// @brief Elimina todas las lineas dibujadas hasta el momento
		void clearLines();

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
		/// @param warningString 
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
		DebugDrawModes _debugMode;
		//Ogre::SceneNode* _node;
	};

}

#endif

