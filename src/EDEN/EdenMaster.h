#ifndef EDENMASTER_h
#define EDENMASTER_h

#include "Singleton.h"

namespace Ogre {
	class Root;
}

namespace eden 
{
	/// @brief El master es la clase singleton encargada de llevar el bucle principal de juego
	/// @brief Es esta clase que gestiona el tiempo del juego
	class Master : public Singleton<Master>
	{
		friend Singleton<Master>;

	public:
		/// @brief Bucle principal de juego
		void Loop();

		~Master() override;
	private:
		/// @brief El tiempo entre frames 
		double _deltaTime = 0;
		/// @brief El tiempo transcurrido desde el inicio del bucle en milisegundos
		double _elapsedTime = 0;
		Ogre::Root* _root = nullptr;

		Master();
	};
}
#endif

