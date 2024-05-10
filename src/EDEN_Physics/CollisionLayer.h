#ifndef EDEN_COLLISIONLAYER_H
#define EDEN_COLLISIONLAYER_H

#include <string>
#include <unordered_map>

#include "defs.h"
#define MAX_COLLISION_GROUP_NUMBER 32
#define DEFAULT_COLLISION_LAYER 1
namespace physics_manager {
	class PhysicsManager;
}

namespace physics_wrapper {
	class CollisionLayer
	{
		friend physics_manager::PhysicsManager;
	private:
		/// @brief Constructora de la capa de colision. Se encarga de gestionar que numero le corresponde
		/// @param layerName Nombre asociado a la capa que queremos crear 
		/// @param sceneID ID de la escena a la que pertenece la capa
		CollisionLayer(std::string layerName, std::string sceneID);

		/// @brief Quita colisión entre esta capa y la capa dada (por defecto todas las capas colisionan con todas)
		/// @param layer Capa con la que queremos que no colisione 
		void RemoveCollisionToLayer(physics_wrapper::CollisionLayer* layer);
		
		/// @brief Gestiona el numero de capas que lleva cada escena
		static std::unordered_map<std::string, int> _currentLayer;
		
		/// @brief Nombre de la capa
		const std::string _layerName;
		
		/// @brief Representacion numerica de la capa
		int _layer = 0;
		
		/// @brief Mascara de colision (define con que objetos colisiona)
		int _collisionMask = 0xffffff;
	public:
		/// @brief Devuelve el nombre de la capa
		/// @return Devuelve el nombre de la capa
		EDEN_API std::string GetName();

		/// @brief Devuelve el numero asociado a la capa
		/// @return Devuelve el numero asociado a la capa
		EDEN_API int GetLayer();
		
		/// @brief Devuelve la mascara de colision asociada a la capa
		/// @return Devuelve la mascara de colision asociada a la capa
		EDEN_API int GetCollisionMask();
	};
}
#endif

