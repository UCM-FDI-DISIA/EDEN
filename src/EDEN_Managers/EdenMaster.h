#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_EDENMASTER_H
#define EDEN_EDENMASTER_H

#include "Singleton.h"

#include "defs.h"

namespace Ogre {
	class Root;
}
namespace eden_render {
	class RenderManager;
}
namespace eden_input {
	class InputManager;
}

namespace physics_manager{
	class PhysicsManager;
}

namespace eden_audio {
	class AudioManager;
}

namespace eden 
{
	class SceneManager;
	/// @brief El master es la clase singleton encargada de llevar el bucle principal de juego
	/// @brief Es esta clase que gestiona el tiempo del juego
	class Master : public Singleton<Master>
	{
		friend Singleton<Master>;

	public:
		static bool isInitialized() { return _initialized; }

		/// @brief Booleano de salida del bucle principal
		bool exit = false;

		/// @brief Bucle principal de juego
		EDEN_API void Loop();

		EDEN_API void CloseApplication();

		/// @brief Destructora por defecto de EdenMaster
		EDEN_API ~Master() override;

		EDEN_API static Master* getInstance();
	private:

		static bool _initialized;

		// static bool _initialized;
		/// @brief El tiempo entre frames en segundos
		float _deltaTime = 0;

		/// @brief El intervalo de tiempo (en segundos) que pasa entre dos actualizaciones físicas
		const float _physicsUpdateTimeInterval = 1.0f / 60.0f;
		
		/// @brief El tiempo transcurrido desde el inicio del bucle en segundos
		float _elapsedTime = 0;

		/// @brief Referencia a al InputManager
		eden_input::InputManager* _inputManager;

		/// @brief Referencia a al SceneManager
		SceneManager* _scnManager;

		/// @brief Referencia a al RenderManager
		eden_render::RenderManager* _renderManager;

		/// @brief Referencia al PhysicsManager
		physics_manager::PhysicsManager* _physicsManager;

		/// @brief Referencia al AudioManager
		eden_audio::AudioManager* _audioManager;

		/// @brief Constructora por defecto de EdenMaster
		EDEN_API Master();
	};
}
#endif

