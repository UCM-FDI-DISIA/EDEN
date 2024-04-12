#define _CRTDBG_MAP_ALLOC
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
	class EDEN_API CollisionLayer
	{
		friend physics_manager::PhysicsManager;
	private:
		/// @brief Constructora de la capa de colisi�n. Se encarga de gestionar que n�mero le corresponde
		/// @param layerName Nombre asociado a la capa que queremos crear 
		/// @param sceneID ID de la escena a la que pertenece la capa
		CollisionLayer(std::string layerName, std::string sceneID);

		/// @brief Quita colisi�n entre esta capa y la capa dada (por defecto todas las capas colisionan con todas)
		/// @param layer Capa con la que queremos que no colisione 
		void RemoveCollisionToLayer(physics_wrapper::CollisionLayer* layer);
		
		/// @brief Gestiona el n�mero de capas que lleva cada escena
		static std::unordered_map<std::string, int> _currentLayer;
		
		/// @brief Nombre de la capa
		const std::string _layerName;
		
		/// @brief Representaci�n n�merica de la capa
		int _layer;
		
		/// @brief M�scara de colisi�n (define con que objetos colisiona)
		int _collisionMask = 0xffffff;
	public:
		/// @brief Devuelve el nombre de la capa
		/// @return Devuelve el nombre de la capa
		std::string GetName();

		/// @brief Devuelve el n�mero asociado a la capa
		/// @return Devuelve el n�mero asociado a la capa
		int GetLayer();
		
		/// @brief Devuelve la m�scara de colisi�n asociada a la capa
		/// @return Devuelve la m�scara de colisi�n asociada a la capa
		int GetCollisionMask();
	};
}
#endif

