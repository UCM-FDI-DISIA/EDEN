//Borrar, solo por motivos de test
#include <iostream>
#include<windows.h>  

#include <ctime>
#include <chrono>
#include "EdenMaster.h"
#include "RenderManager.h"
#include "SceneManager.h"


eden::Master::Master()
{
	_renderManager = eden_render::RenderManager::Instance("EDEN Engine");
	if (!_renderManager->couldInitialize()) {
		delete _renderManager;
		std::string error = "EdenMaster ERROR in line 16: RenderManager could not initialize\n";
		throw std::exception(error.c_str());
	}
	//_inputManager = eden_input::InputManager::Instance();
	_scnManager = SceneManager::Instance();
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
	
	while (!exit /*&& !_inputManager->CloseWindowEvent()*/) {
		int numPU = (_elapsedTime - lastPhysicsUpdateTime) / (_physicsUpdateTimeInterval * 1000);
		for (int i = 0; i < numPU; ++i) {
			//std::cout << "Fixed update " << lastPhysicsUpdateTime + (i * _physicsUpdateTimeInterval * 1000) << '\n';
		}
		lastPhysicsUpdateTime = lastPhysicsUpdateTime + (numPU * _physicsUpdateTimeInterval*1000);

		frameStartTime = std::chrono::high_resolution_clock::now();

		_renderManager->Update();
		_scnManager->Update(_deltaTime);
		_renderManager->UpdatePositions();

		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<double, std::milli>(frameEndTime - frameStartTime).count();
		_elapsedTime = std::chrono::duration<double, std::milli>(frameEndTime - loopStartTime).count();

	}

	delete _renderManager;
	//delete _inputManager;
}
