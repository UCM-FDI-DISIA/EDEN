//Borrar, solo por motivos de test
#include <iostream>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <ctime>
#include <chrono>

#include "EdenMaster.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include <InputManager.h>
#include "SceneManager.h"


eden::Master::Master()
{
	_renderManager = eden_render::RenderManager::Instance("EDEN Engine");
	if (!_renderManager->couldInitialize()) {
		delete _renderManager;
		std::string error = "EdenMaster ERROR in line 16: RenderManager could not initialize\n";
#ifdef _MSC_VER
		throw std::exception(error.c_str());
#endif
#ifdef __clang__
		throw std::exception();
#endif
	}
	_inputManager = eden_input::InputManager::Instance();
	_scnManager = SceneManager::Instance();
	_physicsManager = physics_manager::PhysicsManager::Instance();
}

eden::Master::~Master()
{
	delete _inputManager;
	delete _renderManager;
	delete _physicsManager;
	Singleton::~Singleton();
}

void eden::Master::Loop()
{
	const std::chrono::steady_clock::time_point loopStartTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point frameStartTime, frameEndTime;

	float lastPhysicsUpdateTime = 0;

	
	while (!exit) {
		int numPU = (_elapsedTime - lastPhysicsUpdateTime) / (_physicsUpdateTimeInterval);
		if (numPU > 0) {
			_physicsManager->UpdatePositions();
			for (int i = 0; i < numPU; ++i) {
				_physicsManager->updateSimulation(_physicsUpdateTimeInterval);
				//std::cout << "Fixed update " << lastPhysicsUpdateTime + (i * _physicsUpdateTimeInterval * 1000) << '\n';
			}
			_physicsManager->ResolvePositions();
		}
		lastPhysicsUpdateTime = lastPhysicsUpdateTime + (numPU * _physicsUpdateTimeInterval);

		frameStartTime = std::chrono::high_resolution_clock::now();

		_inputManager->Update();
		_scnManager->Update(_deltaTime);
		_renderManager->UpdatePositions();
		_renderManager->Update();
		exit = _inputManager->CloseWindowEvent();
		if (_inputManager->ResizedWindowEvent()) {
			_renderManager->ResizedWindow();
		}

		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<float, std::milli>(frameEndTime - frameStartTime).count() / 1000;
		_elapsedTime = std::chrono::duration<float, std::milli>(frameEndTime - loopStartTime).count() / 1000;
	}
}
