#define _CRTDBG_MAP_ALLOC
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <string>

#include "RenderObject.h"

namespace Ogre {
	class ParticleSystem;
	class MovableObject;
}

namespace render_wrapper {
	/// @brief Wrapper de ParticleSystem
	class __declspec(dllexport) ParticleSystem : public RenderObject
	{
	public:
		/// @brief Constructora del wrapper
		/// @param entityID ID de la entidad que lo va a tener
		/// @param resourceName nombre del particleSystem en un script .particle
		/// @param systemName nombre del sistema de particulas
		ParticleSystem(const std::string entityID, const std::string sceneID, const std::string resourceName, const std::string systemName);
		
		/// @brief Destructora del particleSystem
		~ParticleSystem();
		
		/// @brief Indica si esta activo o no
		/// @return True: El sistema de particulas esta activo, false: El sistema no esta activo
		bool IsActive();

		/// @brief Establece si el sistema de particulas esta activo o no
		/// @param active Booleano que establece si está activo
		void SetActive(bool active);

		/// @brief Cambias el material de las particulas
		/// @param material Material al que quieres cambiar
		void SetMaterial(const std::string material);
	private:
		/// @brief Sistema de particulas de ogre
		Ogre::ParticleSystem* _ogrePSystem;
		/// @brief Nombre del sistema de particulas
		std::string _name;
		Ogre::MovableObject* GetRenderObject() override;
	};
}
#endif

