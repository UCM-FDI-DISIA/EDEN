#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_RAYCASTWRAPPER_H
#define EDEN_RAYCASTWRAPPER_H

#include <vector>
#include <string>

#include "Singleton.h"
#include "Vector3.h"

#include "defs.h"

class btDynamicsWorld;
class btIDebugDraw;
namespace physics_manager {
	class PhysicsManager;
}

namespace eden_ec {
	class Entity;
}

namespace physics_wrapper {
	/// @brief Estructura de datos que contiene la informacion del rayo una vez impacta.
	/// @param hasHit Valor booleano que indica si el rayo ha colisionado o no
	/// @param rayHitLocationPoint Vector3 que indica la posicion de impacto
	/// @param rayHitLocationNormal Vector3 que representa el vector normal de la colision
	/// @param entityHit Referencia a la entidad alcanzada por el rayo
	struct RayCastHitResult {
		bool hasHit = false;
		eden_utils::Vector3 rayHitLocationPoint = eden_utils::Vector3(0, 0, 0);
		eden_utils::Vector3 rayHitLocationNormal = eden_utils::Vector3(0, 0, 0);
		const eden_ec::Entity* entityHit = nullptr;
	};

	class RayCast : public Singleton<RayCast>
	{
		friend Singleton<RayCast>;

	public:
		/// @brief Metodo que genera un rayo que devuelve la informacion del primer objeto con el que colisiona
		/// @param rayOrigin Es el punto en el espacio desde donde sale el rayo
		/// @param rayDestiny Es el punto en el espacio donde queremos que termine el rayo
		/// @param drawDebugLine Un booleano que determina si se tiene o no que dibujar el rayo (para uso de debug)
		/// @param debugLineColor Vector con la informacion RGB del color del rayo a dibujar
		/// @return Devuelve un struct de tipo "RayCastHitResult" con la informacion de colision del rayo con el primer objeto en su trayectoria
		EDEN_API const RayCastHitResult SingleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1,0,0));

		/// @brief Metodo que genera un rayo que devuelve la informacion de todos los objetos con los que colisiona
		/// @param rayOrigin Es el punto en el espacio desde donde sale el rayo
		/// @param rayDestiny Es el punto en el espacio donde queremos que termine el rayo
		/// @param drawDebugLine Un booleano que determina si se tiene o no que dibujar el rayo (para uso de debug)
		/// @param debugLineColor Vector con la informacion RGB del color del rayo a dibujar
		/// @return Devuelve un vector de struct de tipo "RayCastHitResult" con la informacion de colision del rayo con todos los objetos en su trayectoria
		EDEN_API const std::vector<RayCastHitResult> MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1, 0, 0));

		EDEN_API const std::vector<RayCastHitResult> MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const char* layerName, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1, 0, 0));

		EDEN_API const std::vector<RayCastHitResult> MultipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, std::string layerName, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1, 0, 0));

		~RayCast() override = default;
	protected:
		/// @brief Esta constructora deberia llamarse desde e metodo Instance de la clase Singleton
		/// @param worldRef Referencia al mundo de la simulacion fisica
		/// @param drawerRef Referencia a un objeto de dibujado de figuras debug
		EDEN_API RayCast(class btDynamicsWorld* worldRef, class btIDebugDraw* drawerRef);

		/// @brief Constructora por defecto, no deberia llamarse nunca
		EDEN_API RayCast() = default;
	private:
		/// @brief Referencia al mundo de la simulacion fisica
		btDynamicsWorld* _dynamicWorldRef = nullptr;

		/// @brief Encargado de hacer dibujos con caracter de debug
		btIDebugDraw* _debugDrawer = nullptr;
	};
}
#endif // RAYCASTWRAPPER_h
