//Borrar, solo por motivos de test
#include <iostream>

#include <ctime>
#include <chrono>
#include <OgreRoot.h>
#include "EdenMaster.h"


eden::Master::Master()
{
	_root = new Ogre::Root();
}

eden::Master::~Master()
{
	delete _root;
	Singleton::~Singleton();
}

void eden::Master::Loop()
{
	const std::chrono::steady_clock::time_point loopStartTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point frameStartTime, frameEndTime;
	
	while (true) {
		frameStartTime = std::chrono::high_resolution_clock::now();
		
		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<double, std::milli>(frameEndTime - frameStartTime).count();
		_elapsedTime = std::chrono::duration<double, std::milli>(frameEndTime - loopStartTime).count();
		std::cout << "Elapsed time: " << _elapsedTime << '\n';
	}
}
