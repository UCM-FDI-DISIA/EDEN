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
		float _deltaTime = 0.f;
		Ogre::Root* _root = nullptr;

		Master();
	};
}
#endif

