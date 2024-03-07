#ifndef RAYCASTWRAPPER_h
#define RAYCASTWRAPPER_h

#include <vector>
#include "../EDEN/Singleton.h"
#include "../EDEN/Vector3.h"
#include "../EDEN/Entity.h"

class btDynamicsWorld;
class btIDebugDraw;
namespace physics_manager {
	class PhysicsManager;
}

namespace physics_wrapper {
	/// @brief Estructura de datos que contiene la informaci�n del rayo una vez impacta.
	/// @param hasHit Valor booleano que indica si el rayo ha colisionado o no
	/// @param rayHitLocationPoint Vector3 que indica la posici�n de impacto
	/// @param rayHitLocationNormal Vector3 que representa el vector normal de la colisi�n
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
		/// @brief M�todo que genera un rayo que devuelve la informaci�n del primer objeto con el que colisiona
		/// @param rayOrigin Es el punto en el espacio desde donde sale el rayo
		/// @param rayDestiny Es el punto en el espacio donde queremos que termine el rayo
		/// @param drawDebugLine Un booleano que determina si se tiene o no que dibujar el rayo (para uso de debug)
		/// @param debugLineColor Vector con la informaci�n RGB del color del rayo a dibujar
		/// @return Devuelve un struct de tipo "RayCastHitResult" con la informaci�n de colisi�n del rayo con el primer objeto en su trayectoria
		const RayCastHitResult& singleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1,0,0)) const;

		/// @brief M�todo que genera un rayo que devuelve la informaci�n de todos los objetos con los que colisiona
		/// @param rayOrigin Es el punto en el espacio desde donde sale el rayo
		/// @param rayDestiny Es el punto en el espacio donde queremos que termine el rayo
		/// @param drawDebugLine Un booleano que determina si se tiene o no que dibujar el rayo (para uso de debug)
		/// @param debugLineColor Vector con la informaci�n RGB del color del rayo a dibujar
		/// @return Devuelve un vector de struct de tipo "RayCastHitResult" con la informaci�n de colisi�n del rayo con todos los objetos en su trayectoria
		const std::vector<RayCastHitResult> multipleHitRayCast(const eden_utils::Vector3 rayOrigin, const eden_utils::Vector3 rayDestiny, const bool drawDebugLine = false, const eden_utils::Vector3 debugLineColor = eden_utils::Vector3(1, 0, 0)) const;

		~RayCast() override;
	protected:
		/// @brief Esta constructora deber�a llamarse desde e m�todo Instance de la clase Singleton
		/// @param worldRef Referencia al mundo de la simulaci�n f�sica
		/// @param drawerRef Referencia a un objeto de dibujado de figuras debug
		RayCast(class btDynamicsWorld* worldRef, class btIDebugDraw* drawerRef);

		/// @brief Constructora por defecto, no deber�a llamarse nunca
		RayCast() = default;
	private:
		/// @brief Referencia al mundo de la simulaci�n f�sica
		btDynamicsWorld* _dynamicWorldRef = nullptr;

		/// @brief Encargado de hacer dibujos con caracter de debug
		btIDebugDraw* _debugDrawer = nullptr;

		/// @brief Referencia al manager de f�sicas
		physics_manager::PhysicsManager* _physicsManagerInstance = nullptr;
	};
}
#endif // !RAYCASTWRAPPER_h
