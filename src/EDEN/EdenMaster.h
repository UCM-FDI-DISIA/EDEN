#ifndef EDENMASTER_h
#define EDENMASTER_h

#include "Singleton.h"

namespace Ogre {
	class Root;
}
namespace eden_render {
	class RenderManager;
}
namespace eden_input {
	class InputManager;
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
		bool exit = false;

		/// @brief Bucle principal de juego
		void Loop();

		~Master() override;
	private:
		/// @brief El tiempo entre frames 
		double _deltaTime = 0;
		/// @brief El intervalo de tiempo (en segundos) que pasa entre dos actualizaciones f�sicas
		const double _physicsUpdateTimeInterval = 1;
		/// @brief El tiempo transcurrido desde el inicio del bucle en milisegundos
		double _elapsedTime = 0;


		/// @brief Referencia a al InputManager
		eden_input::InputManager* _inputManager;

		/// @brief Referencia a al SceneManager
		SceneManager* _scnManager;

		/// @brief Referencia a al RenderManager
		eden_render::RenderManager* _renderManager;

		Master();
	};
}
#endif

