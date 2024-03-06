//Borrar, solo por motivos de test
#include <iostream>
#include<windows.h>  
//

#include <ctime>
#include <chrono>
#include "EdenMaster.h"

#include "RenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"


eden::Master::Master()
{
	renderManager = eden_render::RenderManager::Instance();
	inputManager = eden_input::InputManager::Instance();
	scnManager = SceneManager::Instance();
}

eden::Master::~Master()
{
	Singleton::~Singleton();
}

void eden::Master::Loop()
{
	const std::chrono::steady_clock::time_point loopStartTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point frameStartTime, frameEndTime;

	double lastPhysicsUpdateTime = 0;
	
	while (true) {
		int numPU = (_elapsedTime - lastPhysicsUpdateTime) / (_physicsUpdateTimeInterval * 1000);
		for (int i = 0; i < numPU; ++i) {
			std::cout << "Fixed update " << lastPhysicsUpdateTime + (i * _physicsUpdateTimeInterval * 1000) << '\n';
		}
		lastPhysicsUpdateTime = lastPhysicsUpdateTime + (numPU * _physicsUpdateTimeInterval*1000);

		frameStartTime = std::chrono::high_resolution_clock::now();

		renderManager->Update();
		scnManager->Update(_deltaTime);

		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<double, std::milli>(frameEndTime - frameStartTime).count();
		_elapsedTime = std::chrono::duration<double, std::milli>(frameEndTime - loopStartTime).count();

	}
}
