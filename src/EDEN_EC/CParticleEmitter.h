#ifndef CPARTICLE_SYSTEM_H
#define CPARTICLE_SYSTEM_H

#ifdef _MSC_VER
#define PARTICLE_ROUTE "assets\\particles\\"
#endif
#ifdef __APPLE__
#define PARTICLE_ROUTE "assets/particles/"
#endif

#define PARTICLE_EXTENSION ".particle"

#include "Component.h"

#include "defs.h"

namespace render_wrapper {
	class ParticleSystem;
}

namespace eden_ec {
	class CParticleEmitter : public Component
	{
	public:
		/// @brief Constructora por defecto del componente ParticleEmitter
		EDEN_API CParticleEmitter();

		/// @brief Constructora con parametros del componente ParticleEmitter
		/// @param system Nombre del ParticleSystem en un script .particle
		EDEN_API CParticleEmitter(std::string system);

		/// @brief Destructora del ParticleEmitter
		EDEN_API ~CParticleEmitter() override;

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		EDEN_API void Start() override {}

		/// @brief Metodo update heredado de component 
		/// @param t Tiempo entre updates
		EDEN_API void Update(float t) override;

		/// @brief Devuelve el identificador del componente
		EDEN_API static std::string GetID() { return "PARTICLE_EMITTER"; }

		/// @brief Indica si esta activo o no
		/// @return True: El sistema de particulas esta activo, false: El sistema no esta activo
		EDEN_API bool IsActive();

		/// @brief Establece si el sistema de particulas esta activo o no
		/// @param active Booleano que establece si está activo
		EDEN_API void SetActive(bool active, bool sceneChanged = false);

		/// @brief 
		/// @param visibility 
		/// @param sceneChanged 
		EDEN_API void SetVisible(bool visibility, bool sceneChanged = false);

		/// @brief Cambias el material de las particulas
		/// @param material Material al que quieres cambiar
		EDEN_API void SetMaterial(const std::string material);

		/// @brief Resetea el sistema de particulas (si esta en modo loop no hace nada)
		EDEN_API void Reset();

	private:
		/// @brief Wrapper del particle system de ogre
		render_wrapper::ParticleSystem* _pSystem;
		/// @brief Establece si se repite o no
		bool _loop;
		/// @brief Tiempo de actividad en caso de no loopearse
		float _time;
		/// @brief Tiempo que ha pasado de actividad
		float _elapsedTime;
		/// @brief 
		bool _isEmiting = true;
		/// @brief 
		bool _particleVisibility = true;
	};
}
#endif


